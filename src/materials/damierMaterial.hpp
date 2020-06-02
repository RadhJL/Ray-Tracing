#ifndef __ISICG_ISIR_DAMIER_MATERIAL__
#define __ISICG_ISIR_DAMIER_MATERIAL__

#include "core/defines.hpp"
#include "light/light.hpp"
#include "aMaterial.hpp"
#include "flatColorMaterial.hpp"
#include <cmath>

namespace ISICG_ISIR
{
	class DamierMaterial : public AMaterial
	{

	public:
		DamierMaterial() = default;

		DamierMaterial(const FlatColorMaterial &one, const FlatColorMaterial &two, int axe)
			: one(one), two(two), axe(axe)
		{
		}
		
		bool getPosition(const vec3 &position)
		{
			int a,b;
			if(axe == 0){
				a = (position.y - 100) / 0.5f;
				b = (position.z - 100) / 0.5f;
			}else if (axe == 1){
				a = (position.x - 100) / 0.5f;
				b = (position.z - 100) / 0.5f;
			}else{
				a = (position.x - 100) / 0.5f;
				b = (position.y - 100) / 0.5f;
			}
			if (a % 2 == 0 && b % 2 != 0 || a % 2 != 0 && b % 2 == 0)
				return true;
			return false;
		}
		
		vec3 getDiffuse(const vec3 &position)
		{
			if(getPosition(position))
				return one.diffuse;
			return two.diffuse;
		}
		
		vec3 getSpecular(const vec3 &position)
		{
			if(getPosition(position))
				return one.specular;
			return two.specular;
		}
		
		float getDiffusion(const vec3 &position)
		{
			if(getPosition(position))
				return one.diffusion;
			return two.diffusion;
		}

  		float getReflection(const vec3 &position){
			if(getPosition(position))
				return one.reflection;
			return two.reflection;
		}

		float getRefraction(const vec3 &position)
		{
			if(getPosition(position))
				return one.refraction;
			return two.refraction;
		}

		float getRoughness(const vec3 &position)
		{
			if(getPosition(position))
				return one.r;
			return two.r;
		}
		
		float getIor(const vec3 &position) 
		{
			if(getPosition(position))
				return one.ior;
			 return two.ior;
		}
		
		float getKd(const vec3 &position)
		{
			if(getPosition(position))
				return one.kd;
			 return two.kd;
		}
		
		float getKs(const vec3 &position) 
		{
			if(getPosition(position))
				return one.ks;
			 return two.ks;
		}

		vec3 shade(const Ray &ray, const Intersection &pos,Light* lights)
		{
			vec3 position = ray.origin + pos.distance * ray.direction;
			return damier(position)->shade(ray, pos, lights);
		}

		FlatColorMaterial* damier(const vec3 &position)
		{
			if(getPosition(position))
				return &one;
			return &two;
		}

		int axe;
		FlatColorMaterial one;
		FlatColorMaterial two;
	};
} 

#endif
