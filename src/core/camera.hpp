#ifndef __ISICG_ISIR_CAMERA__
#define __ISICG_ISIR_CAMERA__

#include "core/ray.hpp"
#include "core/defines.hpp"

namespace ISICG_ISIR
{
	class Camera
	{
	public:
		
		Camera () = default;

		Camera(const vec3 &origin,const vec3 &target,const vec3 &upguide,const float &fov,const float &aspectRatio)
			: origin(origin)
		{
			forward = normalize(target - origin);
			right = normalize(cross(forward, upguide));
			up = cross( right,forward);
			h = tan(fov);
			w = h * aspectRatio;
			view = glm::mat3(right,up,forward);
		}

		Ray generateRay(const vec3 &point) const
		{
			vec3 direction = forward + point.x * w * right + point.y * h * up;
			return Ray(origin, normalize(direction));
		}

		glm::mat3 getView()
		{
			return view;
		}

	private:
		vec3 origin;
		vec3 forward;
		vec3 up ;
		vec3 right;
		float h, w;
		glm::mat3 view;
	};
} 

#endif 
