#include <message_handler/message_handler.h>

void MessageHandler::handleReceivedMessage(const std::string& message) {
    // Example handling logic
    Utilities::console_logger()->info("Received message: {}", message);
    // Add logic to process the message
}
