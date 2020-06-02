#ifndef __ISICG_ISIR_LIGHT__
#define __ISICG_ISIR_LIGHT__

namespace ISICG_ISIR
{	
	class Light
	{
	public:

		void setColor(const vec3 &color)
		{
		  this->color = color;
		}

		void setIntensity(const float &intensity)
		{
		  this->intensity = intensity;
		}

		void setToWorld(const mat3 &to_world)
		{
		  this->to_world = to_world;
		}

		void setType(const int &type)
		{
		  this->type = type;
		}
		
		virtual vec3 getPosition() =0;
		virtual vec3 getDirection() =0;
		virtual float getIntensity(const vec3 &pos) =0;

		vec3 color;
		float intensity;
		mat3 to_world;
		int type;
	};
} 

#endif 
