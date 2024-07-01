cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(TestPbf
    LANGUAGES CXX
)

add_subdirectory(tcpsocket)
add_subdirectory(client)
add_subdirectory(server)
