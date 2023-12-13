#pragma once
#ifndef SERVER_H
#define SERVER_H
#include <utilities/utilities.h>
#include <session/session.h>
class Session;
using boost::asio::ip::tcp;

class Server {
    tcp::acceptor acceptor_;
    tcp::socket socket_;

public:
    Server(boost::asio::io_service& io_service, short port);

private:
    void doAccept();
};
#endif //SERVER_H