cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 26)

project(Cmake_Properties)
set(PROJECT_VERSION 1.2.3.4)

project(${PROJECT_NAME}
		VERSION ${PROJECT_VERSION}
		DESCRIPTION "Very nice project"
		LANGUAGES CXX
)

add_custom_target(TargetOne)
add_custom_target(TargetTwo)

set_property(TARGET TargetOne  PROPERTY SOME_PROP_ONE 111)
set_target_properties(TargetOne PROPERTIES SOME_PROP_TWO 222)

set_property(TARGET TargetTwo  PROPERTY SOME_PROP_ONE 111222)
set_target_properties(TargetTwo PROPERTIES SOME_PROP_TWO 222333)


get_property(ResultVariable TARGET TargetOne PROPERTY SOME_PROP_ONE)
message("ResultVariable = ${ResultVariable}")

get_property(ResultVariable TARGET TargetOne PROPERTY SOME_PROP_TWO)
message("ResultVariable = ${ResultVariable}")

get_property(ResultVariable TARGET TargetTwo PROPERTY SOME_PROP_ONE)
message("ResultVariable = ${ResultVariable}")

get_property(ResultVariable TARGET TargetTwo PROPERTY SOME_PROP_TWO)
message("ResultVariable = ${ResultVariable}")