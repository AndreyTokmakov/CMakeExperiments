cmake_minimum_required(VERSION 3.16.3)
project(BookingService)

add_compile_options(-c -Wall -Wextra -O3 -std=c++2a)

# set(CMAKE_PREFIX_PATH ../../third_party/poco/cmake-build)
# find_package(Poco REQUIRED Foundation Net Util)

set(CMAKE_CXX_STANDARD 20)

add_executable(BookingService
        main.cpp
        Database.cpp Database.h
        BookingService.cpp BookingService.h
        CLI.cpp CLI.h
        # WebService.cpp WebService.h
)

TARGET_LINK_LIBRARIES(
        BookingService
        # Poco::Foundation Poco::Net Poco::Util
        pthread
)