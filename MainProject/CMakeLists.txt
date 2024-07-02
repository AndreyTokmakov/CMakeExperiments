cmake_minimum_required(VERSION 3.22)
project(MainProject)

include_directories(${install_dir}/include)

set(CMAKE_CXX_STANDARD 23)

message(STATUS "CMake variables:")
message(STATUS "    CMAKE_VERSION = ${CMAKE_VERSION}")
message(STATUS "    CMAKE_ROOT = ${CMAKE_ROOT}")
message(STATUS "    CMAKE_PROJECT_NAME = ${CMAKE_PROJECT_NAME}")
message(STATUS "    PROJECT_NAME = ${PROJECT_NAME}")
message(STATUS "    CMAKE_CACHEFILE_DIR = ${CMAKE_CACHEFILE_DIR}")
message(STATUS "    CMAKE_COMMAND = ${CMAKE_COMMAND}")
message(STATUS "    CMAKE_BUILD_TOOL = ${CMAKE_BUILD_TOOL}")
message(STATUS "    CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
message(STATUS "    CMAKE_BINARY_DIR = ${CMAKE_BINARY_DIR}")
message(STATUS "    CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "    CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "    PROJECT_BINARY_DIR = ${PROJECT_BINARY_DIR}")
message(STATUS "    CMAKE_CURRENT_LIST_DIR = ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "    CMAKE_CURRENT_LIST_FILE = ${CMAKE_CURRENT_LIST_FILE}")

set (PARENT_DIR ${CMAKE_SOURCE_DIR}/..)
message(STATUS "    PARENT_DIR = ${PARENT_DIR}")
message(STATUS "    Utilities = ${PARENT_DIR}/Utilities")

include_directories("${PARENT_DIR}/Utilities")

message(STATUS "")

add_executable(MainProject main.cpp Integer.cpp Integer.h)
