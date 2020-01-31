
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR})


set(This GraphicCore)

file(GLOB sources ./**.cpp )
file(GLOB headers ./**.h )
	
set ( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library(${This} SHARED ${sources} ${headers})
	
file(MAKE_DIRECTORY ${INCLUDE_DIRECTORY}/${This})
add_custom_command(TARGET ${This} PRE_BUILD COMMAND cp ${headers} ${INCLUDE_DIRECTORY}/${This})
	
target_link_libraries(${This} PUBLIC gapi llr wnd)
	
install(TARGETS ${This} 
	RUNTIME DESTINATION ${BIN_DIRECTORY}
	LIBRARY DESTINATION ${LIB_DIRECTORY}
)

