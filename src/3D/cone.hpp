#ifndef __ISICG_ISIR_CONE__
#define __ISICG_ISIR_CONE__

#include <vector>
#include "aObject3D.hpp"
#include "materials/aMaterial.hpp"

namespace ISICG_ISIR
{
	class Cone : public AObject3D
	{
	public:
		Cone() = default;
		Cone(const vec3 &center, const float &radius, const float& height, AMaterial *const material, const glm::mat3 &view)
			: center(center), radius(radius), height(height)
		{	
			setMaterial(material);
			setViewMatrix(view);
		}

		Intersection intersect(const Ray &ray) override
		{	
 		  Intersection result;
		
		  float radius2 = radius * radius;
		  vec3 pos = ray.origin;
		  vec3 dir = ray.direction;
		
		  float A = pos.x - center.x;
		  float B = pos.z - center.z;
		  float D = height - pos.y + center.y;
		
		  float tan = (radius / height) * (radius / height);
		
		  float a = (dir.x * dir.x) + (dir.z * dir.z) - (tan * (dir.y * dir.y));
		  float b = (2 * A * dir.x) + (2 * B * dir.z) + (2 * tan * D * dir.y);
		  float c = (A * A) + (B * B) - (tan * (D * D));
		
		  float delta = b * b - 4 * (a * c);
		  if (delta < 0.0) return result;
		
		  float t1 = (-b - sqrt(delta)) / (2 * a);
		  float t2 = (-b + sqrt(delta)) / (2 * a);
		  float t;
		
		  if (t1 > t2) t = t2;
		  else t = t1;
		
		  if (t < 0)
		    return result;
		
		  float r = pos.y + t * dir.y;
		
		  if ((r > center.y) && (r < center.y + height)) {
		     vec3 p = pos  + t * dir;
			 float tmp = sqrt((p.x-center.x)*(p.x-center.x) + (p.z-center.z)*(p.z-center.z));
			 vec3 n = vec3 (p.x-center.x, tmp*(radius/height), p.z-center.z);
			 result.distance = t;
		     result.obj = this;
			 result.normal = normalize(n);
			 result.tmax = t2;
			 return result;
		  }
		
		  return result;
		}

	private:
		vec3 center;
		float radius;
		float height;
	};
} 

#endif 
