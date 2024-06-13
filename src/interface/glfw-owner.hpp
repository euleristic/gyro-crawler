#ifndef GLFW_OWNER_HPP
#define GLFW_OWNER_HPP

namespace Interface {
	// This class provides an RAII wrapper for glfw initializing and destruction
	// There should never be more than one object of these, but I will not check it with any global state
	class GLFWOwner {
	public:
		GLFWOwner();
		GLFWOwner(GLFWOwner&& other);
		GLFWOwner& operator=(GLFWOwner&& rhs);	
		~GLFWOwner();

		GLFWOwner(GLFWOwner&) = delete;
		GLFWOwner& operator=(GLFWOwner&) = delete;
	private:
		bool movedFrom{};
	};
}

#endif // GLFW_OWNER_HPP
