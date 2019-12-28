
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR})

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

if (GLEW_FOUND AND GLEW_FOUND)
	file(GLOB sources ./**.cpp ./**.h)

	add_library(llr SHARED ${sources})
	
	target_include_directories(llr PRIVATE ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
    target_link_libraries(llr PRIVATE ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
	
	install(TARGETS llr DESTINATION ${BIN_DIRECTORY})
endif()

