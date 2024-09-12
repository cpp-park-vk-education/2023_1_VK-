cmake_minimum_required(VERSION 3.22.1)

project(cli_network)

include_directories(include)
include_directories(src)
include_directories(../Include)

add_executable(cli_network main.cpp)