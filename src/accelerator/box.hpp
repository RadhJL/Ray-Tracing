#ifndef __ISICG_ISIR_BOX__
#define __ISICG_ISIR_BOX__

#include "3d/sphere.hpp"
#include "3d/triangle.hpp"
#include "core/defines.hpp"
#include "core/intersection.hpp"

namespace ISICG_ISIR
{
	class Box 
	{
	public:
		Box()
		{
			max = vec3(-MAX, -MAX, MAX);
			min = vec3(MAX, MAX, -MAX);
		};

		Box(const vec3 &vmin, const vec3 &vmax)
		{
			min = vmin;
			max = vmax;
		}

		void expand(const vec3 &p)
		{
			min.x = std::min(min.x, p.x);
			min.y = std::min(min.y, p.y);
			min.z = std::max(min.z, p.z);
			max.x = std::max(max.x, p.x);
			max.y = std::max(max.y, p.y);
			max.z = std::min(max.z, p.z);
		}

		void expand(const Triangle &t)
		{
			expand(t.v0);
			expand(t.v1);
			expand(t.v2);
		}

		bool empty() const
		{
			return min.x >= max.x || min.y >= max.y || min.z <= max.z;
		}

		float surfaceArea()
		{
			float L = abs(max.z - min.z);
			float H = abs(max.y - min.y);
			float W = abs(max.x - min.x);
			return 2 * (L * W +  L * H +  W * H);
		}

		Intersection intersetTriangles(const Ray &ray)
		{
			Intersection inter;
			Intersection min_inter;
			float tmin = MAX;
			for (int i = 0; i < triangles.size(); i++)
			{
				inter = triangles[i]->intersect(ray);
				if (inter.obj != nullptr && inter.distance < tmin){
					min_inter = inter;
					tmin = inter.distance;
				}
			}
			return min_inter;
		}

		bool intersectBox(const Ray &ray)
		{
		    float tmin = (min.x - ray.origin.x) / ray.direction.x;
			float tmax = (max.x - ray.origin.x) / ray.direction.x;
			if (tmin > tmax)
				std::swap(tmin, tmax);
			float tymin = (min.y - ray.origin.y) / ray.direction.y;
			float tymax = (max.y - ray.origin.y) / ray.direction.y;
			if (tymin > tymax)
				std::swap(tymin, tymax);
			if ((tmin > tymax) || (tymin > tmax))
				return false;
			if (tymin > tmin)
				tmin = tymin;
			if (tymax < tmax)
				tmax = tymax;
			float tzmin = (min.z - ray.origin.z) / ray.direction.z;
			float tzmax = (max.z - ray.origin.z) / ray.direction.z;
			if (tzmin > tzmax)
				std::swap(tzmin, tzmax);
			if ((tmin > tzmax) || (tzmin > tmax))
				return false;
			if (tzmin > tmin)
				tmin = tzmin;
			if (tzmax < tmax)
				tmax = tzmax;

			return true;
		}

		vec3 min;
		vec3 max;
		std::vector<Triangle *> triangles;
	};
} 

#endif
