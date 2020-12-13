
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR})


set(ZLIB_INCLUDE_DIR ${INCLUDE_DIRECTORY}/zlib)
set(PNG_PNG_INCLUDE_DIR ${INCLUDE_DIRECTORY}/png)
set(PNG_LIBRARY ${LIB_DIRECTORY}/libpng16d.lib)

find_package(PNG REQUIRED)

set(This common)

file(GLOB sources ./**.cpp )
file(GLOB headers ./**.h )
	
set ( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library(${This} SHARED ${sources} ${headers})
set_target_properties(${This} PROPERTIES LINKER_LANGUAGE CXX)
	
file(MAKE_DIRECTORY ${INCLUDE_DIRECTORY}/${This})
add_custom_command(TARGET ${This} PRE_BUILD COMMAND cp ${headers} ${INCLUDE_DIRECTORY}/${This})

target_include_directories(${This} PUBLIC ${PNG_INCLUDE_DIR})
target_link_libraries(${This} PUBLIC ${PNG_LIBRARY})



	
install(TARGETS ${This} 
	RUNTIME DESTINATION ${BIN_DIRECTORY}
	LIBRARY DESTINATION ${LIB_DIRECTORY}
)

