cmake_minimum_required(VERSION 3.16.3)
project(cache)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SRCS "main.cpp")

add_executable(cache ${SRCS})
