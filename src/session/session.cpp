#include <session/session.h>

Session::Session(tcp::socket socket) : socket_(std::move(socket)) {
    Utilities::console_logger()->info("Session: New session created");
}

void Session::start() {
    Utilities::console_logger()->info("Session: Starting session");
    doRead();
}

void Session::doRead() {
    Utilities::console_logger()->info("Session: Starting async_read_some");
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        boost::bind(&Session::handleRead, self,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void Session::handleRead(const boost::system::error_code& error, size_t bytes_transferred) {
    if (!error) {
        Utilities::console_logger()->info("Session: Successfully read {} bytes", bytes_transferred);
        std::string received_data(data_, data_ + bytes_transferred);
        // Use MessageHandler to process the received data
        messageHandler.handleReceivedMessage(received_data);
        doWrite(bytes_transferred);
    } else {
        Utilities::console_logger()->error("Session Read Error: {}", error.message());
    }
}

void Session::doWrite(size_t length) {
    Utilities::console_logger()->info("Session: Starting async_write with {} bytes", length);
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
        boost::bind(&Session::handleWrite, self,
            boost::asio::placeholders::error));
}

void Session::handleWrite(const boost::system::error_code& error) {
    if (!error) {
        Utilities::console_logger()->info("Session: Write completed, continuing to read");
        doRead();
    } else {
        Utilities::console_logger()->error("Session Write Error: {}", error.message());
    }
}
