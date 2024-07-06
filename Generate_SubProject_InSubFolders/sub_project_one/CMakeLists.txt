cmake_minimum_required(VERSION 3.16)
project(GenerateCerificateGetterFunctions)

set(CMAKE_CXX_STANDARD 23)


message(STATUS "CMAKE_PROJECT_NAME : ${CMAKE_PROJECT_NAME}")
message(STATUS "CMAKE_SYSTEM_NAME  : ${CMAKE_SYSTEM_NAME}")
message(STATUS "CMAKE_SOURCE_DIR   : ${CMAKE_SOURCE_DIR}")
# message(STATUS "CMAKE_PROJECT_VERSION    : ${CMAKE_PROJECT_VERSION}")
# message(STATUS "CMAKE_ROOT               : ${CMAKE_ROOT}")
# message(STATUS "CMAKE_BINARY_DIR         : ${CMAKE_BINARY_DIR}")
# message(STATUS "CMAKE_CURRENT_SOURCE_DIR : ${CMAKE_CURRENT_SOURCE_DIR}")


file(GLOB_RECURSE RESULT_VAR LIST_DIRECTORIES true "${CMAKE_SOURCE_DIR}/*")

foreach(item ${RESULT_VAR})
    if(IS_DIRECTORY ${item})
         message(STATUS "item    : ${item}")
    endif()
endforeach()