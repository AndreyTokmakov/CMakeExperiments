cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 26)

project(Cmake_Cache_Variables)
set(PROJECT_VERSION 1.2.3.4)

project(${PROJECT_NAME}
		VERSION ${PROJECT_VERSION}
		DESCRIPTION "Very nice project"
		LANGUAGES CXX
)


message("MY_CACHE_VARIABLE = ${MY_CACHE_VARIABLE}")
set(MY_CACHE_VARIABLE "VALUE" CACHE STRING "Description")
