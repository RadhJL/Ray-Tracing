#ifndef __ISICG_ISIR_RAY__
#define __ISICG_ISIR_RAY__

#include "defines.hpp"

namespace ISICG_ISIR
{
	class Ray
	{
	public:
		
		Ray() = default;

		Ray(const vec3 &origin, const vec3 &direction)
			: origin(origin), direction(direction)
		{
		}

		vec3 origin;
		vec3 direction;
	};
} 

#endif
