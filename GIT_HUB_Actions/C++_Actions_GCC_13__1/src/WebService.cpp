/**============================================================================
Name        : WebService.cpp
Created on  : 28.12.2023
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : WebService.cpp
============================================================================**/

#include "WebService.h"

#include <iostream>

#include "Poco/Net/DNS.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketStream.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/StreamCopier.h"
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/ServerSocketImpl.h>
#include <Poco/Util/ServerApplication.h>

using Poco::Net::DNS;
using Poco::Net::IPAddress;
using Poco::Net::HostEntry;

#include "BookingService.h"


namespace PocoService
{
    struct EndPoint : public Poco::Net::HTTPRequestHandler
    {
        explicit EndPoint(Booking::BookingService& service): service {service} {
        }

    protected:
        Booking::BookingService& service;
    };

    class GetTheaters: public EndPoint
    {
    public:
        explicit GetTheaters(Booking::BookingService& service): EndPoint (service) {
        }

    private:
        void handleRequest([[maybe_unused]] Poco::Net::HTTPServerRequest &request,
                           [[maybe_unused]] Poco::Net::HTTPServerResponse &response) override
        {
            std::string payload;
            const std::vector<Booking::Theater*> allTheaters = service.getTheaters();
            for (const auto& theater: allTheaters)
                payload.append(theater->name).append("\n");

            response.send() << payload;
            response.send().flush();
            response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);
        }
    };

    struct Factory : public Poco::Net::HTTPRequestHandlerFactory
    {
        Factory() {
            service.initialize();
        }

    private:
        Booking::BookingService service;

        Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &request) override
        {
            if (request.getMethod() != Poco::Net::HTTPRequest::HTTP_GET)
                return nullptr;

            if ("/get_theaters" == request.getURI())
                return new GetTheaters(service);

            return nullptr;
        }
    };

    class ServerSocket : public Poco::Net::ServerSocketImpl {
    public:
        using Poco::Net::SocketImpl::init;
    };

    class Socket : public Poco::Net::Socket {
    public:
        explicit Socket(const std::string &address) :
                Poco::Net::Socket(new ServerSocket()) {
            const Poco::Net::SocketAddress socket_address(address);
            auto *socket = dynamic_cast<ServerSocket *>(impl());
            socket->init(socket_address.af());
            socket->setReuseAddress(true);
            socket->setReusePort(false);
            socket->bind(socket_address, false);
            socket->listen();
        }
    };

    class Server: public Poco::Util::ServerApplication
    {


        int main([[maybe_unused]] const std::vector<std::string>& args) override
        {
            Poco::Net::HTTPServerParams::Ptr parameters = new Poco::Net::HTTPServerParams();
            parameters->setTimeout(10000);
            parameters->setMaxQueued(100);
            parameters->setMaxThreads(4);

            const Poco::Net::ServerSocket socket(Socket("0.0.0.0:8080"));

            Poco::Net::HTTPServer server(new Factory(), socket, parameters);

            server.start();
            waitForTerminationRequest();
            server.stopAll();

            return 0;
        }
    };
}


int WebService::start(int argc,  char** argv)
{
    PocoService::Server server;
    return server.run(argc, argv);
};
