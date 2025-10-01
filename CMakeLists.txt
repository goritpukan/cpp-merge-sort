cmake_minimum_required(VERSION 4.0)
project(merge)

set(CMAKE_CXX_STANDARD 20)

add_executable(merge src/main.cpp
        include/merge/node.h
        include/merge/data_storage.h
        src/data_storage.cpp
)
