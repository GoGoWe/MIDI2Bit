cmake_minimum_required(VERSION 3.24)
project(MIDI2Bit)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(MIDI2Bit
        src/main.cpp)
