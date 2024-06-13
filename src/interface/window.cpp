#include "window.hpp"

#include "error.hpp"

#include "graphics-include.hpp"

#include <stdexcept>
#include <utility>

namespace Interface {
	
	Window::Window(const int width, const int height, const std::string& title) : 
		handle([&]() {
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_RESIZABLE, false);
			return Window::UniqueWindow(glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr), glfwDestroyWindow); 
		}()) {
		if (!handle) {
			throw std::runtime_error(FormatErrorStringGLFW("Could not create GLFWwindow."));
		}
		glfwMakeContextCurrent(handle.get());

		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
			throw std::runtime_error("GLAD failed");
		}

		glViewport(0, 0, width, height);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_PROGRAM_POINT_SIZE);
	}

	bool Window::ShouldClose() const {
		return glfwWindowShouldClose(handle.get());
	}

	void Window::Clear(const glm::vec4 normalColor) {
		glClearColor(normalColor.r, normalColor.g, normalColor.b, normalColor.a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::Present() {
		glfwSwapBuffers(handle.get());
	}

	GLFWwindow* Window::Handle() const {
		return handle.get();
	}
}
