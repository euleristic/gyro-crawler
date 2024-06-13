#include "error.hpp"

#include "graphics-include.hpp"

#include <format>
#include <utility>

namespace Interface {
	std::string FormatErrorStringGLFW(const std::string_view prefix) {
		auto [code, description] = []() {
			const char* description;
			auto code = glfwGetError(&description);
			return std::make_pair(code, description);
		}();
		return std::format("{}\nError Code: {}\nError message: {}", prefix, code, description);
	}

	std::string FormatErrorStringGL(const std::string_view prefix) {
		auto code = OpenGLError();
		return std::format("{}\nError Code: {}", prefix, code ? *code : "None");
	}

#define ERROR_ELEMS \
X(GL_INVALID_ENUM) \
X(GL_INVALID_VALUE) \
X(GL_INVALID_OPERATION) \
X(GL_INVALID_FRAMEBUFFER_OPERATION) \
X(GL_OUT_OF_MEMORY) \
X(GL_STACK_UNDERFLOW) \
X(GL_STACK_OVERFLOW) 
		
#define X(name) \
case name: return #name;

	std::optional<std::string> OpenGLError() {
		if (auto error = glGetError()) {
			switch (error) {
				ERROR_ELEMS
			default:
				std::unreachable();
			}
		}
		else
			return {};
	}
}
