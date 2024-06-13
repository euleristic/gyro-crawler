#include "glfw-owner.hpp"

#include "error.hpp"

#include "graphics-include.hpp"

#include <stdexcept>


namespace Interface {
	void GLAPIENTRY MessageCallBack(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
		(void)source;
		(void)type;
		(void)id;
		(void)severity;
		(void)length;
		(void)message;
		(void)userParam;
		throw std::runtime_error("Something went wrong with openGL");
	}

	GLFWOwner::GLFWOwner() {
		if (!glfwInit()) {
			throw std::runtime_error(FormatErrorStringGLFW("Could not initialize GLFW."));
		}
	}

	GLFWOwner::~GLFWOwner() {
		if (!movedFrom) {
			glfwTerminate();
		}
	}

	GLFWOwner::GLFWOwner(GLFWOwner&& other) {
		other.movedFrom = true;
	}

	GLFWOwner& GLFWOwner::operator=(GLFWOwner&& rhs) {
		rhs.movedFrom = true;
		return *this;
	}
}
