cmake_minimum_required(VERSION 3.23.1)
project(MIDI2Bit)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libgcc -static-libstdc++")
include_directories(src)

add_executable(MIDI2Bit 
        src/main.cpp src/MidiStringParser.cpp src/MidiStringParser.h)