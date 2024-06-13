cmake_minimum_required(VERSION 3.28)

project(gyro-crawler VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra -Wpedantic -Werror -fconcepts-diagnostics-depth=5")

add_executable(gyro-crawler)

add_subdirectory(src) 

target_link_libraries(
	gyro-crawler
		PRIVATE 		
			interface
)

# TODO: Replace with File set
target_include_directories(
	gyro-crawler
		PRIVATE
			resource-embeds
)
