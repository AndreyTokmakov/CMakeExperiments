cmake_minimum_required(VERSION 3.16)
project(GenerateCerificateGetterFunctions)

set(CMAKE_CXX_STANDARD 23)

message("")

# message(STATUS "CMAKE_PROJECT_NAME : ${CMAKE_PROJECT_NAME}")
# message(STATUS "CMAKE_SYSTEM_NAME  : ${CMAKE_SYSTEM_NAME}")
message("CMAKE_SOURCE_DIR --> : ${CMAKE_SOURCE_DIR}")

file(GLOB_RECURSE RESULT_FOLDERS_LIST LIST_DIRECTORIES true
    "${CMAKE_SOURCE_DIR}/*"
)

foreach (item ${RESULT_FOLDERS_LIST})

    # if(IS_DIRECTORY ${item})
    if (${item} MATCHES "/CMakeLists.txt")
        get_filename_component(directory ${item} DIRECTORY)

        message("item : ${item}")
        message("dir  : ${directory}")

    endif()
endforeach()

message("")