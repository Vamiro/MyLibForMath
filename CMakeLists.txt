cmake_minimum_required(VERSION 3.25)
project(MyLibForMath)

set(CMAKE_CXX_STANDARD 20)

add_executable(MyLibForMath main.cpp Matrix.cpp PointR2.cpp PointR3.cpp VectorR2.cpp VectorR3.cpp RBTree.h)
