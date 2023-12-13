#include <client/client.h>

Client::Client(boost::asio::io_service& io_service, const std::string& host, const std::string& port)
    : io_service_(io_service), socket_(io_service) {
    Utilities::console_logger()->info("Client: Initializing with host {} and port {}", host, port);
    tcp::resolver resolver(io_service_);
    auto endpoint_iterator = resolver.resolve(host, port);
    doConnect(endpoint_iterator);
}

const std::string& Client::server_response() const { return server_response_; }

void Client::doConnect(const tcp::resolver::results_type& endpoints) {
    Utilities::console_logger()->info("Client: Starting async_connect");
    boost::asio::async_connect(socket_, endpoints,
        [this](boost::system::error_code ec, tcp::endpoint) {
            if (!ec) {
                notifyConnected();
                Utilities::console_logger()->info("Client: Connected successfully");
                Bar bar;
                bar.data = "Hello from client";
                std::string serialized_bar = serialize(bar);
                boost::asio::async_write(socket_, boost::asio::buffer(serialized_bar),
                    [this](boost::system::error_code ec, std::size_t /* length */) {
                        if (!ec) {
                            Utilities::console_logger()->info("Client: Data sent successfully");
                            doRead();
                        } else {
                            Utilities::console_logger()->error("Client: Error sending data - {}", ec.message());
                        }
                    });
            } else {
                Utilities::console_logger()->error("Client: Error in async_connect - {}", ec.message());
            }
        }
    );
}

void Client::doRead() {
    Utilities::console_logger()->info("Client: Starting async_read_some");
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        [this](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                Utilities::console_logger()->info("Client: Read {} bytes successfully", length);
                server_response_ = std::string(data_, length);
            } else {
                Utilities::console_logger()->error("Client: Error in async_read_some - {}", ec.message());
            }
        }
    );
}
