//
// Created by Pedro Rio on 06/12/2019.
//

#ifndef PROJECT2_SIMULATION_H
#define PROJECT2_SIMULATION_H

#include <iostream>
#include <vector>
#include <map>
#include <sys/stat.h>
#include <sstream>
#include <cstring>

#include "../agents/players/Player.h"
#include "../agents/umpires/Umpire.h"
#include "../agents/players/payoffsPlayer.h"
#include "../agents/umpires/payoffsUmpire.h"
#include "../agents/fitness.h"

#include "../utils/utils.h"
#include "../utils/logs.h"
#include "../utils/counts.h"
#include "../utils/other.h"
#include "../utils/imitationProbabilities.h"

void simulation(float b, float c, float f, float h, float A, float B, float p, float T, float imitationStrength,
                float playerExplorationProbability, float umpireExplorationProbability,
                int timeStep, int numberOfGenerations, int OC, int PC, int OD, int PD, int H, int C, std::string subPath
);


#endif //PROJECT2_SIMULATION_H
