#include <session/session.h>

Session::Session(tcp::socket socket) : socket_(std::move(socket)) {}

void Session::start() {
    doRead();
}

void Session::doRead() {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        boost::bind(&Session::handleRead, self,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void Session::handleRead(const boost::system::error_code& error, size_t bytes_transferred) {
    if (!error) {
        std::string received_data(data_, data_ + bytes_transferred);
        // Use MessageHandler to process the received data
        messageHandler.handleReceivedMessage(received_data);

        doWrite(bytes_transferred);
    } else {
        std::cerr << "Error: " << error.message() << std::endl;
    }
}

void Session::doWrite(size_t length) {
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
        boost::bind(&Session::handleWrite, self,
            boost::asio::placeholders::error));
}

void Session::handleWrite(const boost::system::error_code& error) {
    if (!error) {
        doRead();
    } else {
        std::cerr << "Error: " << error.message() << std::endl;
    }
}
