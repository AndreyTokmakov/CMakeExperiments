cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)

set(TEST_VAR 12345)

project(CmakParamsTestApp)
set(PROJECT_VERSION 1.2.3.4)

project(${PROJECT_NAME}
    VERSION ${PROJECT_VERSION} 
    DESCRIPTION "Very nice project"
    LANGUAGES CXX
)


message(STATUS "CMAKE_VERSION            : ${CMAKE_VERSION}")
message(STATUS "CMAKE_ROOT               : ${CMAKE_ROOT}")
message(STATUS "CMAKE_SOURCE_DIR         : ${CMAKE_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR       : ${PROJECT_BINARY_DIR}")
message(STATUS "CMAKE_PROJECT_NAME       : ${CMAKE_PROJECT_NAME}")
message(STATUS "CMAKE_PROJECT_VERSION    : ${CMAKE_PROJECT_VERSION}")
message(STATUS "PROJECT_SOURCE_DIR       : ${PROJECT_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR : ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR : ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR   : ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_FILE  : ${CMAKE_CURRENT_LIST_FILE}")
message(STATUS "PROJECT_DESCRIPTION      : ${PROJECT_DESCRIPTION}")
message(STATUS "PROJECT_IS_TOP_LEVEL     : ${PROJECT_IS_TOP_LEVEL}")
message(STATUS "PROJECT_NAME             : ${PROJECT_NAME}")

message("\n")

message(STATUS "PROJECT_VERSION          : ${PROJECT_VERSION}")
message(STATUS "PROJECT_VERSION_MAJOR    : ${PROJECT_VERSION_MAJOR}")
message(STATUS "PROJECT_VERSION_MINOR    : ${PROJECT_VERSION_MINOR}")
message(STATUS "PROJECT_VERSION_PATCH    : ${PROJECT_VERSION_PATCH}")
message(STATUS "PROJECT_VERSION_TWEAK    : ${PROJECT_VERSION_TWEAK}")

message("\n")

message(STATUS "TEST_VAR: ${TEST_VAR}" )
# message(STATUS "SRC_LEVEL CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
message(STATUS "SRC_LEVEL SOME_TEST_VAR = ${SOME_TEST_VAR}")


list(APPEND English one two three four)
list(APPEND Bahasa satu dua tiga)


message(STATUS "English:" )
foreach(num IN ZIP_LISTS English Bahasa)
    message(STATUS "\tnum_0=${num_0}, num_1=${num_1}")
endforeach()

message(STATUS "Bahasa:" )
foreach(en ba IN ZIP_LISTS English Bahasa)
    message(STATUS "\ten=${en}, ba=${ba}")
endforeach()


list(APPEND LIBS pthread curld)

add_compile_options(-c -Wall -Wextra -O3 -std=c++2a)

# include all components
add_executable(${PROJECT_NAME} 
    main.cpp
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME}
    ${LIBS}
)

