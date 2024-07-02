cmake_minimum_required(VERSION 3.23)
project(FileListing)

set(CMAKE_CXX_STANDARD 23)

set(HEADERS ${CMAKE_SOURCE_DIR}/headers)
set(DEST_INCLUDE_FILE ${HEADERS}/all_headers.h)

# Remove 'all_headers.h' file 
file(REMOVE ${DEST_INCLUDE_FILE})

# Get list of files
file(GLOB TEST_DATA_FILES
    ${HEADERS}/**.h
    # ${CMAKE_SOURCE_DIR}/test_files/**.cpp
)

foreach (file ${TEST_DATA_FILES})

    # get_filename_component(filename_without_extenstion ${file} NAME_WE) # No extension
    # get_filename_component(filename_with_extenstion ${file} NAME)       # With extension

    # message(STATUS "file    : ${file}")
    # message(STATUS "\tname 1  : ${filename_without_extenstion} \n\tname 2  : ${filename_with_extenstion}")

    # file(READ ${file} content)
    # file(READ ${file} content HEX)  # Read as hex

    # message(STATUS "\tcontent : ${content}\n")

    get_filename_component(filename ${file} NAME)
    list(APPEND INCL_FILE_CONTENT "#include \"${filename}\"\n")

endforeach (file ${TEST_DATA_FILES})

# Create 'all_headers.h' file with 'INCL_FILE_CONTENT' content
file(WRITE ${DEST_INCLUDE_FILE} ${INCL_FILE_CONTENT})

include_directories(${HEADERS})

add_executable(${PROJECT_NAME}
        main.cpp
        ${HEADERS}/all_headers.h
)
