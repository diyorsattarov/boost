#include <client/client.h>

Client::Client(boost::asio::io_service& io_service, const std::string& host, const std::string& port)
    : io_service_(io_service), socket_(io_service) {
    tcp::resolver resolver(io_service_);
    auto endpoint_iterator = resolver.resolve(host, port);
    doConnect(endpoint_iterator);
}

const std::string& Client::server_response() const {
    return server_response_;
}

void Client::doConnect(const tcp::resolver::results_type& endpoints) {
    boost::asio::async_connect(socket_, endpoints,
        [this](boost::system::error_code ec, tcp::endpoint) {
            if (!ec) {
                Bar bar;
                bar.data = "Hello from client";
                std::string serialized_bar = serialize(bar);
                boost::asio::async_write(socket_, boost::asio::buffer(serialized_bar),
                    [this](boost::system::error_code ec, std::size_t /* length */) {
                        if (!ec) {
                            doRead();
                        }
                    });
            }
        }
    );
}

void Client::doRead() {
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        [this](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                server_response_ = std::string(data_, length);
            }
        }
    );
}