cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

project(SocketClasses)

set(SOURCE_LIB ClientSocket.cpp)
add_library(ClientSocket STATIC ${SOURCE_LIB})
set(SOURCE_LIB ServerSocket.cpp)
add_library(ServerSocket STATIC ${SOURCE_LIB})

add_executable(server server.cpp)
add_executable(client client.cpp)

target_link_libraries(client ClientSocket)
target_link_libraries(server ServerSocket)
