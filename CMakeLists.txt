 cmake_minimum_required(VERSION 2.8)
 
 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")
 
 set(PROJECT_NAME Numeral)
 
 project(${PROJECT_NAME})
 
 set(SRC_EXE Numeral.cpp)
 
 add_executable(main ${SRC_EXE})
 
