cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 26)

project(Cmake_Functions)
set(PROJECT_VERSION 1.2.3.4)

project(${PROJECT_NAME}
        VERSION ${PROJECT_VERSION}
        DESCRIPTION "Very nice project"
        LANGUAGES CXX
)

function(log_message MSG)
    message("\n==> log_message() called")
    message(STATUS "[LOG] ${MSG}")
endfunction()


function(print_all)
    message("\n==> log_message() called")
    foreach(arg IN LISTS ARGN)
        message("\t ARG: ${arg}")
    endforeach()
endfunction()


function(my_super_function REQUIRED_ARG)
    message("\n==> my_super_function() called")
    message("Simple arguments: ${REQUIRED_ARG}, followed by ${ARGN}")
    set(${REQUIRED_ARG} "From 'my_super_function'" PARENT_SCOPE)
endfunction()


function(complex_function)
    message("\n==> complex_function() called")
    cmake_parse_arguments(
            COMPLEX_PREFIX
            "SINGLE;ANOTHER"
            "ONE_VALUE;ALSO_ONE_VALUE"
            "MULTI_VALUES"
            ${ARGN}
    )
endfunction()

#######################################################################################

log_message("Starting build process")

print_all(foo bar baz)

my_super_function(This Foo Bar)
message("Output: ${This}")

complex_function(SINGLE ONE_VALUE value MULTI_VALUES some other values)