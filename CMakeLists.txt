cmake_minimum_required(VERSION 3.31)
project(LibraryManagementSystem)

set(CMAKE_CXX_STANDARD 20)

add_executable(LibraryManagementSystem main.cpp
        book.cpp
        book.h
        library.cpp
        library.h
        library_helper.cpp
        library_helper.h
        utility.h
        utility.cpp
)
