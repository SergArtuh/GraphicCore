include_directories(${INCLUDE_DIRECTORY} ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(llr_tests llr_tests.cpp)

target_link_libraries(llr_tests llr wnd gtest_main)

install(TARGETS gtest gtest_main DESTINATION ${BIN_DIRECTORY})
install(TARGETS llr_tests DESTINATION ${BIN_DIRECTORY})

add_test(UnitTests llr_tests)