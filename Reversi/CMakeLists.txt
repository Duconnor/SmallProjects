cmake_minimum_required(VERSION 3.10)
project(Reversi)

set(CMAKE_CXX_STANDARD 11)

add_executable(Reversi main.cpp Define.h Board.cpp Reversi.cpp  ClientSocket.cpp)