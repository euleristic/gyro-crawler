project(gyro-crawler)

set(sourceFiles
	error.cpp
	event-handler.cpp
	input.cpp
	glfw-owner.cpp
	program.cpp
	renderer.cpp
	shader.cpp
	uniform.cpp
	vertex-buffer.cpp
	vertex-array.cpp
	window.cpp
)

add_library(interface ${sourceFiles})

find_package(glfw3 3.4 REQUIRED)
find_package(glad REQUIRED)
find_package(glm REQUIRED)
find_package(stb REQUIRED)

target_link_libraries(interface
	PRIVATE
			glfw
			glad::glad
			stb::stb
	PUBLIC
			glm::glm
)
