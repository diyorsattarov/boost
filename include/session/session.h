#pragma once
#ifndef SESSION_H
#define SESSION_H

#include <utilities/utilities.h>

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
    tcp::socket socket_;
    enum { max_length = 1024 };
    char data_[max_length];
    MessageHandler messageHandler;
public:
    explicit Session(tcp::socket socket);
    void start();

private:
    void doRead();
    void handleRead(const boost::system::error_code& error, size_t bytes_transferred);
    void doWrite(size_t length);
    void handleWrite(const boost::system::error_code& error);
};

#endif // SESSION_H
