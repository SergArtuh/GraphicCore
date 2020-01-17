include_directories(${INCLUDE_DIRECTORY} ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(This demo)

add_executable(${This} demo.cpp)

target_link_libraries(${This} PUBLIC GraphicCore gapi llr wnd)

install(TARGETS ${This} 
		RUNTIME DESTINATION ${BIN_DIRECTORY}
		LIBRARY DESTINATION ${LIB_DIRECTORY}
	)