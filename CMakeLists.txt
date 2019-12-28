project(graphic_core)

cmake_minimum_required(VERSION 3.1.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

#find_package(OpenGL REQUIRED)
#find_package(GLEW REQUIRED)

set(BIN_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(LIB_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(INCLUDE_DIRECTORY ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src)