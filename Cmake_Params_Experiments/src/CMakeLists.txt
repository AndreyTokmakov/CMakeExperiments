cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)


set(TEST_VAR 12345)

message(STATUS "CMAKE_SOURCE_DIR       : ${CMAKE_SOURCE_DIR}")
message(STATUS "PROJECT_SOURCE_DIR     : ${PROJECT_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR : ${CMAKE_CURRENT_LIST_DIR}")


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


project(Application VERSION 1.0.0.0 LANGUAGES C CXX)
# set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION} LANGUAGES CXX)

add_compile_options(-c -Wall -Wextra -O3 -std=c++2a)

# include all components
add_executable(${PROJECT_NAME} 
    main.cpp
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME}
    ${LIBS}
)

