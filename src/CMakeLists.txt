project(gyro-crawler)

target_sources(gyro-crawler
	PRIVATE
		main.cpp
		stars.cpp
)

add_subdirectory(interface)
