#include <gtest/gtest.h>
#include <session/session.h>
#include <server/server.h>
#include <client/client.h>

class SessionTest : public ::testing::Test {
protected:
    boost::asio::io_service io_service;
    boost::asio::io_service::work work;
    std::unique_ptr<std::thread> server_thread;
    Server* server;

    SessionTest() : work(io_service) {
        server = new Server(io_service, 1234);
        server_thread = std::make_unique<std::thread>([this]() { io_service.run(); });
    }

    void TearDown() override {
        // Stop the server and join the thread
        io_service.stop();
        if (server_thread && server_thread->joinable()) {
            server_thread->join();
        }
        delete server;
    }
};

TEST_F(SessionTest, ClientServerCommunication) {
    Client client(io_service, "127.0.0.1", "1234");
    Client client2(io_service, "127.0.0.1", "1234");
    // Give some time for client-server communication to complete
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Deserialize the server response into a Bar object
    Bar received_obj = deserialize<Bar>(client.server_response());
    Bar received_obj2 = deserialize<Bar>(client2.server_response());

    // Check if the client received the correct data from the server
    std::string expected_response = "Hello from client";
    ASSERT_EQ(received_obj.data, expected_response);
    ASSERT_EQ(received_obj2.data, expected_response);
}
