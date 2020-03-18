cmake_minimum_required(VERSION 3.14)
project(pbrain-Junk)

set(CMAKE_CXX_STANDARD 14)
add_executable(pbrain-Junk Gomoku.cpp Gomoku.h Evaluate.cpp Zobrist.cpp pisqpipe.h pisqpipe.cpp example.cpp)
add_definitions(-Wall -Werror)