cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(Application VERSION 1.0.0.0 LANGUAGES C CXX)
# set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION} LANGUAGES CXX)

add_compile_options(-c -Wall -Wextra -O3 -std=c++2a)

# include all components
add_executable(Application 
    main.cpp)

TARGET_LINK_LIBRARIES(Application)

# message(STATUS "SRC_LEVEL CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
message(STATUS "SRC_LEVEL SOME_TEST_VAR = ${SOME_TEST_VAR}")
