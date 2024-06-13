#include "stars.hpp"

#include "shader-source.hpp"

using namespace Interface;

constexpr glm::vec2 vertices[] = {
	{  1.0f, -1.0f },
	{  1.0f,  1.0f },
	{ -1.0f, -1.0f },
	{ -1.0f,  1.0f }
};

Stars::Stars(Input& input) : 
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
	vertexBuffer(VertexBuffer(vertices, sizeof(vertices))),
	vertexArray(VertexArray::WithLayout<glm::vec2>(vertexBuffer)) {

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
	static_cast<void>(program.Run<Program::DrawingMode::POINTS>(vertexArray, 0, sizeof(vertices) / sizeof(decltype(*vertices)), std::move(boundToken)));
}
