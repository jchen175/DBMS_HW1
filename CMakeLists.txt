cmake_minimum_required(VERSION 3.26)
project(dbmsHW1)

set(CMAKE_CXX_STANDARD 17)

add_library(dbmsHW1 record.cpp
        page.cpp
        page.h
        record.h
        write_fixed_len_pages.cpp
        read_fixed_len_page.cpp
        fixed_len_size_exp.cpp)
