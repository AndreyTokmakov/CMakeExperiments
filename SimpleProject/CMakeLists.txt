cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(SimpleProject)

set(CMAKE_CXX_STANDARD 20)

#message(STATUS "ROOT CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
set(SOME_TEST_VAR "Some_Value")

add_subdirectory(src)