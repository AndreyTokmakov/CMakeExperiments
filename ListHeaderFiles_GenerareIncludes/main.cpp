/**============================================================================
Name        : main.cpp
Created on  : 04.06.2024
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description :
============================================================================**/

#include <iostream>
#include <vector>
#include <string_view>

#include "all_headers.h"

int main([[maybe_unused]] int argc,
         [[maybe_unused]] char** argv)
{
    const std::vector<std::string_view> args(argv + 1, argv + argc);

    DataOne one;
    DataTwo two;
    DataThree three;


    return EXIT_SUCCESS;
}

