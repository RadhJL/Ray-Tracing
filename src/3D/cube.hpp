#ifndef __ISICG_ISIR_Cube__
#define __ISICG_ISIR_Cube__

#include "3d/plane.hpp"
#include "core/defines.hpp"
#include "core/intersection.hpp"

namespace ISICG_ISIR
{
	class Cube : public AObject3D
	{

	public:

		Cube(const vec3 &min, const vec3 &max, AMaterial *const material,const mat3& view)
			: max(max), min(min)
		{
			setMaterial(material);
			setViewMatrix(view);
			float z0 = min.z;
			float z1 = max.z;
			float y0 = min.y;
			float y1 = max.y;
			float x0 = min.x;
			float x1 = max.x;

			//left to right, buttom to top
			Plane plane0(vec3(x0, y0, z0),vec3(x1,y0,z0),vec3(x1,y1,z0),vec3(x0,y1,z0), material,view);
			Plane plane2(vec3(x1, y0, z1),vec3(x0,y0,z1),vec3(x0,y1,z1),vec3(x1,y1,z1), material,view);
			
			Plane plane1(vec3(x1, y0, z0),vec3(x1,y0,z1),vec3(x1,y1,z1),vec3(x1,y1,z0), material,view);
			Plane plane3(vec3(x0, y0, z1),vec3(x0,y0,z0),vec3(x0,y1,z0),vec3(x0,y1,z1), material,view);
			
			Plane plane4(vec3(x0, y0, z1),vec3(x1,y0,z1),vec3(x1,y0,z0),vec3(x0,y0,z0), material,view);
			Plane plane5(vec3(x1, y1, z1),vec3(x0,y1,z1),vec3(x0,y1,z0),vec3(x1,y1,z0), material,view);
			
			planes.push_back(plane0);
			planes.push_back(plane1);
			planes.push_back(plane2);
			planes.push_back(plane3);
			planes.push_back(plane4);
			planes.push_back(plane5);
		}

		Intersection intersect(const Ray &ray) override
		{
			Intersection min_inter, max_inter;
			min_inter.distance = MAX;
			max_inter.distance = -MAX;

			for(int i = 0; i < 6; i++){
				Intersection inter = planes[i].intersect(ray);
				if(inter.obj != nullptr && inter.distance < min_inter.distance)
					min_inter = inter;
				if(inter.obj != nullptr && inter.distance > max_inter.distance)
					max_inter = inter;
			}
			min_inter.tmax = max_inter.distance;
			return min_inter;
		}

		vec3 min;
		vec3 max;
		std::vector<Plane > planes;
	};
} 

#endif
