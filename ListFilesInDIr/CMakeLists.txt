cmake_minimum_required(VERSION 3.23)
project(FileListing)

set(CMAKE_CXX_STANDARD 23)


message(STATUS "CMAKE_CURRENT_LIST_DIR: ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "CMAKE_SOURCE_DIR      : ${CMAKE_SOURCE_DIR}")


file(GLOB TEST_DATA_FILES
    ${CMAKE_CURRENT_LIST_DIR}/test_files/**.txt
    ${CMAKE_CURRENT_LIST_DIR}/test_files/**.h
    ${CMAKE_CURRENT_LIST_DIR}/test_files/**.cpp
)


message(STATUS "\nContent of the '${CMAKE_CURRENT_LIST_DIR}/test_files' folder:")
foreach (file ${TEST_DATA_FILES})

    get_filename_component(filename_without_extenstion ${file} NAME_WE) # No extension
    get_filename_component(filename_with_extenstion ${file} NAME)       # With extension

    message(STATUS "\tfile    : ${file}")
    message(STATUS "\tname 1  : ${filename_without_extenstion}")
    message(STATUS "\tname 2  : ${filename_with_extenstion}")

    file(READ ${file} content)
    # file(READ ${file} content HEX)  # Read as hex

    message(STATUS "\tcontent : ${content}\n")

endforeach (file ${TEST_DATA_FILES})


add_executable(${PROJECT_NAME}
        main.cpp
        # ${CMAKE_CURRENT_BINARY_DIR}/variables.h
)
