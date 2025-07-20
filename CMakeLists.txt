cmake_minimum_required(VERSION 3.21)
project(CMakeExperiments)

set(CMAKE_CXX_STANDARD 26)

list(APPEND EXTRA_LIBS)
if (CMAKE_SYSTEM_VERSION MATCHES "5.15") # 5.15 - My home Ubuntu-20.04
    set(THIRD_PARTY_DIR /home/andtokm/DiskS/ProjectsUbuntu/third_party)
    list(APPEND EXTRA_LIBS tbb)
else()
    set(THIRD_PARTY_DIR /home/andrei/Projects/third_party)
endif()

# Gcc-15 Experimental library symbols: 'Stacktrace'
list(APPEND EXTRA_LIBS stdc++exp)


#[[
add_subdirectory(Check_Print_OS_Params)
add_subdirectory(Cmake_Params_Experiments)
add_subdirectory(Deternmine_Compiler_Type)
add_subdirectory(FetchContent_Experiments)
add_subdirectory(Find_Libs_and_Include_Folders)
add_subdirectory(GenerateCerificateGetterFunctions)
add_subdirectory(Generate_SubProject_InSubFolders)
add_subdirectory(GIT_HUB_Actions)
add_subdirectory(ListFilesInDIr)
add_subdirectory(ListHeaderFiles_GenerareIncludes)
add_subdirectory(MainProject)
add_subdirectory(SimpleProject)
add_subdirectory(Utilities)
#]]