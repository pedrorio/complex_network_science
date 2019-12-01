cmake_minimum_required(VERSION 3.15)
project(project2)

set(CMAKE_CXX_STANDARD 17)

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
#        example.h example.cpp
)