#ifndef __ISICG_ISIR_POINT_LIGHT__
#define __ISICG_ISIR_POINT_LIGHT__

#include "light.hpp"

namespace ISICG_ISIR
{	
	class PointLight: public Light
	{
	public:
		PointLight() = default;

		PointLight(const vec3 &color, const float &intensity, const mat3 &to_world, const vec3& position)
		{	
			this->setColor(color);
			this->setIntensity(intensity);
			this->setType (2);	
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
			return intensity;
		 }

		vec3 position;

	};
} 

#endif 
