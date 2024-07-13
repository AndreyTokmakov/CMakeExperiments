cmake_minimum_required(VERSION 3.30 FATAL_ERROR)
project(FetchContent_Experiments)

include(FetchContent)

set(CMAKE_CXX_STANDARD 23)

message(STATUS "[dependency] fetching googletest")

FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
    GIT_SHALLOW ON
    GIT_PROGRESS ON
)

FetchContent_MakeAvailable(googletest)