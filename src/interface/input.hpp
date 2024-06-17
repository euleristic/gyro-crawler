#ifndef INPUT_HPP
#define INPUT_HPP

#include <bitset>

namespace Interface {

	class Window;

	class Input {
	public:
		enum class Key {
			K1, K2, K3, K4, K5, K6, K7, K8, K9, K0,
			Q, W, E, R, T, Y, U, I, O, P,
			 A, S, D, F, G, H, J, K, L,
			  Z, X, C, V, B, N, M,
			ESCAPE, LEFT_CONTROL, LEFT_SHIFT, LEFT_ALT, SPACE, ENTER, UP, LEFT, DOWN, RIGHT,
			COUNT
		};

		enum class MouseButton {
			LEFT, MIDDLE, RIGHT, COUNT
		};

		Input(Window& window);

		void Update();
		
		[[nodiscard]] bool Down(const Key key) const;
		[[nodiscard]] bool Down(const MouseButton button) const;
		[[nodiscard]] bool Held(const Key key) const;
		[[nodiscard]] bool Held(const MouseButton button) const;
		[[nodiscard]] bool Up(const Key key) const;
		[[nodiscard]] bool Up(const MouseButton button) const;

	private:
		Window& window;
		using KeyState = std::bitset<static_cast<size_t>(Key::COUNT)>;
		KeyState NextKeyState() const;
		KeyState lastKeyState;
		KeyState currentKeyState;

		using MouseButtonState = std::bitset<static_cast<size_t>(MouseButton::COUNT)>;
		MouseButtonState NextMouseButtonState() const;
		MouseButtonState lastMouseButtonState;
		MouseButtonState currentMouseButtonState;
	};
}

#endif // !INPUT_HPP
