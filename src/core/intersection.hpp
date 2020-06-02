#ifndef __ISICG_ISIR_INTERSECTION__
#define __ISICG_ISIR_INTERSECTION__

#include "core/defines.hpp"

namespace ISICG_ISIR
{
	class AObject3D;

	class Intersection
	{
	public:	
		Intersection() = default;
		
		Intersection(const vec3& normal,const float& distance,const float& tmax, AObject3D* obj)
		{
			this->normal = normalize(normal);
			this->distance = distance;
			this->obj = obj;
			this->tmax = tmax;
		}
	
		Intersection(const Intersection &i)
		{
			this->normal = i.normal;
			this->distance = i.distance;
			this->obj = i.obj;
			this->tmax = i.tmax;
		}

		vec3 normal = VEC3F_ZERO;
		float distance = -1.f;
		float tmax = -1.f;
		AObject3D *obj = nullptr;
	};
} 

#endif 
