/**============================================================================
Name        : BookingService.cpp
Created on  : 28.12.2023
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : BookingService.cpp
============================================================================**/

#include "BookingService.h"
#include <algorithm>
#include <iostream>
#include <unordered_set>

namespace Booking
{
    Premiere::Premiere(const Theater& theater, const Movie& movie):
            theaterId { theater.id }, movieId { movie.id} {
    }

    std::vector<uint16_t> Premiere::getSeatsAvailable() const noexcept
    {
        std::vector<uint16_t> seatsAvailable;
        seatsAvailable.reserve(seats.size());

        for (int seatNum = 1; SeatStatus status: seats) {
            if (SeatStatus::Available == status)
                seatsAvailable.push_back(seatNum);
            ++seatNum;
        }

        seatsAvailable.shrink_to_fit();
        return seatsAvailable;
    }

    // TODO: Describe CAS
    bool Premiere::bookSeats(const std::vector<uint16_t>& seatsToBook)
    {
        std::lock_guard<std::mutex> lock {mtxBooking};
        std::array<SeatStatus, Theater::seatsCapacityMax> seatsCopy {seats};
        for (uint16_t seatNum: seatsToBook)
        {
            const uint16_t seatIdx = seatNum - 1;
            if (0 >= seatNum || seatNum > Theater::seatsCapacityMax || SeatStatus::Booked == seatsCopy[seatIdx])
                return false;
            seatsCopy[seatIdx] = SeatStatus::Booked;
        }

        seats.swap(seatsCopy);
        return true;
    }
}

namespace Booking
{
    std::vector<Movie*> BookingService::getMovies() const
    {
        return movies.getAllEntries();
    }

    std::vector<Theater*> BookingService::getTheaters() const
    {
        return theaters.getAllEntries();
    }

    std::optional<Movie*>
    BookingService::findMovie(const std::string& name) const
    {
        return movies.findEntryName(name);
    }

    std::optional<Theater*>
    BookingService::findTheater(const std::string& name) const
    {
        return theaters.findEntryName(name);
    }

    [[nodiscard]]
    std::vector<Movie*> BookingService::getPlayingMovies() const
    {
        std::unordered_set<size_t> idMovies;
        for (const PremierePtr& premiere: bookingSchedule)
            idMovies.insert(premiere->movieId);

        std::vector<Movie*> playingMovies;
        playingMovies.reserve(idMovies.size());
        for (size_t id: idMovies)
            playingMovies.push_back(movies.findEntryByID(id).value());

        return playingMovies;
    }

    std::vector<Theater*> BookingService::getTheatersByMovie(const std::string& movieName) const
    {
        std::vector<Theater*> theatersByMovie;
        const std::optional<Movie*> movie = findMovie(movieName);
        if (!movie)
            return theatersByMovie;

        for (const PremierePtr& premiere: bookingSchedule)
            if (premiere->movieId == movie.value()->id)
                theatersByMovie.push_back(theaters.findEntryByID(premiere->theaterId).value());

        return theatersByMovie;
    }

    // TODO: To be used if we already have a DB-like objects of Theater and Movie
    std::optional<BookingService::PremierePtr>
    BookingService::getPremiere(const Theater* const theater,
                                const Movie* const movie) const
    {
        for (const PremierePtr& premiere: bookingSchedule) {
            if (premiere->movieId == movie->id && premiere->theaterId == theater->id) {
                return std::make_optional<PremierePtr>(premiere);
            }
        }
        return std::nullopt;
    }

    std::optional<BookingService::PremierePtr>
    BookingService::getPremiere(const std::string& theaterName,
                                const std::string& movieName) const
    {
        const std::optional<Movie*> movie = findMovie(movieName);
        if (!movie)
            return std::nullopt;
        const std::optional<Theater*> theater = findTheater(theaterName);
        if (!movie)
            return std::nullopt;

        return getPremiere(theater.value(), movie.value());
    }

    std::vector<uint16_t> BookingService::getSeatsAvailable(const Theater* const theater,
                                                            const Movie* const movie) const
    {
        const std::optional<PremierePtr> premiere { getPremiere(theater, movie) };
        if (!premiere.has_value())
            return {};

        return premiere.value()->getSeatsAvailable();
    }

    std::vector<uint16_t> BookingService::getSeatsAvailable(const std::string& theaterName,
                                                            const std::string& movieName) const
    {
        const std::optional<PremierePtr> premiere { getPremiere(theaterName, movieName) };
        if (!premiere.has_value())
            return {};

        return premiere.value()->getSeatsAvailable();
    }

    void BookingService::addMovie(const std::string& movieName)
    {
        movies.addEntry(movieName);
    }

    void BookingService::addTheater(const std::string& theaterName)
    {
        theaters.addEntry(theaterName);
    }

    bool BookingService::scheduleMovie(const std::string& movieName,
                                       const std::string& theaterName)
    {
        const std::optional<Movie*> movie { movies.findEntryName(movieName) };
        if (!movie)
            return false;
        const std::optional<Theater*> theater { theaters.findEntryName(theaterName) };
        if (!theater)
            return false;

        bookingSchedule.emplace_back(std::make_shared<Premiere>(*theater.value(), *movie.value()));
        return true;
    }

    // Create some default data
    // TODO : Create some data provider : for tests ??
    void BookingService::initialize()
    {
        addMovie("Fight Club");
        addMovie("The Lord of the Rings: The Fellowship of the Ring");
        addMovie("The Lord of the Rings: The Two Towers");
        addMovie("The Lord of the Rings: The Return of the King");
        addMovie("The Green Mile");
        addMovie("The Shawshank Redemption");
        addMovie("Pulp Fiction");
        addMovie("Terminator");
        addMovie("Terminator 2: Judgment Day");
        addMovie("Inception");
        addMovie("Harry Potter and the Sorcerer's Stone");
        addMovie("Harry Potter and the Chamber of Secrets");
        addMovie("Harry Potter and the Goblet of Fire");
        addMovie("Harry Potter and the Prisoner of Azkaban");

        addTheater("Raj Mandir");
        addTheater("Alamo Drafthouse");
        addTheater("Cine Thisio");
        addTheater("Kino International");
        addTheater("4DX");
        addTheater("Uplink X");
        addTheater("Prasads");
        addTheater("Cine de Chef");
        addTheater("Castro Theatre");
        addTheater("Rooftop Cinema");
        addTheater("AMC Pacific Place Cinema");
        addTheater("Odeon");
        addTheater("Biograf Teater");
        addTheater("Electric Cinema");
        addTheater("Sun Pictures");

        scheduleMovie("Fight Club", "4DX") ;
        scheduleMovie("Fight Club", "Electric Cinema");
        scheduleMovie("The Green Mile", "4DX");
        scheduleMovie("Terminator", "4DX");
        scheduleMovie("Inception", "Odeon");
    }
}