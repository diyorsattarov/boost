#include <server/server.h>

Server::Server(boost::asio::io_service& io_service, short port)
    : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
      socket_(io_service) {
    Utilities::console_logger()->info("Server: Starting on port {}", port);
    doAccept();
}


void Server::doAccept() {
    Utilities::console_logger()->info("Server: Waiting for new connection");
    acceptor_.async_accept(socket_,
        [this](boost::system::error_code ec) {
            if (!ec) {
                Utilities::console_logger()->info("Server: New connection accepted");
                std::make_shared<Session>(std::move(socket_))->start();
            } else {
                Utilities::console_logger()->error("Server Accept Error: {}", ec.message());
            }

            doAccept();
        });
}
