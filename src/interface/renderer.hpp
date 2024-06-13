#ifndef RENDERER_HPP
#define RENDERER_HPP

namespace Interface {
	
	class Renderer {
	public:
		Renderer();
		
		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;

		void Clear();
	private:
		
	};
}

#endif // RENDERER_HPP
