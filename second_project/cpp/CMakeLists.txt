cmake_minimum_required(VERSION 3.15)
project(project2)

set(CMAKE_CXX_STANDARD 17)

add_executable(project2 main.cpp Player.cpp Player.h Umpire.cpp Umpire.h utils.cpp utils.h playerPayoffs.cpp playerPayoffs.h umpirePayoffs.cpp umpirePayoffs.h)