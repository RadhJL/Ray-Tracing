#ifndef __ISICG_ISIR_MICROFACET__
#define __ISICG_ISIR_MICROFACET__

#include<vector>
#include"../core/intersection.hpp"
#include"../core/ray.hpp"
#include"../light/light.hpp"
#include"materials/aMaterial.hpp"

namespace ISICG_ISIR
{	
	class Microfacet
	{
	public:
		 
		 Microfacet() = default;
		 
		 static Vec3f Brdf_shade(AMaterial *m, const Ray &ray, const Intersection &pos, Light* &light)
		 {
			
			Vec3f n = pos.normal;
			Vec3f p = ray.origin + pos.distance * ray.direction;
			Vec3f v = -ray.direction;
			Vec3f diffuse = m->getDiffuse(p);
			Vec3f specular = m->getSpecular(p);
			float kd = m->getKd(p);
			float ks = m->getKs(p);
			float r = m->getRoughness(p);
				  r = r*r;
			float ior= m->getIor(p); 
			float f0 = std::pow((1.0f-ior)/(1.0f+ior),2.0f) + 0.05f; 
			vec3 specular_coef;
			vec3  diffuse_coef;
		  
			vec3 l;
			if(light->type == 0 ||light->type == 2) // light with position
				l = normalize(light->getPosition() - p);
			else // light with direction
				l = normalize(light->getDirection());

			vec3  h = normalize (v + l);

			float nov = saturate(dot(n, v));
			float nol = saturate(dot(n, l));
			float noh = saturate(dot(n, h));
			float voh = saturate(dot(v, h));

			if (nol > 0) {
				
				float D = D_ggx(noh,r);
				//float D = D_beckmann(noh,r);
				float G = G_smith(nov,nol,r,2); //0 => ggx, 1 => beckmann, else shlick_beckmann  
				//float G1 = G_cook_torrence(nov,nol,noh,voh);
				float F = F_cook_torrence(voh,f0);
				//float F = F_schlick(voh,f0);

				specular_coef = light->getIntensity(p) * light->color *  G * F * D / saturate(4.0f*nol*nov + 0.05f);
				diffuse_coef  = light->getIntensity(p) * light->color * nol;
			}

				return ( /*kd * */ diffuse_coef * diffuse )  +( /*ks **/ specular_coef * specular);
		 }
	
		static float D_blinn_phong(const float &noh,const float& a)
		{
			float a2 = a*a;
			float power = 2.0f/a2 - 2.0f;
			return (1/PI*a2)* std::pow(noh,power);
		}

		static float D_beckmann(const float& noh ,const float& a)
		{
			float noh2 = noh * noh;
			float noh4 = noh2 * noh2;
			float a2 = a*a;
			float power = ((noh2 - 1.0f)/(a2*noh2));
			return (1/(PI*a2*noh4))*std::exp(power);
		}

		static float D_ggx(const float& noh ,const float& a)
		{

			float noh2 = noh * noh;
			float a2 = a*a;
			float power = noh2*(a2 - 1.0f) + 1.0f;
			return a2/(PI*power*power);
		}
		
		static float G_implicit(const float& nov, const float& nol)
		{
			 return nol*nov;		
		}

		static float G_neumann(const float& nov, const float& nol)
		{
			return G_implicit(nol,nov)/std::max(nol,nov);
		}

		static float G_cook_torrence(const float& nov, const float& nol,const float& noh, const float& voh)
		{
			float compare = (2.0 * noh)/voh;
			return std::min(float(1),std::min(compare*nov,compare*nol));
		}
		
		static float G_kelemen(const float& nov, const float& nol,const float& noh, const float& voh)
		{
			return (nol*nov)/(voh*voh);
		}
		
		static float G_smith(const const float& nov, const float& nol, const float& a,const uint& type)
		{
			
			if(type == 0)
				return G_beckmann(nol,a)*G_beckmann(nov,a);
		
			else if (type == 1)
			  return G_ggx(nol,a)*G_ggx(nov,a);
			
			return G_schlick_beckmann(nol,a)*G_schlick_beckmann(nov,a);
		}

		static float g_beckmann(const float& nov, const float& a)
		{
			float nov2 = nov * nov;
			float deno = a * std::sqrt(1.0f-nov2);
			return nov/deno;
		}

		static float G_beckmann(const float& nov, const float& a)
		{

			float c = g_beckmann(nov,a);
			if (c >= 1.6f)
				return 1;
			float c2= c*c;
			float d = 3.535f*c+2.181f*c2;
			float deno = 1.f+2.276f*c+2.577f*c2;
			return d/deno;
		}

		static float G_ggx(const float& nov, const float& a)
		{
			float nov2= nov * nov;
			float a2 = a*a;
			float d = 2.0f * nov;
			float deno = nov + std::sqrt(a2 + (1.0f-a2)*nov2);
			return d/deno;
		}
		
		//deprecated ?
		static float G_schlick_beckmann(const float& nov, const float& a)
		{
			float k= a * std::sqrt(2.f/PI);
			float nov2= nov * nov;
			return nov/(nov*(1.0f-k)+k);
		}

		static float F_schlick(const float& voh, const float& f0)
		{
			return f0 + (1.0f - f0) * std::pow(1.0f - voh,5.0f);
		}
		
		static float F_cook_torrence(const float& voh, const float& f0)
		{
			float n = (1.0f + std::sqrt(f0))/(1.0f - std::sqrt(f0));
			float c = voh;
			float g = std::sqrt(n*n+c*c-1.0f);
			float first = 0.5f * ((g-c)/(g+c)) * ((g-c)/(g+c));
			float second = 1.0f + std::pow((((g+c)*c-1.0f)/((g-c)*c+1.0f)),2.0f);
			return first * second;
		}

		static float saturate (const float& f)
		{
			return clamp(f, 0.0f, 1.0f);			
		}

		static constexpr const float& clamp( const float& v, const float& lo, const float& hi )
		{
			assert( !(hi < lo) );
			return (v < lo) ? lo : (hi < v) ? hi : v;
		}

		// for importance smapling	
		static Vec3f ImportanceSampleGGX(glm::vec2 Xi, float Roughness, Vec3f N, const Intersection& pos) {

			  float a = Roughness * Roughness;
			  float Phi = 2 * PI * Xi.x;
			  float CosTheta = sqrt((1.0 - Xi.y) / (1.0 + (a*a - 1.0) * Xi.y));
			  float SinTheta = sqrt(1 - CosTheta * CosTheta);
			  Vec3f H;
			  H.x = SinTheta * cos(Phi);
			  H.y = SinTheta * sin(Phi);
			  H.z = CosTheta;
			  return pos.obj->toView(H);
		  }
			
		static uint reversebits(uint bits) 
		{ 
	  	    bits = (bits << 16u) | (bits >> 16u);
			bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
			bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
			bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
			bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
			return float(bits) * 2.3283064365386963e-10; 
		}
		
		static glm::vec2 Hammersley(const uint &i,const uint &N) 
		{
			return glm::vec2(float(i) / float(N), reversebits(i));
		}

	};
} 

#endif 
