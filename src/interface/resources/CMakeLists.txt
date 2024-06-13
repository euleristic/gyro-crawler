project(GyroCrawler)

file(GLOB_RECURSE resourceList
	RELATIVE_PATH ${CMAKE_SOURCE_DIR}/resources/*
)

foreach(resource IN ITEMS ${resourceList})
	cmake_path(GET resource FILENAME filename)
	string(REPLACE "." "_" defName ${filename})
	string(TOUPPER ${defName} defName)
	string(PREPEND defName "EMBED_")
	string(APPEND filename ".hpp")
	add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${filename}
		COMMAND embedder -o ${CMAKE_CURRENT_BINARY_DIR}/${filename} -d ${defName} -f ${resource}
		COMMENT "embedding ${resource} as ${defName} in ${CMAKE_CURRENT_BINARY_DIR}/${filename}"
	)
	target_sources(GyroCrawler PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/${filename})
	message("embedding ${resource} as ${defName} in ${CMAKE_CURRENT_BINARY_DIR}/${filename}")
endforeach()
