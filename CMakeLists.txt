cmake_minimum_required(VERSION 3.17)
project(oop_lab1)

set(CMAKE_CXX_STANDARD 20)

add_executable(oop_lab1 main.cpp main.hpp LinkedList.hpp Iterator.hpp Node.hpp Book.cpp Book.hpp Library.cpp Library.hpp Reader.cpp Reader.hpp Console.cpp Console.hpp)
