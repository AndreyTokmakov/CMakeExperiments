cmake_minimum_required(VERSION 3.16)
project(Generate_SubProject_InSubFolders)

set(CMAKE_CXX_STANDARD 23)

set(PROJECT_ROOT_CMAKE_FILE "${CMAKE_SOURCE_DIR}/CMakeLists.txt")
file(GLOB_RECURSE RESULT_FOLDERS_LIST LIST_DIRECTORIES true
    "${CMAKE_SOURCE_DIR}/*"
)

# message(STATUS "CMAKE_PROJECT_NAME : ${CMAKE_PROJECT_NAME}")
# message(STATUS "CMAKE_SYSTEM_NAME  : ${CMAKE_SYSTEM_NAME}")
# message("CMAKE_SOURCE_DIR          : ${CMAKE_SOURCE_DIR}")
# message("PROJECT_ROOT_CMAKE_FILE   : ${PROJECT_ROOT_CMAKE_FILE}")

foreach (item ${RESULT_FOLDERS_LIST})

    if (${item} MATCHES ${PROJECT_ROOT_CMAKE_FILE})
        # Skipping Project root folder
        continue()
    endif()

    if (${item} MATCHES "/CMakeLists.txt")
        get_filename_component(directory ${item} DIRECTORY)
        # message("item : ${item}")
        # message("dir  : ${directory}")
        add_subdirectory(${directory})
    endif()

endforeach()