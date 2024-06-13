#ifndef SHADER_SOURCE_HPP
#define SHADER_SOURCE_HPP

#include "resources/stars-vertex-shader.glsl.hpp"
#include "resources/stars-fragment-shader.glsl.hpp"

namespace ShaderSource {
	constexpr const char STARS_VERTEX[] = { EMBED_STARS_VERTEX_SHADER_GLSL, '\0' };
	constexpr const char STARS_FRAGMENT[] = { EMBED_STARS_FRAGMENT_SHADER_GLSL, '\0' };
}

#endif // !SHADER_SOURCE_HPP
