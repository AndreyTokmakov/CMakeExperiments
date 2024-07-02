cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)

project(tests)
add_compile_options(-c -Wall -Werror -Wextra -O3 -std=c++2a)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
include_directories(${SRC_DIR})

if(Boost_VERSION LESS 106500)
    message(STATUS "Boost version: Boost_VERSION=${Boost_VERSION}")
    message(FATAL "Required Boost version >= 1.65.0")
endif()
message (STATUS "BOOST VERSION: ${Boost_VERSION}")

find_package(Boost REQUIRED COMPONENTS unit_test_framework)

# include all components
add_executable(tests
        main.cpp
        ${SRC_DIR}/BookingService.h
        ${SRC_DIR}/BookingService.cpp
        ${SRC_DIR}/CLI.cpp
        ${SRC_DIR}/CLI.h
        ${SRC_DIR}/Database.cpp
        ${SRC_DIR}/Database.h
)

TARGET_LINK_LIBRARIES(tests boost_unit_test_framework)
