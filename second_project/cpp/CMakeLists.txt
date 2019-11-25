cmake_minimum_required(VERSION 3.15)
project(project2)

set(CMAKE_CXX_STANDARD 17)

add_executable(project2 main.cpp agents/Player.cpp agents/Player.h agents/Umpire.cpp agents/Umpire.h utils/utils.cpp utils/utils.h payoffs/playerPayoffs.cpp payoffs/playerPayoffs.h payoffs/umpirePayoffs.cpp payoffs/umpirePayoffs.h)