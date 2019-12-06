cmake_minimum_required(VERSION 3.15)
project(project2)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_PARALLEL_LEVEL 4)

#-I/usr/local/Cellar/tbb/2019_U8/include/  -L/usr/local/Cellar/tbb/2019_U8/lib/ -ltbb

#find_library (tbb  pstl)
#find_package(tbb REQUIRED)
#include_directories(${tbb_INCLUDE_DIRS})
#set(LIBS ${LIBS} ${LibXML++_LIBRARIES})

#set(-D CMAKE_CXX_COMPILER=/usr/local/Cellar/gcc/9.2.0_2/bin/gcc-9)

add_executable(
        project2
        main.cpp
        agents/players/Player.cpp agents/players/Player.h
        agents/umpires/Umpire.cpp agents/umpires/Umpire.h
        agents/players/payoffsPlayer.cpp agents/players/payoffsPlayer.h
        agents/umpires/payoffsUmpire.cpp agents/umpires/payoffsUmpire.h
        utils/random.cpp utils/random.h
        utils/utils.cpp utils/utils.h
        agents/fitness.cpp agents/fitness.h
        agents/agents.cpp agents/agents.h
        utils/counts.cpp utils/counts.h
        utils/imitationProbabilities.cpp utils/imitationProbabilities.h
        utils/other.cpp utils/other.h
        utils/logs.cpp utils/logs.h
        simulation/Simulation.cpp simulation/Simulation.h)