#ifndef __ISICG_ISIR_FLAT_COLOR_MATERIAL__
#define __ISICG_ISIR_FLAT_COLOR_MATERIAL__

#include "materials/aMaterial.hpp"
#include "Light/Light.hpp"
#include "brdf/microfacet.hpp"
#include <cmath>

namespace ISICG_ISIR
{	
	class Intersection;

	class FlatColorMaterial : public AMaterial
	{

	public:
			
		FlatColorMaterial() = default;
		
		vec3 shade(const Ray &ray, const Intersection &pos,Light* light)
		{
				return Microfacet::Brdf_shade(this,ray,pos,light);
		}
		
		vec3 getDiffuse(const vec3 &position)
		{
				return diffuse;
		}
		
		vec3 getSpecular(const vec3 &position)
		{
				return specular;
		}
		
		float getReflection(const vec3 &position)
		{
				return reflection;
		}

		float getRefraction(const vec3 &position)
		{
				return refraction;
		}

		float getDiffusion(const vec3 &position)
		{
				return diffusion;
		}
		
		float getIor(const vec3& position)
		{
			return ior;
		};
		
		float getRoughness(const vec3 &position)
		{
				return r;
		}
		
		float getKd(const vec3 &position)
		{
				return kd;
		}
		
		float getKs(const vec3 &position)
		{
				return ks;
		}

		
		static FlatColorMaterial mirror()
		{
			FlatColorMaterial m;
			m.diffuse = vec3(0.7, 0.7, 0.7) + vec3(0.1, 0.1, 0.1);
			m.specular = vec3(1.0, 1.0, 1.0);
			m.diffusion = 0.0f;
			m.reflection = 1.0f;
			m.refraction = 0.0f;
			m.r = 0.1f; // 0->1
			m.ior = 1.3f;
			m.ks=0.5f;
			m.kd=0.5f;
			return m;
		}
		
		static FlatColorMaterial white_plastic()
		{
			FlatColorMaterial m;
			m.diffuse = vec3(0.7, 0.7, 0.7) + vec3(0.1, 0.1, 0.1);
			m.specular = vec3(1.0, 1.0, 1.0);
			m.diffusion = 0.9f;
			m.reflection = 0.1f;
			m.refraction = 0.0f;
			m.r = 0.2f; // 0->1
			m.ior = 1.0f;
			m.ks=0.5f;
			m.kd=0.5f;
			return m;
		}
		
		static FlatColorMaterial red_plastic()
		{
			FlatColorMaterial m;
			m.diffuse = vec3(0.85, 0.05, 0.05) + vec3(0.1, 0.0, 0.0);
			m.specular = vec3(1.0, 0.8, 0.8);
			m.diffusion = 0.90f;
			m.reflection = 0.10f;
			m.refraction = 0.0f;
			m.r= 0.2f;
			m.ior=1.0f;
			m.ks=0.4f;
			m.kd=0.6f;
			return m;
		}
		
		static FlatColorMaterial bronze()
		{
			FlatColorMaterial m;
			m.diffuse = vec3(0.714, 0.4284, 0.18144) + vec3(0.1125, 0.0675, 0.054);
			m.specular = vec3(0.9, 0.8, 0.7);
			m.diffusion = 0.75f;
			m.reflection = 0.25f;
			m.refraction = 0.0f;
			m.r=0.1f;
			m.ior=1;
			m.ks=0.2f;
			m.kd=0.8f;
			return m;
		}
		
		static FlatColorMaterial emerald()
		{
			FlatColorMaterial m;
			m.diffuse = vec3(0.09568f, 0.77424f, 0.10f) + vec3( 0.0215f, 0.1745f, 0.0215f);
			m.specular = vec3(0.9, 1.0, 0.9); 
			m.diffusion = 0.30f;
			m.reflection = 0.20f;
			m.refraction = 0.50f;
			m.r=0.1f;
			m.ior=1.4f;
			m.ks=0.7f;
			m.kd=0.3f;

			return m;
		}

		static FlatColorMaterial glass()
		{
			FlatColorMaterial m;
			m.diffuse = vec3(0.95, 0.95, 1.0) + vec3(0.0, 0.0, 0.0);
			m.specular = vec3(1.0, 1.0, 1.0);
			m.diffusion = 0.00f;
			m.reflection = 0.00f; // 0.05
			m.refraction = 1.0f; // 1 -
			m.r=0.1f;
			m.ior=1.33f;
			m.ks=0.8f;
			m.kd=0.2f;
			return m;
		}

		static FlatColorMaterial obsidian()
		{
			FlatColorMaterial m;
			m.diffuse = vec3(0.18275,0.17,0.22525);
			m.specular = vec3(0.332741,0.328634,0.346435);
			m.diffusion = 0.90f;
			m.reflection = 0.10f; 
			m.refraction = 0.0f; 
			m.r=0.3f;
			m.ior=1.0f;
			m.ks=0.8f;
			m.kd=0.2f;
			return m;
		}
			
		static FlatColorMaterial pearl()
		{	
					
			FlatColorMaterial m;
			m.diffuse = vec3(1,0.829,0.829);
			m.specular = vec3(0.296648,0.296648,0.296648);
			m.diffusion = 0.90f;
			m.reflection = 0.10f; 
			m.refraction = 0.0f; 
			m.r=0.088f;
			m.ior=1.0f;
			m.ks=0.8f;
			m.kd=0.2f;
			return m;
		
		}
		static FlatColorMaterial ruby()
		{
			FlatColorMaterial m;
			m.diffuse = vec3(0.61424,0.04136,0.04136);
			m.specular = vec3(0.727811,0.626959,0.626959);
			m.diffusion = 0.50f;
			m.reflection = 0.40f; 
			m.refraction = 0.1f; 
			m.r=0.6f;
			m.ior=1.0f;
			m.ks=0.8f;
			m.kd=0.2f;
			return m;
		
		}
		
		static FlatColorMaterial turquoise()
		{		
			FlatColorMaterial m;
			m.diffuse = vec3(0.396,0.74151,0.69102)	;
			m.specular = vec3(0.297254,0.30829,0.306678);
			m.diffusion = 0.70f;
			m.reflection = 0.30f; 
			m.refraction = 1.0f; 
			m.r=0.1f;
			m.ior=1.0f;
			m.ks=0.8f;
			m.kd=0.2f;
			return m;
		
		}
		
		static FlatColorMaterial brass()
		{
					
			FlatColorMaterial m;
			m.diffuse = vec3(0.780392,0.568627,0.113725);
			m.specular = vec3(0.992157,0.941176,0.807843);
			m.diffusion = 0.70f;
			m.reflection = 0.30f; 
			m.refraction = 1.0f; 
			m.r=0.21794872f;
			m.ior=1.0f;
			m.ks=0.8f;
			m.kd=0.2f;
			return m;
		
		}
		static FlatColorMaterial chrome()
		{
					
			FlatColorMaterial m;
			m.diffuse = vec3(0.4,0.4,0.4);
			m.specular = vec3(0.774597, 0.774597,0.774597);
			m.diffusion = 0.60f;
			m.reflection = 0.40f; 
			m.refraction = 1.0f; 
			m.r=0.6f;
			m.ior=1.0f;
			m.ks=0.8f;
			m.kd=0.2f;
			return m;
		}
					
		static FlatColorMaterial copper()
		{
			FlatColorMaterial m;
			m.diffuse = vec3(0.7038,0.27048,0.0828);
			m.specular = vec3(0.256777,0.137622,0.086014);
			m.diffusion = 0.70f;
			m.reflection = 0.30f; 
			m.refraction = 0.0f; 
			m.r=0.1f;
			m.ior=1.0f;
			m.ks=0.8f;
			m.kd=0.2f;
			return m;
		
		}
		
		static FlatColorMaterial gold()
		{
			FlatColorMaterial m;
			m.diffuse = vec3(0.75164,0.60648,0.22648);
			m.specular = vec3(0.628281,0.555802,0.366065);
			m.diffusion = 0.70f;
			m.reflection = 0.30f; 
			m.refraction = 0.0f; 
			m.r=0.4f;
			m.ior=1.0f;
			m.ks=0.8f;
			m.kd=0.2f;
			return m;
				
		}
		
		static FlatColorMaterial silver()
		{
			FlatColorMaterial m;
			m.diffuse =vec3(0.50754,0.50754,0.50754) ;
			m.specular = vec3(0.508273,0.508273,0.508273);
			m.diffusion = 0.70f;
			m.reflection = 0.30f; 
			m.refraction = 0.0f; 
			m.r=0.4f;
			m.ior=1.0f;
			m.ks=0.8f;
			m.kd=0.2f;
			return m;
		}

		static FlatColorMaterial black_plastic()
		{
			FlatColorMaterial m;
			m.diffuse = vec3(0.01,0.01,0.01);
			m.specular = vec3(0.50,0.50,0.50);
			m.diffusion = 0.90f;
			m.reflection = 0.10f; 
			m.refraction = 0.0f; 
			m.r=.25f;
			m.ior=1.0f;
			m.ks=0.8f;
			m.kd=0.2f;
			return m;
		
		}

		static FlatColorMaterial cyan_plastic()
		{
			FlatColorMaterial m;
			m.diffuse = vec3(0.0,0.50980392,0.50980392)	;
			m.specular = vec3(0.50196078,0.50196078,0.50196078);
			m.diffusion = 0.90f;
			m.reflection = 0.10f; 
			m.refraction = 0.0f; 
			m.r=.25f;
			m.ior=1.0f;
			m.ks=0.8f;
			m.kd=0.2f;
			return m;
		
		}			
		static FlatColorMaterial green_plastic()
		{
			FlatColorMaterial m;
			m.diffuse = vec3(0.1,0.35,0.1);
			m.specular = vec3(0.45,0.55,0.45);
			m.diffusion = 0.90f;
			m.reflection = 0.10f; 
			m.refraction = 0.0f; 
			m.r=.25f;
			m.ior=1.0f;
			m.ks=0.8f;
			m.kd=0.2f;
			return m;
		
		}
		
		static FlatColorMaterial yellow_plastic()
		{
					
			FlatColorMaterial m;
			m.diffuse = vec3(0.5,0.5,0.0);
			m.specular = vec3(0.60,0.60,0.50);
			m.diffusion = 0.90f;
			m.reflection = 0.10f; 
			m.refraction = 0.0f; 
			m.r=.25f;
			m.ior=1.0f;
			m.ks=0.8f;
			m.kd=0.2f;
			return m;
		
		}
		
		static FlatColorMaterial black_rubber()
		{
			FlatColorMaterial m;
			m.diffuse = vec3(0.01,0.01,0.01);
			m.specular = vec3(0.4,0.4,0.4);
			m.diffusion = 0.98f;
			m.reflection = 0.02f; 
			m.refraction = 0.0f; 
			m.r=.078125f;
			m.ior=1.0f;
			m.ks=0.8f;
			m.kd=0.2f;
			return m;
		}

		static FlatColorMaterial cyan_rubber()
		{

			FlatColorMaterial m;
			m.diffuse = vec3(0.4,0.5,0.5);
			m.specular = vec3(0.04,0.7,0.7);
			m.diffusion = 0.98f;
			m.reflection = 0.02f; 
			m.refraction = 0.0f; 
			m.r=.078125f;
			m.ior=1.0f;
			m.ks=0.8f;
			m.kd=0.2f;
			return m;
		
		}
		static FlatColorMaterial green_rubber()
		{
			FlatColorMaterial m;
			m.diffuse = vec3(0.4,0.5,0.4);
			m.specular = vec3(0.04,0.7,0.04);
			m.diffusion = 0.98f;
			m.reflection = 0.02f; 
			m.refraction = 0.0f; 
			m.r=.078125f;
			m.ior=1.0f;
			m.ks=0.8f;
			m.kd=0.2f;
			return m;
		
		}
		static FlatColorMaterial red_rubber()
		{
			FlatColorMaterial m;
			m.diffuse =vec3(0.5,0.4,0.4) ;
			m.specular = vec3(0.7,0.04,0.04);
			m.diffusion = 0.98f;
			m.reflection = 0.02f; 
			m.refraction = 0.0f; 
			m.r=.078125f;
			m.ior=1.0f;
			m.ks=0.8f;
			m.kd=0.2f;
			return m;
		
		}
		static FlatColorMaterial white_rubber()
		{
						
			FlatColorMaterial m;
			m.diffuse = vec3(0.5,0.5,0.5);
			m.specular = vec3(0.7,0.7,0.7);
			m.diffusion = 0.98f;
			m.reflection = 0.02f; 
			m.refraction = 0.0f; 
			m.r=.078125f;
			m.ior=1.0f;
			m.ks=0.8f;
			m.kd=0.2f;
			return m;
		
		}
		static FlatColorMaterial yellow_rubber()
		{
					
			FlatColorMaterial m;
			m.diffuse = vec3(0.5,0.5,0.4);
			m.specular = vec3(0.7,0.7,0.04);
			m.diffusion = 0.98f;
			m.reflection = 0.02f; 
			m.refraction = 0.0f; 
			m.r=.078125f;
			m.ior=1.0f;
			m.ks=0.8f;
			m.kd=0.2f;
			return m;
		
		}
		vec3 diffuse;
		vec3 specular;
		float diffusion;
		float reflection;
		float refraction;
		float r;
		float ior;
		float ks;
		float kd;
	};
} 

#endif 
