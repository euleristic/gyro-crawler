#include "uniform.hpp"

#include "graphics-include.hpp"
#include "error.hpp"

#include "glm/gtc/type_ptr.hpp"

#include <span>
#include <format>

namespace Interface {

	template <UniformType T>
	Uniform<T>::Uniform(Program& program, const char* identifier) :
		program(program), location(glGetUniformLocation(program.Key(), identifier)) {
		if (location == -1) {
			throw std::runtime_error(FormatErrorStringGL(std::format("Get uniform location for program={}, id={} failed.", program.Key(), identifier)));
		}
	}

	template <UniformType T>
	Program::BoundToken Uniform<T>::Set(const T value) {
		return Set(value, program.Bind());
	}

	template <UniformType T>
	Program::BoundToken Uniform<T>::Set(const T value, Program::BoundToken&& token) {
		std::unreachable();
	}

#	define SCALAR_ELEMS \
	X(GLfloat, 1f) \
	X(GLint, 1i) \
	X(GLuint, 1ui) 

#	define VEC2_ELEMS \
	X(glm::vec2, 2f) \
	X(glm::ivec2, 2i) \
	X(glm::uvec2, 2ui) 

#	define VEC3_ELEMS \
	X(glm::vec3, 3f) \
	X(glm::ivec3, 3i) \
	X(glm::uvec3, 3ui) 

#	define VEC4_ELEMS \
	X(glm::vec4, 4f) \
	X(glm::ivec4, 4i) \
	X(glm::uvec4, 4ui) 

#	define MAT_ELEMS \
	X(glm::mat2, Matrix2f) \
	X(glm::mat3, Matrix3f) \
	X(glm::mat4, Matrix4f) \
	X(glm::mat2x3, Matrix2x3f) \
	X(glm::mat3x2, Matrix3x2f) \
	X(glm::mat2x4, Matrix2x4f) \
	X(glm::mat4x2, Matrix4x2f) \
	X(glm::mat4x3, Matrix4x3f) \
	X(glm::mat3x4, Matrix3x4f) 

#	define X(Type, postfix) \
	template <> \
	Program::BoundToken Uniform<Type>::Set(const Type value, Program::BoundToken&& token) { \
		glUniform##postfix(location, value); \
		return std::move(token); \
	}

	SCALAR_ELEMS

#	undef X

#	define X(Type, postfix) \
	template <> \
	Program::BoundToken Uniform<Type>::Set(const Type value, Program::BoundToken&& token) { \
		glUniform##postfix(location, value.x, value.y); \
		return std::move(token); \
	}

	VEC2_ELEMS

#	undef X

#	define X(Type, postfix) \
	template <> \
	Program::BoundToken Uniform<Type>::Set(const Type value, Program::BoundToken&& token) { \
		glUniform##postfix(location, value.x, value.y, value.z); \
		return std::move(token); \
	}

	VEC3_ELEMS

#	undef X

#	define X(Type, postfix) \
	template <> \
	Program::BoundToken Uniform<Type>::Set(const Type value, Program::BoundToken&& token) { \
		glUniform##postfix(location, value.x, value.y, value.z, value.w); \
		return std::move(token); \
	}

	VEC4_ELEMS

#	undef X

#	define X(Type, postfix) \
	template <> \
	Program::BoundToken Uniform<Type>::Set(const Type value, Program::BoundToken&& token) { \
		glUniform##postfix##v(location, 1, GL_FALSE, glm::value_ptr(value)); \
		return std::move(token); \
	}

	MAT_ELEMS

#	undef X

#	define X(Type, postfix) \
	template <> \
	Program::BoundToken Uniform<std::span<Type>>::Set(const std::span<Type> value, Program::BoundToken&& token) { \
		glUniform##postfix##v(location, value.size(), value.data()); \
		return std::move(token); \
	}

	SCALAR_ELEMS

#	undef X

#	define X(Type, postfix) \
	template <> \
	Program::BoundToken Uniform<std::span<Type>>::Set(const std::span<Type> value, Program::BoundToken&& token) { \
		glUniform##postfix##v(location, value.size(), glm::value_ptr(value.front())); \
		return std::move(token); \
	}

	VEC2_ELEMS
	VEC3_ELEMS
	VEC4_ELEMS

#	undef X

#	define X(Type, postfix) \
	template <> \
	Program::BoundToken Uniform<std::span<Type>>::Set(const std::span<Type> value, Program::BoundToken&& token) { \
		glUniform##postfix##v(location, value.size(), GL_FALSE, glm::value_ptr(value.front())); \
		return std::move(token); \
	}

	MAT_ELEMS

#	undef X

	// Instantiate the templates
#	define X(Type, _) \
	template class Uniform<Type>;

	SCALAR_ELEMS
	VEC2_ELEMS
	VEC3_ELEMS
	VEC4_ELEMS
	MAT_ELEMS

#	undef X

#	define X(Type, _) \
	template class Uniform<std::span<Type>>;

	SCALAR_ELEMS
	VEC2_ELEMS
	VEC3_ELEMS
	VEC4_ELEMS
	MAT_ELEMS

#	undef X
}
