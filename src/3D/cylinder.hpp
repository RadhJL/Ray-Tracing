#ifndef __ISICG_ISIR_Cylinder__
#define __ISICG_ISIR_Cylinder__

#include "aObject3D.hpp"
#include "materials/aMaterial.hpp"

namespace ISICG_ISIR
{
	class Cylinder : public AObject3D
	{
	public:

		Cylinder() = default;
		
		Cylinder(const vec3 &in, const vec3 &out, const float &radius,
				 AMaterial *const material, const glm::mat3 &view)
			: in(in), out(out), radius(radius)
		{
			setMaterial(material);
			setViewMatrix(view);
		}

		Intersection intersect(const Ray& ray){
			vec3 vRayNorm = ray.direction;
			
			vec3 A = in;	
			vec3 B = out;		

			vec3 AB		= B - A;						
			vec3	AO		= ray.origin - A;				
			vec3	AOxAB	= cross(AO, AB);		
			vec3	VxAB 	= cross(vRayNorm, AB);	
			float	ab2		= dot(AB,AB);						
  			float	a		= dot(VxAB,VxAB);					
  			float	b		= 2 * dot(VxAB,AOxAB);
			float	c		= dot(AOxAB,AOxAB) - (radius * radius * ab2);
  			float	d		= b * b - 4 * a * c;					

  			if (d < 0) return Intersection();

			float t = (-b - sqrt(d)) / (2 * a);
			float t1 = (-b + sqrt(d)) / (2 * a);

  			if(t < 0) return inSphereCap(ray, sqrt(dot(A,ray.origin)) < sqrt(dot(B,ray.origin)) ? A : B ,radius*radius);

			vec3 iPos 	= vRayNorm * t + ray.origin;	
			vec3 iPosLen	= iPos - A;						
			float	tLimit	= dot(iPosLen,AB) / ab2;				

			if(tLimit >= 0 && tLimit <= 1)	{
				vec3 q = iPos;
				vec3 pa = B;
				vec3 va = normalize(AB);
				vec3 n = ( (q - pa) -  dot(va,(q -pa)) * va) ;
				return Intersection(n, t, t1, this);
			}
			else if(tLimit < 0)				return inSphereCap(ray,A,radius * radius); 
			else if(tLimit > 1)				return inSphereCap(ray,B,radius * radius); 

			return Intersection();
		}

	Intersection inSphereCap(const Ray& ray,const vec3& spherePos,const float& radiusSqr){

		vec3 vRayNorm = ray.direction;
		vec3 vRayToCenter = spherePos - ray.origin;
		float	tProj = dot(vRayToCenter,vRayNorm);

		float oppLenSqr = dot(vRayToCenter,vRayToCenter) - (tProj*tProj); 

		if(oppLenSqr > radiusSqr) return Intersection();
		if(oppLenSqr == radiusSqr){
			vec3 n = normalize(ray.origin + ray.direction * tProj - spherePos);
			return Intersection(n, tProj, tProj , this);
		}

		float oLen = sqrt(radiusSqr - oppLenSqr), 
			t0 = tProj - oLen,
			t1 = tProj + oLen;
		if(t1 < t0){ float tmp = t0; t0 = t1; t1 = tmp; } 

		vec3 iPos = vRayNorm * t0 + ray.origin;
				
		vec3 n = normalize(iPos - spherePos);
		return Intersection(n, t0, t1, this);
	}

	private:
		vec3 in;
		vec3 out;
		float radius;
	};
} 

#endif
