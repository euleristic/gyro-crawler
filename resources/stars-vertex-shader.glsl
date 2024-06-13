#version 330 core

layout (location = 0) in vec2 vertexAttribute;

uniform float apparentPixelWidthUniform;
uniform float apparentPixelsPerGameUnitUniform;
uniform mat3  transformUniform;
uniform mat3  apparentPixelToClipSpaceUniform;

void main() {
	
	// Get the star in game space (relative to camera/player).
	vec2 gameSpacePosition = vec2(transformUniform * vec3(vertexAttribute, 1.0f));

	// The transformation to apparent pixel space is a simple scalar.
	vec2 apparentPixelSpacePosition = apparentPixelsPerGameUnitUniform * gameSpacePosition;
	
	// Snap these into the nearest apparent pixel, adjusting for offset.
	apparentPixelSpacePosition = round(apparentPixelSpacePosition) - vec2(0.5f);

	// Transform to clip space
	gl_Position = vec4(apparentPixelToClipSpaceUniform * vec3(apparentPixelSpacePosition, 1.0f), 1.0f);

	gl_PointSize = apparentPixelWidthUniform;
}
