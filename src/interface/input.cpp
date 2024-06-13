#include "input.hpp"

#include <utility>

#include "window.hpp"

#include "graphics-include.hpp"

namespace Interface {

	Input::Input(Window& window) : window(window) {}

	void Input::Update() {
		lastKeyState = std::exchange(currentKeyState, NextKeyState());
		lastMouseButtonState = std::exchange(currentMouseButtonState, NextMouseButtonState());
	}

	bool Input::Down(const Key key) const {
		return !lastKeyState[static_cast<size_t>(key)] && currentKeyState[static_cast<size_t>(key)];
	}

	bool Input::Down(const MouseButton mouseButton) const {
		return !lastKeyState[static_cast<size_t>(mouseButton)] && currentKeyState[static_cast<size_t>(mouseButton)];
	}

	bool Input::Held(const Key key) const {
		return currentKeyState[static_cast<size_t>(key)];
	}

	bool Input::Held(const MouseButton mouseButton) const {
		return currentKeyState[static_cast<size_t>(mouseButton)];
	}

	bool Input::Up(const Key key) const {
		return lastKeyState[static_cast<size_t>(key)] && !currentKeyState[static_cast<size_t>(key)];
	}

	bool Input::Up(const MouseButton mouseButton) const {
		return lastKeyState[static_cast<size_t>(mouseButton)] && !currentKeyState[static_cast<size_t>(mouseButton)];
	}

	Input::MouseButtonState Input::NextMouseButtonState() const {
		MouseButtonState state{};

		state.set(static_cast<size_t>(MouseButton::LEFT),   glfwGetMouseButton(window.Handle(), GLFW_MOUSE_BUTTON_LEFT)   == GLFW_PRESS);
		state.set(static_cast<size_t>(MouseButton::MIDDLE), glfwGetMouseButton(window.Handle(), GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS);
		state.set(static_cast<size_t>(MouseButton::RIGHT),  glfwGetMouseButton(window.Handle(), GLFW_MOUSE_BUTTON_RIGHT)  == GLFW_PRESS);

		return state;
	}

#	define NUMBER_ELEMS \
	X(1) \
	X(2) \
	X(3) \
	X(4) \
	X(5) \
	X(6) \
	X(7) \
	X(8) \
	X(9) \
	X(0) \

#	define SIMPLE_KEY_ELEMS \
	X(Q) \
	X(W) \
	X(E) \
	X(R) \
	X(T) \
	X(Y) \
	X(U) \
	X(I) \
	X(O) \
	X(P) \
	X(A) \
	X(S) \
	X(D) \
	X(F) \
	X(G) \
	X(H) \
	X(J) \
	X(K) \
	X(L) \
	X(Z) \
	X(X) \
	X(C) \
	X(V) \
	X(B) \
	X(N) \
	X(M) \
	X(ESCAPE) \
	X(LEFT_CONTROL) \
	X(LEFT_SHIFT) \
	X(LEFT_ALT) \
	X(SPACE) \
	X(ENTER) \
	X(UP) \
	X(LEFT) \
	X(DOWN) \
	X(RIGHT) 

	Input::KeyState Input::NextKeyState() const {
		KeyState state{};
		
#		define X(key) \
		state.set(static_cast<size_t>(Key::K##key), glfwGetKey(window.Handle(), GLFW_KEY_##key) == GLFW_PRESS);

		NUMBER_ELEMS

#		undef X
#		define X(key) \
		state.set(static_cast<size_t>(Key::key), glfwGetKey(window.Handle(), GLFW_KEY_##key) == GLFW_PRESS);

		SIMPLE_KEY_ELEMS

#		undef X

		return state;
	}
}
