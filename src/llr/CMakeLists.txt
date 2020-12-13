
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR})

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

if (GLEW_FOUND AND GLEW_FOUND)
	set(This llr)

	file(GLOB sources ./**.cpp )
	file(GLOB headers ./**.h )
	
	set ( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
	add_library(${This} SHARED ${sources} ${headers})

	file(MAKE_DIRECTORY ${INCLUDE_DIRECTORY}/${This})
	add_custom_command(TARGET ${This} PRE_BUILD COMMAND cp ${headers} ${INCLUDE_DIRECTORY}/${This})
	
	target_include_directories(${This} PUBLIC ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
	target_link_libraries(${This} PUBLIC wnd common ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
	install(TARGETS ${This} 
		RUNTIME DESTINATION ${BIN_DIRECTORY}
		LIBRARY DESTINATION ${LIB_DIRECTORY}
	)

	
endif()

