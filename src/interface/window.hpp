#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <memory>

#include <glm/glm.hpp>

class GLFWwindow;

namespace Interface {

	class Window {
		using UniqueWindow = std::unique_ptr<GLFWwindow, void(*)(GLFWwindow*)>;
	public:
		Window() = default;
		Window(const int width, const int height, const std::string& title);
		
		// Copying is not allowed (for now), it could make sense.
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		
		bool ShouldClose() const;
		void Clear(const glm::vec4 normalColor);
		void Present();
		
		GLFWwindow* Handle() const;
	private:
		UniqueWindow handle;
	};
}

#endif // !WINDOW_HPP
