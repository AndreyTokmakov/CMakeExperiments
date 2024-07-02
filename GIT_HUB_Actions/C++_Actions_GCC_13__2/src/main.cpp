/**============================================================================
Name        : main.cpp
Created on  : 27.12.2023
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : Booking service
============================================================================**/

#include <iostream>
#include <sstream>
#include <future>

#include "BookingService.h"
#include "CLI.h"
#include "WebService.h"


int main([[maybe_unused]] int argc,
         [[maybe_unused]] char** argv)
{
    using namespace Booking;
    // WebService::start(argc, argv);

    Booking::BookingService service;
    service.initialize();

    CLI::SimpleCLI cli (service);
    cli.start();

    return EXIT_SUCCESS;
}
