project(graphic_core)

cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BIN_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(LIB_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(INCLUDE_DIRECTORY ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src)

add_subdirectory(googletest)
enable_testing()
add_subdirectory(tests)