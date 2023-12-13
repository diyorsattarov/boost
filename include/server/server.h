#pragma once
#ifndef SERVER_H
#define SERVER_H
#include <utilities/utilities.h>
class Session;
using boost::asio::ip::tcp;

class Server {
    tcp::acceptor acceptor_;
    tcp::socket socket_;

public:
    Server(boost::asio::io_service& io_service, short port)
        : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
          socket_(io_service) {
        doAccept();
    }

private:
    void doAccept();
};
#endif //SERVER_H