
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR})

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

if (GLEW_FOUND AND GLEW_FOUND)
	file(GLOB sources ./**.cpp ./**.h)

	set ( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

	add_library(llr SHARED ${sources})
	
	
	target_include_directories(llr PUBLIC ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
    target_link_libraries(llr PUBLIC ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
	
	install(TARGETS llr 
		RUNTIME DESTINATION ${BIN_DIRECTORY}
		LIBRARY DESTINATION ${LIB_DIRECTORY}
	)

	install(DIRECTORY ./ DESTINATION ${INCLUDE_DIRECTORY}/llr FILES_MATCHING PATTERN "*.h")
endif()

