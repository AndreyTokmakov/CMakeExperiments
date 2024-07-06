cmake_minimum_required(VERSION 3.11)
project(FileListing)

set(CMAKE_CXX_STANDARD 23)


message("CMAKE_CURRENT_LIST_DIR: ${CMAKE_CURRENT_LIST_DIR}")
message("CMAKE_SOURCE_DIR      : ${CMAKE_SOURCE_DIR}")


file(GLOB TEST_DATA_FILES
    ${CMAKE_CURRENT_LIST_DIR}/test_files/**.txt
    ${CMAKE_CURRENT_LIST_DIR}/test_files/**.h
    ${CMAKE_CURRENT_LIST_DIR}/test_files/**.cpp
)


message("\nContent of the '${CMAKE_CURRENT_LIST_DIR}/test_files' folder:")
foreach (file ${TEST_DATA_FILES})

    get_filename_component(filename_without_extenstion ${file} NAME_WE) # NAME_WE   = File name with neither the directory nor the longest extension
    get_filename_component(filename_with_extenstion ${file} NAME)       # NAME      = File name without directory
    get_filename_component(directory ${file} DIRECTORY)                 # DIRECTORY = Directory without file name
    get_filename_component(extenstion ${file} EXT)                      # EXT       = File name longest extension (.b.c from d/a.b.c)

    # get_filename_component(name_nwl ${item} NAME_WLE ABSOLUTE)
    # get_filename_component(extenstion ${item}  ABSOLUTE)
    # get_filename_component(last_ext ${item} LAST_EXT ABSOLUTE)

    message("\t file       : ${file}")
    message("\t filename_without_extenstion : ${filename_without_extenstion}")
    message("\t filename_with_extenstion    : ${filename_with_extenstion}")
    message("\t extenstion                  : ${filename_with_extenstion}")
    message("\t directory                   : ${directory}")

    file(READ ${file} content)
    # file(READ ${file} content HEX)  # Read as hex

    message("\n\t content    : ${content}\n")

endforeach (file ${TEST_DATA_FILES})

add_executable(${PROJECT_NAME}
        main.cpp
        # ${CMAKE_CURRENT_BINARY_DIR}/variables.h
)
