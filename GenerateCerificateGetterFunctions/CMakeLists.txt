cmake_minimum_required(VERSION 3.23)
project(GenerateCerificateGetterFunctions)

set(CMAKE_CXX_STANDARD 23)

file(GLOB TEST_DATA_FILES
    ${CMAKE_CURRENT_LIST_DIR}/test_data/certificates/**.pem
    ${CMAKE_CURRENT_LIST_DIR}/test_data/certificates/**.crt
)

foreach (file ${TEST_DATA_FILES})
    get_filename_component(filename ${file} NAME_WE) # No extension
    file(READ ${file} content HEX)
    string(REGEX MATCHALL "([A-Fa-f0-9][A-Fa-f0-9])" separated_hex ${content})
    set(counter 0)
    foreach (hex IN LISTS separated_hex)
        string(APPEND blob_value "0x${hex},")
        math(EXPR counter "${counter}+1")
        if (counter GREATER 16)
            string(APPEND blob_value "\n    ")
            set(counter 0)
        endif ()
    endforeach()

    string(SUBSTRING ${filename} 0  1 FIRST_LETTER)
    string(SUBSTRING ${filename} 1 -1 REMAINING_PART)
    string(TOUPPER ${FIRST_LETTER} FIRST_LETTER)

    set(functionName "get${FIRST_LETTER}${REMAINING_PART}Content")

    # list(APPEND FUNCS_DEF  "inline auto ${functionName}()\;\n")
    list(APPEND FUNCS_IMPL "constexpr uint8_t ${filename}[] {\n\t${blob_value}}\;\n\n")
    list(APPEND FUNCS_IMPL "constexpr auto ${functionName}() {\n\treturn ${filename}\;\n}\n\n")

endforeach (file ${TEST_DATA_FILES})


# file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/variables.h  ${FUNCS_DEF} )
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/variables.h  "\#include <cstdint>\n\n" )
file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/variables.h  ${FUNCS_IMPL} )

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(GenerateCerificateGetterFunctions
        main.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/variables.h
)
