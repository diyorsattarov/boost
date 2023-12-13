cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME cpp-boost)

project(${PROJECT_NAME})
add_subdirectory(src)

# Assuming you have a tests directory with test sources
add_executable(tests
    tests/session/test_session.cpp
    # ... other test files ...
)

find_package(GTest REQUIRED)
find_package(Boost REQUIRED COMPONENTS system serialization)
find_package(spdlog REQUIRED)

target_include_directories(tests PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(tests PRIVATE 
    ${GTEST_BOTH_LIBRARIES} 
    pthread 
    Boost::system 
    Boost::serialization 
    spdlog::spdlog
    session 
    client 
    server 
    message_handler 
    utilities
)

add_custom_target(run_tests COMMAND tests)
