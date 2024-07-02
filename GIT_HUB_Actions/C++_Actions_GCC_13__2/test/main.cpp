/**============================================================================
Name        : main.cpp
Created on  : 30.12.2023
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description :
============================================================================ **/

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE BookingServiceUnitTests


#include <algorithm>
#include <thread>
#include <future>
#include <vector>
#include <array>
#include <set>
#include <string>
#include <string_view>
#include <mutex>
#include <iomanip>
#include <format>

#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string.hpp>

#include "BookingService.h"
#include "CLI.h"
#include "WebService.h"

#define CHECK_CONTAINS(str, txt)   BOOST_CHECK_NE(str.find(txt), std::string::npos);

using namespace Booking;
using namespace CLI;

namespace {
    void insertTestData(Booking::BookingService &service) {
        service.addMovie("Fight Club");
        service.addMovie("Terminator");
        service.addMovie("Inception");

        service.addTheater("4DX");
        service.addTheater("Electric Cinema");
        service.addTheater("Sun Pictures");

        service.scheduleMovie("Fight Club", "4DX");
        service.scheduleMovie("Fight Club", "Electric Cinema");
        service.scheduleMovie("Terminator", "Sun Pictures");
        service.scheduleMovie("Terminator", "4DX");
        service.scheduleMovie("Inception", "Electric Cinema");
    }

    std::vector<std::string> splitAndTrimOutput(const std::string &output)
    {
        std::vector<std::string> result;
        boost::split(result, output, boost::is_any_of("\n"));
        for (auto &s: result)
            boost::trim(s);
        return result;
    }

    void validateMultilineOutput(const std::string& output,
                                 const std::vector<std::string>& subStrExpected)
    {
        const std::vector<std::string> outLines { splitAndTrimOutput(output)};
        for (const std::string& text: subStrExpected)
        {
            const bool exits = std::any_of(outLines.cbegin(), outLines.cend(), [&](const auto& str) {
                return str.find(text) != std::string::npos;
            });
            BOOST_CHECK_EQUAL(exits, true);
        }
    }
}

struct BaseFixture
{
    Booking::BookingService service;

    BaseFixture() {
        insertTestData(service);
    }

    virtual ~BaseFixture() = default;
};

struct CLIFixture : BaseFixture
{
    std::stringstream ss;
    CLI::SimpleCLI cli { service, ss};

    auto sendCommand(std::string_view cmd) -> decltype(auto)
    {
        const auto status = cli.processCommand(cmd);
        std::string output = ss.str();
        ss.str("");

        return std::make_pair(output, status);
    }

    ~CLIFixture() override = default;
};

struct BookingCLIFixture : CLIFixture
{
    BookingCLIFixture() {
        auto [output, status] = sendCommand("select_theater 4DX");
        BOOST_REQUIRE(status == SimpleCLI::Status::Continue);
        BOOST_REQUIRE_NE(output.find("The 4DX theater is chosen"), std::string::npos);

        std::tie(output, status) = sendCommand("select_movie Terminator");
        BOOST_REQUIRE(status == SimpleCLI::Status::Continue);
        BOOST_REQUIRE_NE(output.find("The Terminator movie is chosen"), std::string::npos);
    }

    ~BookingCLIFixture() override = default;
};

BOOST_FIXTURE_TEST_SUITE(SchedulerTests, BaseFixture)

    BOOST_AUTO_TEST_CASE(TestGetAllMovies)
    {
        std::vector<Movie*> movies = service.getMovies();
        for (const std::string& movieName: std::vector<std::string>{"Fight Club", "Terminator", "Inception"})
        {
            const bool exits = std::any_of(movies.cbegin(), movies.cend(), [&](const auto& movie) {
                return movie->name == movieName;
            });
            BOOST_CHECK_EQUAL(exits, true);
        }
    }

    BOOST_AUTO_TEST_CASE(TestGetAlltheaters)
    {
        const std::vector<Theater*> theaters = service.getTheaters();
        for (const std::string& theaterName: std::vector<std::string>{"4DX", "Electric Cinema", "Sun Pictures"})
        {
            const bool exits = std::any_of(theaters.cbegin(), theaters.cend(), [&](const auto& theater) {
                return theater->name == theaterName;
            });
            BOOST_CHECK_EQUAL(exits, true);
        }
    }

    BOOST_AUTO_TEST_CASE(TestGetTheatersPlayingMovies)
    {
        const std::vector<Theater*> theaters = service.getTheatersByMovie("Fight Club" );

        BOOST_CHECK_EQUAL(theaters.size(), 2);
        for (const std::string& theaterName: std::vector<std::string>{"4DX", "Electric Cinema"})
        {
            const bool exits = std::any_of(theaters.cbegin(), theaters.cend(), [&](const auto& theater) {
                return theater->name == theaterName;
            });
            BOOST_CHECK_EQUAL(exits, true);
        }
    }

    BOOST_AUTO_TEST_CASE(TestGetSeatsAvailable)
    {
        // TODO: str literals
        const std::vector<uint16_t> seats = service.getSeatsAvailable("4DX", "Fight Club");
        BOOST_CHECK_EQUAL(seats.size(), 20);
    }

    BOOST_AUTO_TEST_CASE(TestGetSeatsAvailable_Premiere)
    {
        const auto premiere = service.getPremiere("4DX", "Fight Club");
        BOOST_CHECK_EQUAL(premiere.has_value(), true);

        const std::vector<uint16_t> seats = premiere.value()->getSeatsAvailable();
        BOOST_CHECK_EQUAL(seats.size(), 20);
    }

    BOOST_AUTO_TEST_CASE(TestBookSeatsAndGetSeatsAvailable)
    {
        const auto premiere = service.getPremiere("4DX", "Fight Club");
        BOOST_CHECK_EQUAL(premiere.has_value(), true);

        std::vector<uint16_t> seats = premiere.value()->getSeatsAvailable();
        BOOST_CHECK_EQUAL(seats.size(), 20);

        const bool ok = premiere.value()->bookSeats({1,2,3});
        BOOST_CHECK_EQUAL(ok, true);

        seats = premiere.value()->getSeatsAvailable();
        BOOST_CHECK_EQUAL(seats.size(), 17);
    }

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(CLI_Basic_Tests)

    BOOST_FIXTURE_TEST_CASE(RunUnknownCommand, CLIFixture)
    {
        const auto [output, status] = sendCommand("avada_kedavra");
        BOOST_CHECK(status == SimpleCLI::Status::Continue);
        CHECK_CONTAINS(output, "Invalid command 'avada_kedavra'");
    }

    BOOST_FIXTURE_TEST_CASE(FindTheatres_ShowingMovie_Ok, CLIFixture)
    {
        const auto [output, status] = sendCommand("find_theaters Terminator");
        BOOST_CHECK(status == SimpleCLI::Status::Continue);
        validateMultilineOutput(output,{
                "The movie 'Terminator' is being shown in", "4DX", "Sun Pictures"
        });
    }

    BOOST_FIXTURE_TEST_CASE(FindTheatres_ShowingMovie_Ok2, CLIFixture)
    {
        const auto [output, status] = sendCommand("find_theaters Fight Club");
        BOOST_CHECK(status == SimpleCLI::Status::Continue);
        validateMultilineOutput(output,{
            "The movie 'Fight Club' is being shown in", "4DX", "Electric Cinema"
        });
    }

    BOOST_FIXTURE_TEST_CASE(ListPlayingMovies, CLIFixture)
    {
        const auto [output, status] = sendCommand("list_playing_movies");
        BOOST_CHECK(status == SimpleCLI::Status::Continue);
        validateMultilineOutput(output,{
                "Inception", "Terminator", "Fight Club"
        });
    }

    BOOST_FIXTURE_TEST_CASE(SelectTheater_Exising, CLIFixture)
    {
        const auto [output, status] = sendCommand("select_theater 4DX");
        BOOST_CHECK(status == SimpleCLI::Status::Continue);
        CHECK_CONTAINS(output, "The 4DX theater is chosen");
    }

    BOOST_FIXTURE_TEST_CASE(SelectTheater_NotExising, CLIFixture)
    {
        const auto [output, status] = sendCommand("select_theater Some_Not_Exising_Name");
        BOOST_CHECK(status == SimpleCLI::Status::Continue);
        CHECK_CONTAINS(output, "Failed to find the 'Some_Not_Exising_Name' theater");
    }

    BOOST_FIXTURE_TEST_CASE(SelectTheater_NoName, CLIFixture)
    {
        const auto [output, status] = sendCommand("select_theater");
        BOOST_CHECK(status == SimpleCLI::Status::Continue);
        CHECK_CONTAINS(output, "Theater name expected");
    }

    BOOST_FIXTURE_TEST_CASE(SelectMovie_Exising , CLIFixture)
    {
        const auto [output, status] = sendCommand("select_movie Terminator");
        BOOST_CHECK(status == SimpleCLI::Status::Continue);
        CHECK_CONTAINS(output, "The Terminator movie is chosen");
    }

    BOOST_FIXTURE_TEST_CASE(SelectMovie_NotExising, CLIFixture)
    {
        const auto [output, status] = sendCommand("select_movie Terminator -1");
        BOOST_CHECK(status == SimpleCLI::Status::Continue);
        CHECK_CONTAINS(output, "Failed to find the 'Terminator -1' movie");
    }

    BOOST_FIXTURE_TEST_CASE(SelectMovie_NoName, CLIFixture)
    {
        const auto [output, status] = sendCommand("select_movie");
        BOOST_CHECK(status == SimpleCLI::Status::Continue);
        CHECK_CONTAINS(output, "Movie name expected");
    }

    BOOST_FIXTURE_TEST_CASE(SelectMovieAndTheater_Ok, CLIFixture)
    {
        auto [output, status] = sendCommand("select_movie Terminator");
        CHECK_CONTAINS(output, "The Terminator movie is chosen");

        std::tie(output, status) = sendCommand("select_theater 4DX");
        BOOST_CHECK(status == SimpleCLI::Status::Continue);
        CHECK_CONTAINS(output, "The 4DX theater is chosen");
    }

    BOOST_FIXTURE_TEST_CASE(SelectTheaterAndMovie_Ok, CLIFixture)
    {
        auto [output, status] = sendCommand("select_theater 4DX");
        CHECK_CONTAINS(output, "The 4DX theater is chosen");

        std::tie(output, status) = sendCommand("select_movie Terminator");
        BOOST_CHECK(status == SimpleCLI::Status::Continue);
        CHECK_CONTAINS(output, "The Terminator movie is chosen");
    }

    BOOST_FIXTURE_TEST_CASE(SelectMovieAndTheater_NotShownInTheater, CLIFixture)
    {
        auto [output, status] = sendCommand("select_movie Terminator");
        CHECK_CONTAINS(output, "The Terminator movie is chosen");

        std::tie(output, status) = sendCommand("select_theater Electric Cinema");
        BOOST_CHECK(status == SimpleCLI::Status::Continue);
        CHECK_CONTAINS(output, "Unfortunately, the Terminator movie is not being shown at the Electric Cinema cinema");
    }

    BOOST_FIXTURE_TEST_CASE(SelectMovieAndTheater_Failed_Retry, CLIFixture)
    {
        auto [output, status] = sendCommand("select_movie Terminator");
        CHECK_CONTAINS(output, "The Terminator movie is chosen");

        std::tie(output, status) = sendCommand("select_theater Electric Cinema");
        CHECK_CONTAINS(output, "Unfortunately, the Terminator movie is not being shown at the Electric Cinema cinema");

        std::tie(output, status) = sendCommand("select_theater 4DX");
        BOOST_CHECK(status == SimpleCLI::Status::Continue);
        CHECK_CONTAINS(output, "The 4DX theater is chosen");
    }

    BOOST_FIXTURE_TEST_CASE(SelectTheaterAndMovie_NotShownInTheater, CLIFixture)
    {
        auto [output, status] = sendCommand("select_theater 4DX");
        CHECK_CONTAINS(output, "The 4DX theater is chosen");

        std::tie(output, status) = sendCommand("select_movie Inception");
        BOOST_CHECK(status == SimpleCLI::Status::Continue);
        CHECK_CONTAINS(output, "Unfortunately, the Inception movie is not being shown at the 4DX cinema");
    }

    BOOST_FIXTURE_TEST_CASE(SelectTheaterAndMovie_Failed_Retry, CLIFixture)
    {
        auto [output, status] = sendCommand("select_theater 4DX");
        CHECK_CONTAINS(output, "The 4DX theater is chosen");

        std::tie(output, status) = sendCommand("select_movie Inception");
        BOOST_CHECK(status == SimpleCLI::Status::Continue);
        CHECK_CONTAINS(output, "Unfortunately, the Inception movie is not being shown at the 4DX cinema");

        std::tie(output, status) = sendCommand("select_movie Terminator");
        BOOST_CHECK(status == SimpleCLI::Status::Continue);
        CHECK_CONTAINS(output, "The Terminator movie is chosen");
    }

    BOOST_FIXTURE_TEST_CASE(GetSeatsAvailalbe, CLIFixture)
    {
        auto [output, status] = sendCommand("select_theater 4DX");
        CHECK_CONTAINS(output, "The 4DX theater is chosen");
        std::tie(output, status) = sendCommand("select_movie Terminator");
        CHECK_CONTAINS(output, "The Terminator movie is chosen");

        std::tie(output, status) = sendCommand("list_available_seats");
        CHECK_CONTAINS(output, "Seats available: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20");
    }

    BOOST_FIXTURE_TEST_CASE(TryBookSeats_NoMovieSelected, CLIFixture)
    {
        auto [output, status] = sendCommand("select_theater 4DX");
        CHECK_CONTAINS(output, "The 4DX theater is chosen");

        std::tie(output, status) = sendCommand("book_seats 1,2,3");
        CHECK_CONTAINS(output, "No theater or Movie selected");
    }

    BOOST_FIXTURE_TEST_CASE(TryBookSeats_NoTheaterSelected, CLIFixture)
    {
        auto [output, status] = sendCommand("select_movie Terminator");
        CHECK_CONTAINS(output, "The Terminator movie is chosen");

        std::tie(output, status) = sendCommand("book_seats 1,2,3");
        CHECK_CONTAINS(output, "No theater or Movie selected");
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CLI_Basic_Tests)

    BOOST_FIXTURE_TEST_CASE(BookSingleSeat_OK, BookingCLIFixture)
    {
        const auto [output, status] = sendCommand("book_seats 5");
        CHECK_CONTAINS(output, "Seats 5 are booked");
    }

    BOOST_FIXTURE_TEST_CASE(BookMultipleSeats_OK, BookingCLIFixture)
    {
        const auto [output, status] = sendCommand("book_seats 1,2,3");
        CHECK_CONTAINS(output, "Seats 1,2,3 are booked");
    }

    BOOST_FIXTURE_TEST_CASE(BookSingleSeat_OK_CheckAvailable, BookingCLIFixture)
    {
        auto [output, status] = sendCommand("book_seats 3");
        CHECK_CONTAINS(output, "Seats 3 are booked");

        std::tie(output, status) = sendCommand("list_available_seats");
        CHECK_CONTAINS(output, "Seats available: 1 2 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20");
    }

    BOOST_FIXTURE_TEST_CASE(BookSingleSeat_Repeat_OK_CheckAvailable, BookingCLIFixture)
    {
        for (int seatNum: {1,3,5,7,9,11}) {
            auto [output, status] = sendCommand(std::format("book_seats {}", seatNum));
            CHECK_CONTAINS(output, std::format("Seats {} are booked", seatNum));
        }

        auto [output, status] = sendCommand("list_available_seats");
        CHECK_CONTAINS(output, "Seats available: 2 4 6 8 10 12 13 14 15 16 17 18 19 20");
    }

    BOOST_FIXTURE_TEST_CASE(BookMultipleSeats_OK_CheckAvailable, BookingCLIFixture)
    {
        auto [output, status] = sendCommand("book_seats 1,2,3,4,5");
        CHECK_CONTAINS(output, "Seats 1,2,3,4,5 are booked");

        std::tie(output, status) = sendCommand("list_available_seats");
        CHECK_CONTAINS(output, "Seats available: 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20");
    }

    BOOST_FIXTURE_TEST_CASE(OverbookingTest_BookSingle, BookingCLIFixture)
    {
        auto [output, status] = sendCommand("book_seats 5");
        CHECK_CONTAINS(output, "Seats 5 are booked");

        std::tie(output, status) = sendCommand("book_seats 5");
        CHECK_CONTAINS(output, "Sorry: Failed to book seats: 5");
    }

    BOOST_FIXTURE_TEST_CASE(OverbookingTest_BookMultipleThenSingle, BookingCLIFixture)
    {
        auto [output, status] = sendCommand("book_seats 1,2,3,4,5");
        CHECK_CONTAINS(output, "Seats 1,2,3,4,5 are booked");

        std::tie(output, status) = sendCommand("book_seats 5");
        CHECK_CONTAINS(output, "Sorry: Failed to book seats: 5");
    }

    BOOST_FIXTURE_TEST_CASE(OverbookingTest_BookSingleThenMultiple, BookingCLIFixture)
    {
        auto [output, status] = sendCommand("book_seats 3");
        CHECK_CONTAINS(output, "Seats 3 are booked");

        std::tie(output, status) = sendCommand("book_seats 1,2,3,4,5");
        CHECK_CONTAINS(output, "Sorry: Failed to book seats: 1,2,3,4,5");
    }

    BOOST_FIXTURE_TEST_CASE(Booking_WrongInput_NoSeats, BookingCLIFixture)
    {
        auto [output, status] = sendCommand("book_seats");
        CHECK_CONTAINS(output, "Seats numbers expected");
    }

    BOOST_FIXTURE_TEST_CASE(Booking_WrongInput_Boundaries_Test, BookingCLIFixture)
    {
        for (int invalidSeatNumber: {0, 21, 1001})
        {
            auto [output, status] = sendCommand(std::format("book_seats {}", invalidSeatNumber));
            CHECK_CONTAINS(output, std::format("Sorry: Failed to book seats: {}", invalidSeatNumber));
        }
    }

    BOOST_FIXTURE_TEST_CASE(Booking_WrongInput_InvalidSeat_Test, BookingCLIFixture)
    {
        for (int invalidSeatNumber: {-1, 100500})
        {
            auto [output, status] = sendCommand(std::format("book_seats {}", invalidSeatNumber));
            CHECK_CONTAINS(output, std::format("Incorrect syntax: '{}'", invalidSeatNumber));
        }

        for (auto invalidSeatNumber: {"-1", "100500", "one", "one-two"})
        {
            auto [output, status] = sendCommand(std::format("book_seats {}", invalidSeatNumber));
            CHECK_CONTAINS(output, std::format("Incorrect syntax: '{}'", invalidSeatNumber));
        }
    }

BOOST_AUTO_TEST_SUITE_END()