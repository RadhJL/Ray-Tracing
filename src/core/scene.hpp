#ifndef __ISICG_ISIR_Scene__
#define __ISICG_ISIR_Scene__

#include "defines.hpp"
#include "camera.hpp"
#include "3D/aObject3D.hpp"
#include "Light/Light.hpp"
#include <algorithm>

namespace ISICG_ISIR
{
	class Scene
	{
	public:


		Scene(Camera camera): camera(camera)
		{
		}

		Ray generateRay(const vec3 &vec) {
			return camera.generateRay(vec);
		}

		Intersection intersect(const Ray &ray) {
			
			float minDistance = LONG_MAX;
			Intersection minIntersection; 				
			
			for (uint o = 0; o < objects.size(); ++o)
			{
				Intersection inter = objects[o]->intersect(ray);
				if (inter.obj != nullptr && inter.distance < minDistance)
				{
					minIntersection = inter;
					minDistance = inter.distance;
				}
			}
			return minIntersection; 
		}

		AObject3D* intersectShadow(const Ray &ray, const float &max_distance) {

			for (uint o = 0; o < objects.size(); ++o)
			{
				Intersection inter = objects[o]->intersect(ray);
				if (inter.obj != nullptr &&  (max_distance != -1 && inter.distance < max_distance) )
					return inter.obj;
				else if (inter.obj != nullptr && max_distance == -1)
					return inter.obj;
			}
			return nullptr;
		}
		
		vec3 raytrace(const Ray& ray,const int& nb) {
			
			vec3 color = vec3(0);
			bool hit = false;

			if (nb > 0)
			{
				Intersection inter = intersect(ray);
				
				if (inter.obj != nullptr )
				{
					hit = true;
					vec3 normal = inter.normal;
					vec3 position = ray.origin + inter.distance * ray.direction;
					vec3 view = - ray.direction;
					Ray rayReflection(ray.origin + (inter.distance - 0.0001f )* ray.direction  , reflect(-view,normal));
					Ray rayRefraction = Refract(ray,normal,position,inter.obj->material->getIor(position));
					
					float diffusion =inter.obj->material->getDiffusion(position) ;
					float reflection =inter.obj->material->getReflection(position) ;
					float refraction =inter.obj->material->getRefraction(position) ;
					
					for (Light* light : lights)
					{	
						Ray rayShadow;
						AObject3D* obj;
						if(light->type == 0)
						{
							int nb_sample = 1;
							vec3 sample_color = vec3(0);
							for(int i = 0; i < nb_sample; i++){
								vec3 hamm  = vec3(0); 
								if(i != 0){
									vec2 h = Hammersley(i,nb_sample);
									hamm = hemisphereSample_uniform(h.x, h.y);
								}
								vec3 l = light ->getPosition()  + hamm;

								rayShadow = Ray(ray.origin + (inter.distance -0.001f )* ray.direction ,normalize(l - position));
								obj = intersectShadow(rayShadow,glm::length(l- position));

								if( (obj != nullptr && obj == inter.obj) || obj == nullptr ) 
								{
									sample_color += diffusion *  inter.obj->material->shade(ray, inter, light);
									sample_color += reflection *  raytrace(rayReflection, nb - 1);
									sample_color += refraction *  raytrace(rayRefraction, nb - 1);
								}
							}
							color += sample_color / float(nb_sample);
						}
						else if(light->type == 1)
						{
							vec3 l = light->getDirection();
							rayShadow = Ray(ray.origin + (inter.distance -0.001f )* ray.direction , l);
							obj = intersectShadow(rayShadow,-1);
							if( (obj != nullptr && obj== inter.obj) || obj == nullptr ){
									color += diffusion *  inter.obj->material->shade(ray, inter, light);
									color += reflection *  raytrace(rayReflection, nb - 1);
									color += refraction *  raytrace(rayRefraction, nb - 1);
							}else
									color += diffusion / float(10) *  inter.obj->material->shade(ray, inter, light);

						}else{
							vec3 l = light ->getPosition();
							rayShadow = Ray(ray.origin + (inter.distance -0.001f )* ray.direction ,normalize(l - position));
							obj = intersectShadow(rayShadow,glm::length(l- position));
							if( (obj != nullptr && obj == inter.obj) || obj == nullptr ) 
							{
								color += diffusion *  inter.obj->material->shade(ray, inter, light);
								color += reflection *  raytrace(rayReflection, nb - 1);
								color += refraction *  raytrace(rayRefraction, nb - 1);
							}else
								color += diffusion / float(10) *  inter.obj->material->shade(ray, inter, light);
						}
					}
						
				}else
					color = vec3(0.196078, 0.6, 0.8);
			}

			return glm::clamp(color /float(lights.size()),vec3(0,0,0),vec3(1,1,1));
		}

		static uint reversebits(uint bits) 
		{ 
	  	    bits = (bits << 16u) | (bits >> 16u);
			bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
			bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
			bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
			bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
			return float(bits) * 2.3283064365386963e-9; 
		}
		
		static glm::vec2 Hammersley(const uint &i,const uint &N) 
		{
			return glm::vec2(float(i) / float(N), reversebits(i) / float(10));
		}

		 vec3 hemisphereSample_uniform(const float& u,const float& v) {
			 float phi = v * 2.0 * PI;
			 float cosTheta = 1.0 - u;
			 float sinTheta = sqrt(1.0 - cosTheta * cosTheta);
			 return vec3(cos(phi) * sinTheta, sin(phi) * sinTheta, cosTheta);
		 }

		Ray Refract(const Ray& ray, const vec3 &normal, const vec3 &position, const float &ior)
		{
				vec3 bias = 0.001f * normal; 
			    bool outside = dot(ray.direction,normal) < 0; 
				float cosi =  clamp(dot(ray.direction,normal),-1.f, 1.f);
				float etai = 1, etat = ior; 
				vec3 n = normal; 
				if (cosi < 0) { cosi = -cosi; } else { std::swap(etai, etat); n= -normal; } 
				float eta = etai / etat; 
				float k = 1 - eta * eta * (1 - cosi * cosi); 
				vec3 direction = k < 0 ? vec3(0,0,0) : eta * ray.direction + (eta * cosi - sqrtf(k)) * n;
				vec3 origin= outside ? position - bias : position + bias;
				return Ray(origin,direction);
		}

		constexpr const float& clamp( const float& v, const float& lo, const float& hi )
		{
			assert( !(hi < lo) );
			return (v < lo) ? lo : (hi < v) ? hi : v;
		}

		int size() 
		{
			return objects.size();
		}

		void addObject(AObject3D* object)
		{
			objects.emplace_back(object);
		}

		void addLight(Light* light)
		{
			lights.emplace_back(light);
		}

		void useCamera(Camera camera)
		{
			this->camera = camera; 
		}
		
		Camera camera;
		std::vector<AObject3D *> objects;
		std::vector<Light *> lights;

	};
} 

#endif 
