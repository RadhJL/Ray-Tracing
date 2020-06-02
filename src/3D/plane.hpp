#ifndef __ISICG_ISIR_PLANE__
#define __ISICG_ISIR_PLANE__

#include <vector>
#include "aObject3D.hpp"

#include<iostream>

namespace ISICG_ISIR
{
	class Plane : public AObject3D
	{
	public:
		Plane() = default;

		Plane(const vec3 &a, const vec3 &b, const vec3 &c, const vec3 &d, AMaterial* const material, const glm::mat3 &view)
			:  a(a), b(b), c(c), d(d)
		{
			this->normal = getNormal();
			setMaterial(material);
			setViewMatrix(view);
		}

		 bool isInside(const vec3& q)
		{
			vec3 n = normal;
			vec3 ua = b-a,  ub = c-b, uc = d-c, ud = a-d;
			vec3 va = q-a,  vb = q-b, vc = q-c, vd = q-d;
    
			if ((dot(cross(ua,va),n)>0) && (dot(cross(ub,vb),n)>0) && (dot(cross(uc,vc),n)>0) && (dot(cross(ud,vd),n)>0))
				return true;
			else
				return false;
		}

		Intersection intersect(const Ray &ray)
		{
			vec3 pos= ray.origin;
			vec3 dir= ray.direction;

			vec3 n = normal;
			vec3 vdif = a-pos;
			float vdotn = dot(dir,n);

			if(fabs(vdotn) < 1.e-4) return Intersection();
			float t = dot(vdif,n)/vdotn;
			
			if(t < 0.0001) return Intersection();
			vec3 q = pos + dir*t;
			
			if(!isInside(q)) return Intersection();

			return Intersection(normal, t, t + 0.1, this);
		}

		vec3 getNormal()
		{
			vec3 result = cross((b-a),c-a);
			result = normalize(result);
			return result;
		}

	private:
		vec3 normal;
		vec3 a;
		vec3 b;
		vec3 c;
		vec3 d;

	};
} 

#endif 
