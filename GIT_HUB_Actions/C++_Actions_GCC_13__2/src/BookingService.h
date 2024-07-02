/**============================================================================
Name        : BookingService.h
Created on  : 28.12.2023
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : BookingService.h
============================================================================**/

#ifndef BOOKINGSERVICE_BOOKINGSERVICE_H
#define BOOKINGSERVICE_BOOKINGSERVICE_H

#include <string>
#include <vector>
#include <array>

#include "Database.h"

namespace Booking
{
    using namespace DB;

    enum class SeatStatus: bool {
        Available,
        Booked
    };

    struct Movie: TableEntry<Movie>
    {
        explicit Movie(std::string name): TableEntry {std::move(name)} {
        }
    };

    struct Theater: TableEntry<Theater>
    {
        static constexpr uint16_t seatsCapacityMax { 20 };

        explicit Theater(std::string name): TableEntry {std::move(name)} {
        }
    };

    struct Premiere
    {
        size_t theaterId {0};
        size_t movieId {0};
        std::array<SeatStatus, Theater::seatsCapacityMax> seats {};

        mutable std::mutex mtxBooking;

        Premiere(const Theater& theater, const Movie& movie);

        [[nodiscard("Please check the result: Expensive to call")]]
        std::vector<uint16_t> getSeatsAvailable() const noexcept;

        [[nodiscard("Please check the result: Expensive to call")]]
        bool bookSeats(const std::vector<uint16_t>& seatsToBook);
    };

    // TODO: DOCUMENTATION
    struct BookingService
    {
        using PremierePtr = std::shared_ptr<Premiere>;

        Table<Movie> movies;
        Table<Theater> theaters;
        std::vector<PremierePtr> bookingSchedule;

        [[nodiscard]]
        std::optional<Movie*> findMovie(const std::string& name) const;

        [[nodiscard]]
        std::optional<Theater*> findTheater(const std::string& name) const;

        [[nodiscard]]
        std::vector<Movie*> getMovies() const;

        [[nodiscard]]
        std::vector<Theater*> getTheaters() const;

        [[nodiscard]]
        std::vector<Movie*> getPlayingMovies() const;

        [[nodiscard]]
        std::vector<Theater*> getTheatersByMovie(const std::string& movieName) const;

        [[nodiscard]]
        std::optional<PremierePtr> getPremiere(const Theater* const theater,
                                               const Movie* const movie) const;
        [[nodiscard]]
        std::optional<PremierePtr> getPremiere(const std::string& theaterName,
                                               const std::string & movieName) const;
        [[nodiscard]]
        std::vector<uint16_t> getSeatsAvailable(const Theater* const theater,
                                                const Movie* const movie) const;
        [[nodiscard]]
        std::vector<uint16_t> getSeatsAvailable(const std::string& theaterName,
                                                const std::string& movieName) const;

        // Test method
        void addMovie(const std::string& movieName);
        void addTheater(const std::string& theaterName);
        bool scheduleMovie(const std::string& movieName, const std::string& theaterName);

        // Create some default data
        void initialize();
    };
};

#endif //BOOKINGSERVICE_BOOKINGSERVICE_H
