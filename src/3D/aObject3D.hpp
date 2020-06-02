#ifndef __ISICG_ISIR_A_OBJECT_3D__
#define __ISICG_ISIR_A_OBJECT_3D__

#include "materials/aMaterial.hpp"
#include "core/intersection.hpp"
#include "core/defines.hpp"

namespace ISICG_ISIR
{
	class AObject3D
	{
	public:
		
		void setMaterial(AMaterial *const material)
		{
			this->material = material;
		}
		
		void setViewMatrix(const glm::mat3 &w)
		{
			this->view = w;
		}
		
		vec3 toView(const vec3 &v)
		{
			float x = v.x*view[0][0] + v.y*view[0][1]+ v.z*view[0][2]; 
			float y = v.x*view[1][0]+ v.y*view[1][1]+ v.z*view[1][2];
			float z = v.x*view[2][0]+ v.y*view[2][1]+ v.z*view[2][2];
			return vec3(x,y,z);			
		}

		virtual Intersection intersect(const Ray &ray) = 0;

		AMaterial *material = nullptr;
		glm::mat3 view;
	};
} 

#endif 
