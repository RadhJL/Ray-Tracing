#ifndef __ISICG_ISIR_BVH__
#define __ISICG_ISIR_BVH__

#include "3d/triangleMesh.hpp"
#include "accelerator/box.hpp"
#include "bvhnode.hpp"
#include "core/intersection.hpp"
#include <algorithm>
#include <omp.h>

namespace ISICG_ISIR
{

	class BVH
	{
	public:
		BVH() = default;

		BVH(std::vector<Triangle*> &triangles, const Box& root_bbx,const int& type)
		{
			Chrono chrono0;
			chrono0.start();
			std::cout << "Begin BVH creation..." << std::endl;
		
			std::sort(triangles.begin(),triangles.end(),Compare);
			this -> root = new BVHNode(NULL, NULL, root_bbx, 0, triangles.size() - 1);
			
			if(type)
				createbvhCOUNT(root, triangles);
			else
				createbvhSAH(root, triangles);

			chrono0.stop();
			std::cout << "End BVH creation in " << chrono0.elapsedTime() << "s "<< std::endl;
		}
		
		void createbvhSAH(BVHNode *node, const std::vector<Triangle*> &triangles)
		{
			if (node->range1 - node->range0 < 7)
			{
				for (int i = node->range0; i <= node->range1; i++)
					node->box.triangles.push_back(triangles[i]);
				return;
			}

			float min_cost = std::numeric_limits<float>:: max();
			int left_range1 = 0, right_range0 = 0;
			Box left_box, right_box;
			
			#pragma omp parallel for schedule(dynamic) shared(min_cost)
			for (int i = node->range0; i <=node->range1; ++i) {
				Box b0, b1;
				int count0 = 0, count1 = 0;
				
				for (int j = node->range0; j <= i; ++j) {
					b0.expand(*triangles[j]);
					count0 ++;
				}

				for (int j = i+1; j <= node->range1; ++j) {
					b1.expand(*triangles[j]);
					count1 ++;
				}
				
				float cost = .125f + (count0 * b0.surfaceArea() + count1 * b1.surfaceArea()) / node->box.surfaceArea();
				#pragma omp critical
				if(cost < min_cost){
					min_cost = cost;
					left_range1 = i;
					right_range0 = i+1;
					left_box = b0;
					right_box = b1;
				}
			}
			
			node->left = new BVHNode(NULL, NULL, left_box, node->range0, left_range1);
			node->right = new BVHNode(NULL, NULL, right_box, right_range0, node->range1);

			createbvhSAH(node->left, triangles);
			createbvhSAH(node->right, triangles);
		}

		void createbvhCOUNT(BVHNode *node, const std::vector<Triangle*> &triangles)
		{
			if (node->range1 - node->range0 < 7)
			{	
				for (int i = node->range0; i <= node->range1; i++)
					node->box.triangles.push_back(triangles[i]);
				return;
			}

			int l = node->range0;
			int r = node->range1;
			int mid = l + (r - l) / 2;
			Box leftBox;
			Box rightBox;
			//#pragma omp parallel for schedule(dynamic)
			for (int i = l; i <= mid; i++)
				leftBox.expand(*triangles[i]);
			//#pragma omp parallel for schedule(dynamic)
			for (int i = mid + 1; i <= r; i++)
				rightBox.expand(*triangles[i]);

			node->left = new BVHNode(NULL, NULL, leftBox, l, mid);
			node->right = new BVHNode(NULL, NULL, rightBox, mid + 1 , r);

			createbvhCOUNT(node->left, triangles);
			createbvhCOUNT(node->right, triangles);
		}

		Intersection intersect(BVHNode *node, const Ray &ray)
		{
			if (node->left == nullptr  && node->right == nullptr && node->box.intersectBox(ray))
				return node->box.intersetTriangles(ray);

			Intersection leftIntersection;
			Intersection rightIntersection;
			
			if (node->left != nullptr && node->left->box.intersectBox(ray))
				leftIntersection = intersect(node->left, ray);

			if (node->right != nullptr && node->right->box.intersectBox(ray))
				rightIntersection = intersect(node->right, ray);

			if (rightIntersection.obj != nullptr && leftIntersection.obj != nullptr)
			{
				if (leftIntersection.distance <= rightIntersection.distance)
					return leftIntersection;
				else
					return rightIntersection;

			}else if (rightIntersection.obj != nullptr)
					return rightIntersection;
		   	 
			 else if (leftIntersection.obj != nullptr )
					return leftIntersection;
				
			return Intersection(); // no intersection
		}
	
		static bool Compare(Triangle* a, Triangle* b)
		{
			return a ->centroid.x < b->centroid.x;
		}

		BVHNode *root;
	};
} 

#endif
