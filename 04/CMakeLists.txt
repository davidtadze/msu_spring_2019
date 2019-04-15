cmake_minimum_required(VERSION 3.12)
project(04)

set(CMAKE_CXX_STANDARD 17)

add_executable(04 main.cpp serializer.h deserializer.h error.h)