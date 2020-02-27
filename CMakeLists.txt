project(graphic_core)

cmake_minimum_required(VERSION 3.11)

option(BUILD_TESTS "Build test programs" OFF)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(DEFINED INSTALL_DIRECTORY)
	set(BIN_DIRECTORY ${INSTALL_DIRECTORY})
else()
	set(BIN_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
endif()

set(LIB_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(INCLUDE_DIRECTORY ${CMAKE_SOURCE_DIR}/include)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

add_subdirectory(src)

if(BUILD_TESTS)
	add_subdirectory(googletest)
	enable_testing()
	add_subdirectory(tests)
endif(BUILD_TESTS)
