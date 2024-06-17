#include "stars.hpp"

#include "shader-source.hpp"
#include <random>
#include <vector>
#include <span>

using namespace Interface;

Stars::Stars(Input& input, const float chebyshevRadius, const size_t count) : 
	input(input),
	program(Program(
		VertexShader(ShaderSource::STARS_VERTEX), 
		FragmentShader(ShaderSource::STARS_FRAGMENT)
	)),
	transform(glm::mat3(1.0f)),
	transformUniform(program, "transformUniform"),
	apparentPixelToClipSpaceUniform(program, "apparentPixelToClipSpaceUniform"),
	apparentPixelsPerGameUnitUniform(program, "apparentPixelsPerGameUnitUniform"),
	apparentPixelWidthUniform(program, "apparentPixelWidthUniform"),
	vertexArray(VertexArray::WithLayout<glm::vec2>()),
	vertexBuffer([chebyshevRadius, count]() {
		std::random_device device;
		std::default_random_engine engine(device());
		std::uniform_real_distribution<float> dist(-chebyshevRadius, chebyshevRadius);
		std::vector<glm::vec2> vertices(count);
		for (size_t i{}; i < count; ++i) {
			vertices[i].x = dist(engine);
			vertices[i].y = dist(engine); 
		}
		return VertexBuffer(std::span(vertices));
	}()) {
	static_cast<void>(transformUniform.Set(transform));
}

void Stars::Update(const float deltaTime) {
	if (input.Held(Input::Key::W)) {
		glm::mat3 translation{1.0f};
		translation[2][1] = -deltaTime;
		transform = translation * transform;
	}
	if (input.Held(Input::Key::S)) {
		glm::mat3 translation{1.0f};
		translation[2][1] = deltaTime;
		transform = translation * transform;
	}

	if (input.Held(Input::Key::A)) {
		glm::mat3 rotation{1.0f};
		rotation[0][0] =  cosf(deltaTime);
		rotation[0][1] = -sinf(deltaTime);
		rotation[1][0] =  sinf(deltaTime);
		rotation[1][1] =  cosf(deltaTime);
		transform = rotation * transform;
	}
	if (input.Held(Input::Key::D)) {
		glm::mat3 rotation{1.0f};
		rotation[0][0] =  cosf(deltaTime);
		rotation[0][1] =  sinf(deltaTime);
		rotation[1][0] = -sinf(deltaTime);
		rotation[1][1] =  cosf(deltaTime);
		transform = rotation * transform;
	}
}

void Stars::Draw(const glm::mat3 apparentPixelToClipSpace, const float apparentPixelsPerGameUnit, const float apparentPixelWidth) {
	auto boundToken = transformUniform.Set(transform);
	boundToken = apparentPixelToClipSpaceUniform.Set(apparentPixelToClipSpace, std::move(boundToken));
	boundToken = apparentPixelsPerGameUnitUniform.Set(apparentPixelsPerGameUnit, std::move(boundToken));
	boundToken = apparentPixelWidthUniform.Set(apparentPixelWidth, std::move(boundToken));
	static_cast<void>(program.Run<Program::DrawingMode::POINTS>(vertexArray, vertexBuffer, std::move(boundToken)));
}
