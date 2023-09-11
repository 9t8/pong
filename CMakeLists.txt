cmake_minimum_required(VERSION 3.5)

project(pong LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(pong main.cpp pong.h pong.cpp paddle.h paddle.cpp
    ball.h ball.cpp test.h test.cpp)

find_package(SFML COMPONENTS graphics window system audio REQUIRED)
target_link_libraries(pong sfml-graphics sfml-audio)

file(CREATE_LINK "${CMAKE_SOURCE_DIR}/assets" assets SYMBOLIC)
