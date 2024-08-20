cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(Check_Print_OS_Params)

set(CMAKE_CXX_STANDARD 23)

cmake_host_system_information(RESULT PRETTY_NAME QUERY DISTRIB_PRETTY_NAME)
message("PRETTY_NAME = ${PRETTY_NAME}\n")


message ("Host params:")
message ("\tCMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")
message ("\tCMAKE_HOST_LINUX: ${CMAKE_HOST_LINUX}")
message ("\tCMAKE_HOST_SYSTEM_PROCESSOR: ${CMAKE_HOST_SYSTEM_PROCESSOR}")
message ("\tCMAKE_SYSTEM_VERSION: ${CMAKE_SYSTEM_VERSION}")
message ("\tCMAKE_HOST_SYSTEM: ${CMAKE_HOST_SYSTEM}")
message ("\tCMAKE_HOST_SYSTEM_VERSION: ${CMAKE_HOST_SYSTEM_VERSION}\n")


message ("Compiler info:")
message ("\tCMAKE_C_COMPILER          ${CMAKE_C_COMPILER}")
message ("\tCMAKE_CXX_COMPILER        ${CMAKE_CXX_COMPILER}")
message ("\tCMAKE_CXX_COMPILER_AR     ${CMAKE_CXX_COMPILER_AR}")
message ("\tCMAKE_CXX_COMPILER_RANLIB ${CMAKE_CXX_COMPILER_RANLIB}")
message ("\tCMAKE_CXX_COMPILER_ID     ${CMAKE_CXX_COMPILER_ID}")

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	message ("\tCompiller  ===>  Clang\n")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	message ("\tCompiller  ===>  GCC\n")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
	message ("\tCompiller  ===>  Intel C++\n")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	message ("\tCompiller  ===>  Visual Studio C++\n")
endif()


message ("OS Type:")
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
	message ("\tLinux\n")
endif()

if(CMAKE_SYSTEM MATCHES Windows)
   message("Target system is Windows\n")
endif()

if(CMAKE_HOST_SYSTEM MATCHES Linux)
   message("Build host runs Linux\n")
endif()


message ("System_Information:")
cmake_host_system_information(RESULT DISTRO QUERY DISTRIB_INFO)
foreach(VAR IN LISTS DISTRO)
  message("\t${VAR}=`${${VAR}}`")
endforeach()
message ("\n")

if(DISTRO_VERSION_ID MATCHES "20.05")
	message("*** OK ***")
endif()
