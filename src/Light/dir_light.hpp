#ifndef __ISICG_ISIR_DIR_LIGHT__
#define __ISICG_ISIR_DIR_LIGHT__

#include "light.hpp"

namespace ISICG_ISIR
{	
	class DirLight: public Light
	{
	public:
		
		DirLight() = default;

		DirLight(const vec3 &color, const float &intensity, const mat3 &to_world, const vec3& direction)
		{
			this->setColor(color);
			this->setIntensity(intensity);
			this->setType (1);	
			this->setToWorld(to_world);
			this->direction = /*to_world **/ direction;
			
		}

		vec3 getPosition() override
		{
			return direction;
		}
		
		vec3 getDirection() override
		{
			return direction;	
		};
	    
		float getIntensity(const vec3 &pos) override
		{
			return intensity;
		}

		vec3 direction;
	};
} 

#endif 
