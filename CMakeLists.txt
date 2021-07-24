# CMakeListst.txt, placed inside the root directory of the project.
cmake_minimum_required(VERSION 3.19)
project(solve)

set(CMAKE_CXX_STANDARD 17) # for C++17 standard
set(CMAKE_C_STANDARD 99) # for C99 standard

add_executable(solve src/main.cpp src/parser.h src/parser.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME})