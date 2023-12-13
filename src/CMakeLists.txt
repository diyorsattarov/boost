add_library(session
    session/session.cpp
)
target_include_directories(session PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

add_library(client
    client/client.cpp
)
target_include_directories(client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

add_library(server
    server/server.cpp
    session/session.cpp
)
target_include_directories(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

add_library(message_handler
    message_handler/message_handler.cpp
)
target_include_directories(message_handler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

add_library(utilities
    utilities/utilities.cpp
)
target_include_directories(utilities PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
