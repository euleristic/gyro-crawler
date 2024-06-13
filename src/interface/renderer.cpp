#include "renderer.hpp"

#include "graphics-include.hpp"

#include <stdexcept>

namespace Interface {
	
	Renderer::Renderer() {
	}
	
	void Renderer::Clear() {
		
		glClear(GL_COLOR_BUFFER_BIT);
	}
}
