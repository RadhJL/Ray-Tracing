#ifndef __ISICG_ISIR_CSG__
#define __ISICG_ISIR_CSG__

#include <vector>
#include <math.h>
#include "aObject3D.hpp"
#include "materials/aMaterial.hpp"


namespace ISICG_ISIR
{
	enum Oper {uni, inter, diff};

	struct CsgNode
	{
		CsgNode() = default;

		CsgNode( AObject3D* primitive,const Oper &operation, CsgNode* left, CsgNode* right)
			: primitive(primitive), operation(operation), left(left), right(right)
		{	
		}

		AObject3D* primitive;
		Oper operation;
		CsgNode* left;
		CsgNode* right;
	};
	
	class CSG: public AObject3D
	{
	public:
		CSG() = default;
	
		CSG(std::vector<AObject3D*> primitives, std::vector<Oper> operations)
			: primitives(primitives), operations(operations)
		{	
			root = createCsg(0,primitives.size() - 1,  operations.size() / 2);
		}

		CsgNode* createCsg(const int& range0,const int& range1, const int& oper_count)
		{
			CsgNode* node = new CsgNode();
			if(range0 == range1){
						node->primitive = primitives.at(primitive_count++);
			}else{
				int mid = range0 + (range1 - range0) / 2;
				node->operation = operations.at(oper_count);		
				node->left = createCsg(range0, mid, oper_count - 1);
				node->right = createCsg(mid + 1, range1,  oper_count + 1);
			}

			return node;
		}


		Intersection intersect(const Ray &ray) override
		{	
			return intersectCSG(ray,root);
		}

		Intersection intersectCSG(const Ray &ray, CsgNode* node){
			
			if(node->left== nullptr || node->right == nullptr){
				return node->primitive->intersect(ray);
			}
			else{
				Intersection left = intersectCSG(ray, node->left);
				Intersection right = intersectCSG(ray, node->right);
				return operationResult(left, right, node->operation);
			}			
		}

		Intersection operationResult(const Intersection& left,const Intersection& right,const Oper& operation){
				Intersection result1, result;
				if(operation == inter)
					result1 = Inter(left,right);
				else if(operation == uni)
					result1 = Union(left,right);
				else if(operation == diff)
					result1 =  Diff(left, right);
				if(result1.obj == nullptr)
					return Intersection();
				result = Intersection(result1);
				//result1.obj = this;
				//result1.obj->material = result.obj->material;
				return result1;
		}

		Intersection Union ( Intersection ab, Intersection cd)
		{

			if(ab.obj != nullptr || cd.obj != nullptr){
					if(ab.obj != nullptr && cd.obj != nullptr && ab.distance <= cd.distance){
						//if(right.distance<left.tmax)
						ab.tmax = std::max(ab.tmax, cd.tmax);
						return ab;
					}
					if(ab.obj != nullptr && cd.obj != nullptr && ab.distance > cd.distance){
						//if(left.distance<right.tmax)
						cd.tmax = std::max(ab.tmax, cd.tmax);
						return cd;
					}
					if(ab.obj != nullptr)
						return ab;
					return cd;
			}

			return Intersection();
		}
		
		Intersection Inter (const Intersection& ab,const Intersection& cd){
			
				Intersection e;
				Intersection f;
				if(ab.obj != nullptr && cd.obj!=nullptr){
					if(ab.distance >= cd.distance)
						e = ab;
					else
						e = cd;
					if(ab.tmax <= cd.tmax)
						f = ab;
					else
						f = cd;
					if(e.distance > f.tmax)
						return Intersection();
					return e;
				}
				return Intersection();
		}

		Intersection Diff (Intersection ab, Intersection cd){
			
			float a = ab.distance;
			float b = ab.tmax;
			float c = cd.distance;
			float d = cd.tmax;
	
			if( a > d || c > b ){ // no intersection
				return ab;
			}
			if ( c > a && b > c  &&  d > b){
				ab.tmax = cd.distance;
				return ab;
			}

			if ( a > c && d > a && b > d){
				//cd.distance = cd.tmax;
				cd.tmax = ab.distance;
				return cd;
			}
			if( c > a &&  d > c && b > d){
				ab.tmax = cd.distance;
				return ab;
			}
			if( a > c  && b > a && d > b){
				return Intersection();
			}
			return Intersection();
		}


	private:
		std::vector<AObject3D*> primitives;
		std::vector<Oper> operations;
		CsgNode* root;
		int primitive_count = 0;
	};

	
} 

#endif 
