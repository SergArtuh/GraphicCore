include_directories(${INCLUDE_DIRECTORY} ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(This llr_tests)

add_executable(${This} llr_tests.cpp)

target_link_libraries(llr_tests PUBLIC llr wnd gtest_main)

install(TARGETS gtest gtest_main DESTINATION ${BIN_DIRECTORY})

install(TARGETS ${This} 
		RUNTIME DESTINATION ${BIN_DIRECTORY}
		LIBRARY DESTINATION ${LIB_DIRECTORY}
	)

add_test(UnitTests llr_tests)