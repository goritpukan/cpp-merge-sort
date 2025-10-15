cmake_minimum_required(VERSION 4.0)
project(merge)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

add_executable(merge src/main.cpp
        include/merge/node.h
        include/merge/natural_merge_sort.h
        src/natural_merge_sort.cpp
        src/read_file_buffer.cpp
        include/merge/read_file_buffer.h
        src/write_file_buffer.cpp
        include/merge/write_file_buffer.h
        src/external_natural_merge_sort.cpp
        include/merge/external_natural_merge_sort.h
)
