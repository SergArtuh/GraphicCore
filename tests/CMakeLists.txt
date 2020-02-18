include_directories(${INCLUDE_DIRECTORY} ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(This tests)

add_executable(${This} llr_tests.cpp common_tests.cpp)

target_link_libraries(${This} PUBLIC llr wnd gtest_main)

set_target_properties(${This} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin )

install(TARGETS gtest gtest_main DESTINATION ${BIN_DIRECTORY})

install(TARGETS ${This} 
		RUNTIME DESTINATION ${BIN_DIRECTORY}
		LIBRARY DESTINATION ${LIB_DIRECTORY}
	)

add_test(UnitTests llr_tests common_tests)