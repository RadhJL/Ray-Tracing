#ifndef __ISICG_ISIR_SPHERE_LIGHT__
#define __ISICG_ISIR_SPHERE_LIGHT__

#include "light.hpp"

namespace ISICG_ISIR
{	
	class SphereLight: public Light
	{
	public:
		SphereLight() = default;

		SphereLight(const vec3 &color, const float &intensity, const mat3 &to_world, const vec3& position)
		{	
			this->setColor(color);
			this->setIntensity(intensity);
			this->setType (0);	
			this->setToWorld(to_world);
			this->position = /*to_world * */position;
		}

		vec3 getPosition() override
		{
			return position;
		}
		
		vec3 getDirection() override
		{
			return position;	
		};

		 float getIntensity(const vec3 &pos) override
		 {
			float r = length(pos - position);
			return intensity / (4 * float(PI) * r*r);
		 }

		vec3 position;

	};
} 

#endif 
