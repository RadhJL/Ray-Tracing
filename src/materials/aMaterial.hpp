#ifndef __ISICG_ISIR_A_MATERIAL__
#define __ISICG_ISIR_A_MATERIAL__

#include "light/light.hpp"
#include "core/intersection.hpp"
#include "core/ray.hpp"


namespace ISICG_ISIR
{
	
	class AMaterial
	{

	public:
		virtual vec3 shade(const Ray &ray, const Intersection &pos,Light* lights) = 0;

		virtual vec3 getDiffuse(const vec3 &position) = 0;
		virtual vec3 getSpecular(const vec3 &position) = 0;

		virtual float getDiffusion(const vec3 &position) = 0;
		virtual float getReflection(const vec3 &position) = 0;
		virtual float getRefraction(const vec3 &position) = 0;
		virtual float getRoughness(const vec3 &position) = 0;
		virtual float getIor(const vec3 &position) = 0;
		virtual float getKd(const vec3 &position) = 0;
		virtual float getKs(const vec3 &position) = 0;
	
	};
} 

#endif 
