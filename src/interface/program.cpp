#include "program.hpp"

#include "graphics-include.hpp"

#include <stdexcept>
#include <format>
#include <string> 

namespace Interface {

	Program::BoundToken::BoundToken(const GLuint key) : bound(BindType(true,
#		ifndef NDEBUG
			[](const bool bound) {
				if (bound)
					glUseProgram(0u);
			}
#		else // NDEBUG
			euleristic::NoOp<bool>
#		endif // !NDEBUG
		)) {
		glUseProgram(key);
	}

	Program::Program(const VertexShader& vertexShader, const FragmentShader& fragmentShader) :
		handle(glCreateProgram(), glDeleteProgram) {

		glAttachShader(*handle, vertexShader.Key());
		glAttachShader(*handle, fragmentShader.Key());

		// Setup program io

		glLinkProgram(*handle);

		{
			GLint success; // No need to initialize
			glGetProgramiv(*handle, GL_LINK_STATUS, &success);
			if (success == GL_FALSE) {
				GLint logSize;
				glGetProgramiv(*handle, GL_INFO_LOG_LENGTH, &logSize);
				std::string log(logSize - 1, {});
				glGetProgramInfoLog(*handle, logSize, nullptr, log.data());
				log.shrink_to_fit();
				throw std::runtime_error(std::format("Program linking failed: {}", log));
			}
		}

		glDetachShader(*handle, vertexShader.Key());
		glDetachShader(*handle, fragmentShader.Key());
	}

	unsigned int Program::Key() const {
		return *handle;
	}

	Program::BoundToken Program::Bind() {
		return BoundToken(Key());
	}

	template <Program::DrawingMode mode>
	Program::BoundToken Program::Run(VertexArray& vertexArray, const GLint first, const GLsizei count) {
		return Run<mode>(vertexArray, first, count, Bind());
	}

#	define DRAWING_MODES \
	X(POINTS) \
	X(LINE_STRIP) \
	X(LINE_LOOP) \
	X(LINES) \
	X(LINE_STRIP_ADJACENCY) \
	X(LINES_ADJACENCY) \
	X(TRIANGLE_STRIP) \
	X(TRIANGLE_FAN) \
	X(TRIANGLES) \
	X(TRIANGLE_STRIP_ADJACENCY) \
	X(TRIANGLES_ADJACENCY) 

	template <Program::DrawingMode mode>
	consteval GLenum Symbol() {
		switch (mode) {

#			define X(name) \
			case Program::DrawingMode::name: return GL_##name;
			DRAWING_MODES
#			undef X
		}
	}

	template <Program::DrawingMode mode>
	Program::BoundToken Program::Run(VertexArray& vertexArray, const GLint first, const GLsizei count, BoundToken&& programBoundToken) {
		auto boundToken = vertexArray.Bind();
		glDrawArrays(Symbol<mode>(), first, count);
		return programBoundToken;
	}

#	define X(name) \
	template Program::BoundToken Program::Run<Program::DrawingMode::name>(VertexArray&, const GLint, const GLsizei); \
	template Program::BoundToken Program::Run<Program::DrawingMode::name>(VertexArray&, const GLint, const GLsizei, BoundToken&&);
	DRAWING_MODES
#	undef X
}
