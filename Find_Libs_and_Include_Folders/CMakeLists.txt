cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(Check_Print_OS_Params)

set(CMAKE_CXX_STANDARD 23)


list(APPEND LIB_DIRS /usr/lib/ /usr/local/lib/ /usr/local/openssl/lib)
list(APPEND INCLUDE_DIRS /usr/include /usr/local/include)

set(MACOS_LIBS_HOME "${CMAKE_SOURCE_DIR}/homebrew/Cellar")

# Tyring to autodetect required libraries:
file(GLOB_RECURSE RESULT_VAR LIST_DIRECTORIES true
    "${MACOS_LIBS_HOME}/*mysql-client*/**"
    "${MACOS_LIBS_HOME}/*libpulsar*/**"
)

foreach(item ${RESULT_VAR})
    if(IS_DIRECTORY ${item})
        if(${item} MATCHES "/include$")
            list(APPEND INCLUDE_DIRS ${item})
        elseif (${item} MATCHES "/lib$")
            list(APPEND LIB_DIRS ${item})
        endif()
    endif()
endforeach()


message(STATUS "\nInclude Directories:")
foreach(dir ${INCLUDE_DIRS})
    message(STATUS "\t${dir}")
endforeach()

message(STATUS "\nLink Directories:")
foreach(dir ${LIB_DIRS})
    message(STATUS "\t${dir}")
endforeach()

message(STATUS "")