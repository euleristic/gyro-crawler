#ifndef STARS_HPP
#define STARS_HPP

#include "interface/interface.hpp"

class Stars {
public:
	Stars(Interface::Input& input);

	void Update(const float deltaTime);
	void Draw(const glm::mat3 apparentPixelToClipSpace, const float apparentPixelsPerGameUnit, const float apparentPixelWidth);
private:
	Interface::Input& input;
	Interface::Program program;
	glm::mat3 transform;
	Interface::Uniform<glm::mat3> transformUniform;
	Interface::Uniform<glm::mat3> apparentPixelToClipSpaceUniform;
	Interface::Uniform<float>     apparentPixelsPerGameUnitUniform;
	Interface::Uniform<float>     apparentPixelWidthUniform;
	Interface::VertexBuffer vertexBuffer;
	Interface::VertexArray vertexArray;
};
#endif // !STARS_HPP
