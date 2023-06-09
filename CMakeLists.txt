cmake_minimum_required(VERSION 3.25)
project(CAOS_server_project C)

set(CMAKE_C_STANDARD 11)

add_executable(server_caos server.c)
add_executable(client_caos client.c)
