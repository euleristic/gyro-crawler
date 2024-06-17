#include "interface/interface.hpp"

#include "stars.hpp"

#include <stdexcept>
#include <cstdint>

#include <chrono>

#include <iostream>

constexpr size_t WINDOW_WIDTH = 640, WINDOW_HEIGHT = 480;
constexpr glm::mat3 PROJECTION = {
	{ static_cast<float>(WINDOW_HEIGHT) / static_cast<float>(WINDOW_WIDTH), 0.0f, 0.0 },
	{ 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f }
};

constexpr auto viewPortWidth  = WINDOW_WIDTH;
constexpr auto viewPortHeight = WINDOW_HEIGHT;

constexpr unsigned int apparentPixelWidth = 4;
constexpr float apparentPixelsPerGameUnit = 16.0f;

constexpr glm::mat3 apparentPixelToClipSpace = {
	static_cast<float>(apparentPixelWidth) / (static_cast<float>(viewPortWidth) / 2.0f),  0.0f, 0.0f,
	0.0f, static_cast<float>(apparentPixelWidth) / (static_cast<float>(viewPortHeight) / 2.0f), 0.0f,
	0.0f, 0.0f, 1.0f
};

int main() {
	try {
		Interface::GLFWOwner loadedLib;
		Interface::Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "GyroCrawler");
		Interface::EventHandler eventHandler;
		Interface::Renderer renderer;
		
		Interface::Input input(window);
		Stars stars(input, 1.0f, 10);

		auto lastFrame = std::chrono::steady_clock::now();
		std::chrono::duration<float> deltaTime{};

		
		while (!window.ShouldClose()) {
			{
				auto now = std::chrono::steady_clock::now();
				deltaTime = now - lastFrame;
				lastFrame = now;
			}

			eventHandler.Poll();
			eventHandler.Dispatch();
			input.Update();
			if (input.Down(Interface::Input::Key::ESCAPE)) break;

			// Updates
			stars.Update(deltaTime.count());

			// Draws
			window.Clear(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

			stars.Draw(apparentPixelToClipSpace, apparentPixelsPerGameUnit, apparentPixelWidth);

			window.Present();
		}
		while (auto err = Interface::OpenGLError()) {
			std::cerr << *err << '\n';
		}
	}
	catch (const std::runtime_error& er) {
		std::cerr << er.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
