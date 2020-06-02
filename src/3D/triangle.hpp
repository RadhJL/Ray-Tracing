#ifndef __ISICG_ISIR_TRIANGLE__
#define __ISICG_ISIR_TRIANGLE__

#include <vector>
#include "aObject3D.hpp"
#include "materials/aMaterial.hpp"


namespace ISICG_ISIR
{
	class Triangle : public AObject3D
	{
	public:
		
		Triangle() = default;

		Triangle(const vec3& a,const vec3& b,const vec3& c)
		{
			v0 = a;
			v1 = b;
			v2 = c;
			centroid = (a+b+c)/3.0f;
		}

		Intersection intersect(const Ray &ray) override
		{
			Intersection inter;
			
			vec3 dir = ray.direction;
			vec3 orig = ray.origin;
			vec3 v0v1 = v1 - v0; 
			vec3 v0v2 = v2 - v0; 
		    
			vec3 N = cross(v0v1,v0v2); 
			vec3 pvec = cross(dir,v0v2); 
			
			float det = dot(v0v1,pvec); 
			if (fabs(det) < 0.00001) return inter; 
			float invDet = 1 / det; 
			vec3 tvec = orig - v0; 
			
			float u = dot(tvec,pvec) * invDet; 
			
			if (u < 0 || u > 1) return inter; 
			vec3 qvec = cross(tvec,v0v1); 
			
			float v = dot(dir,qvec) * invDet; 
			if (v < 0 || u + v > 1) return inter; 
			
			float t = dot(v0v2,qvec) * invDet; 
			inter = Intersection(N,t,t,this);
			inter.tmax = t;

			return inter; 
		}


	public:
		vec3 v0;
		vec3 v1;
		vec3 v2;
		vec3 centroid;
	};
} 

#endif 
