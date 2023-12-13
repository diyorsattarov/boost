#include <server/server.h>

Server::Server(boost::asio::io_service& io_service, short port)
    : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
        socket_(io_service) {
    doAccept();
}

void Server::doAccept() {
    acceptor_.async_accept(socket_,
        [this](boost::system::error_code ec) {
            if (!ec) {
                std::make_shared<Session>(std::move(socket_))->start();
            }

            doAccept();
        });
}