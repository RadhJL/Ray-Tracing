#ifndef __ISICG_ISIR_SPHERE__
#define __ISICG_ISIR_SPHERE__

#include <vector>
#include "aObject3D.hpp"
#include "materials/aMaterial.hpp"

#define RAY_T_MIN 0.001f
#define RAY_T_MAX 1.0e30f

namespace ISICG_ISIR
{
	class Sphere : public AObject3D
	{
	public:
		Sphere() = default;
		
		Sphere(const vec3 &center, const float &radius, AMaterial *const material, const glm::mat3 &view)
			: center(center), radius(radius)
		{	
			setMaterial(material);
			setViewMatrix(view);
		}

		Intersection intersect(const Ray &ray) override
		{	
			Intersection result;

			vec3 oc = ray.origin - center;
			float a = dot(ray.direction, ray.direction);
			float b = 2.0f * dot(oc, ray.direction);
			float c = dot(oc, oc) - radius * radius;
			float discriminant = b * b - 4 * a * c;
			
			if (discriminant < 0.0f)
				return Intersection();
			
			float t1 = (-b - std::sqrt(discriminant)) / (2 * a);
			float t2 = (-b + std::sqrt(discriminant)) / (2 * a);

			if (t1 > RAY_T_MIN && t1 < 1.0e30f){
				result.normal = normalize(vec3(ray.origin + t1 * ray.direction - center));
				result.distance = t1;
				result.obj = this;
			}
			if (t2 > RAY_T_MIN && t2 < 1.0e30f){

			    if(result.distance != -1)
					result.tmax = t2;
				else{
					result.normal = normalize(vec3(ray.origin + t2 * ray.direction - center));
					result.distance = t2;
					result.tmax = t2;
					result.obj = this;
				}
			}
			return result;
		}

	private:
		vec3 center = vec3(0);
		float radius = 1.0f;
	};
} 

#endif 
