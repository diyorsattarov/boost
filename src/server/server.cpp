#include <server/server.h>
#include <session/session.h>

void Server::doAccept() {
    acceptor_.async_accept(socket_,
        [this](boost::system::error_code ec) {
            if (!ec) {
                std::make_shared<Session>(std::move(socket_))->start();
            }

            doAccept();
        });
}