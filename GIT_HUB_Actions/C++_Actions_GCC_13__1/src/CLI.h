/**============================================================================
Name        : CLI.h
Created on  : 28.12.2023
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : CLI.h
============================================================================**/

#ifndef BOOKINGSERVICE_CLI_H
#define BOOKINGSERVICE_CLI_H

#include "BookingService.h"
#include <iostream>
#include <functional>
#include <unordered_map>

namespace CLI
{
    using namespace std::string_view_literals;

    class SimpleCLI
    {
    public:
        SimpleCLI(Booking::BookingService &service,
                  std::basic_ostream<char> &out = std::cout);

        enum class Status {
            Ok,
            Continue,
            Stop
        };

        [[nodiscard]]
        Status processCommand(std::string_view userInput);

        void start();

    private:

        using CmdHandlerType = SimpleCLI;
        using methodPtr_t = bool (CmdHandlerType::*)(std::string_view params);

        template<typename... Args>
        bool calFunction(methodPtr_t func, Args&&... params)
        {
            return std::invoke(func , this, std::forward<Args>(params)...);
        }

        [[nodiscard]]
        bool book_seats(std::string_view name);

        [[nodiscard]]
        bool findTheaters(std::string_view name);

        [[nodiscard]]
        bool listPlayingMovies(std::string_view);

        [[nodiscard]]
        bool selectTheater(std::string_view name);

        [[nodiscard]]
        bool selectMovie(std::string_view name);

        [[nodiscard]]
        bool listAvailableSeats(std::string_view name);

        [[nodiscard]]
        bool listAllTheaters(std::string_view);

        [[nodiscard]]
        bool listAllMovies(std::string_view);

        [[nodiscard]]
        static std::vector<std::string_view> split(std::string_view input,
                                                   std::string_view delim = " "sv);

        [[nodiscard]]
        static std::pair<std::string_view, std::string_view> extractCommand(std::string_view input);

        [[nodiscard]]
        Status validateCommand(std::string_view command) const;

    private:

        static inline const std::unordered_map<std::string_view, methodPtr_t> funcMapping
        {
            {"book_seats"sv, &CmdHandlerType::book_seats},
            {"find_theaters"sv, &CmdHandlerType::findTheaters},
            {"list_playing_movies"sv, &CmdHandlerType::listPlayingMovies},
            {"select_theater"sv, &CmdHandlerType::selectTheater},
            {"select_movie"sv, &CmdHandlerType::selectMovie},
            {"list_available_seats"sv, &CmdHandlerType::listAvailableSeats},
            {"list_theaters"sv, &CmdHandlerType::listAllTheaters},
            {"list_movies"sv, &CmdHandlerType::listAllMovies},
       };

        Booking::BookingService& service;
        std::basic_ostream<char>& outStream;

        std::optional<Booking::Theater*> theaterSelected { std::nullopt };
        std::optional<Booking::Movie*> movieSelected { std::nullopt };
    };
};

#endif //BOOKINGSERVICE_CLI_H