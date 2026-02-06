cmake_minimum_required(VERSION 3.11)
project(ClientSocketProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(
    clientsocketlib STATIC
    src/socket.cpp
)

target_include_directories(
    clientsocketlib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(example examples/main.cpp)
target_link_libraries(example PRIVATE clientsocketlib ws2_32)
