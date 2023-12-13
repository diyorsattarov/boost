#pragma once
#ifndef SESSION_H
#define SESSION_H

#include <utilities/utilities.h>

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
    tcp::socket socket_;
    enum { max_length = 1024 };
    char data_[max_length];

public:
    Session(tcp::socket socket) : socket_(std::move(socket)) {}

    void start() {
        doRead();
    }

private:
    void doRead() {
        auto self(shared_from_this());
        socket_.async_read_some(boost::asio::buffer(data_, max_length),
            boost::bind(&Session::handleRead, self,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }

    void handleRead(const boost::system::error_code& error, size_t bytes_transferred) {
        if (!error) {
            // Here, handle the received data
            std::string received_data(data_, data_ + bytes_transferred);
            Bar obj = deserialize<Bar>(received_data);
            // ... Use obj as needed

            doWrite(bytes_transferred);
        } else {
            std::cerr << "Error: " << error.message() << std::endl;
        }
    }

    void doWrite(size_t length) {
        auto self(shared_from_this());
        boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
            boost::bind(&Session::handleWrite, self,
                boost::asio::placeholders::error));
    }

    void handleWrite(const boost::system::error_code& error) {
        if (!error) {
            doRead();
        } else {
            std::cerr << "Error: " << error.message() << std::endl;
        }
    }
};
#endif //SESSION_H