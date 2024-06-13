#include "shader.hpp"
#include "graphics-include.hpp"

#include <string>
#include <stdexcept>
#include <format>

namespace Interface {
	
	template class Shader<ShaderType::VERTEX>;
	template class Shader<ShaderType::FRAGMENT>;

	constexpr GLenum ToGLenum(ShaderType type) {
		switch (type) {
			case ShaderType::VERTEX:   return GL_VERTEX_SHADER;
			case ShaderType::FRAGMENT: return GL_FRAGMENT_SHADER;
			default: std::unreachable();
		}
	}

	template<ShaderType T> Shader<T>::Shader(const std::string_view source) :
		handle(glCreateShader(ToGLenum(TYPE)), glDeleteShader) {
		{
			// string_view is not necessarily null-terminated, but this should not incur much performance loss while being more correct.
			const auto data = source.data();
			const auto length = static_cast<GLint>(source.length());
			glShaderSource(*handle, 1, &data, &length); 
		}

		glCompileShader(*handle);
		{
			GLint success; // No need to initialize
			glGetShaderiv(*handle, GL_COMPILE_STATUS, &success);
			if (success == GL_FALSE) {
				GLint logSize;
				glGetShaderiv(*handle, GL_INFO_LOG_LENGTH, &logSize);
				std::string log(logSize - 1, {});
				glGetShaderInfoLog(*handle, logSize, nullptr, log.data());
				log.shrink_to_fit();
				throw std::runtime_error(std::format("Shader compilation of type {} failed: \n{}\nSource:\n{}\n",
					TYPE == ShaderType::VERTEX ? "VERTEX" : "FRAGMENT", log, source));
			}
		}
	}

	template<ShaderType T> unsigned int Shader<T>::Key() const {
		return *handle;	
	}
}
