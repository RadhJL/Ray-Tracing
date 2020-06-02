#ifndef ____ISICG_ISIR_DEFINES__
#define ____ISICG_ISIR_DEFINES__

#include "glm/glm.hpp"

namespace ISICG_ISIR
{
	using uint = unsigned int;
	using uchar = unsigned char;

	using Vec3f = glm::vec3;
	using Vec4f = glm::vec4;
	using Vec3u = glm::uvec3;
	using vec3 = glm::vec3;
	using vec2 = glm::vec2;
	using vec4 = glm::vec4;
	using mat3 = glm::mat3;
	const Vec3f VEC3F_ZERO = Vec3f(0.f, 0.f, 0.f);
	constexpr auto PI = 3.14159265359;
	constexpr auto MAX = std::numeric_limits<float>::max();
	constexpr auto MIN = std::numeric_limits<float>::min();

} 

#endif 
