//
// Created by Pedro Rio on 30/11/2019.
//

#ifndef PROJECT2_LOGS_H
#define PROJECT2_LOGS_H

#include <iostream>
#include <iomanip>
#include <fstream>

#include "utils.h"
#include "../agents/players/Player.h"
#include "../agents/umpires/Umpire.h"

void printFrequencies(std::ofstream &outfile,
                      std::map<Player::Strategies, int> &playersCount,
                      float totalPlayers,
                      std::map<Umpire::Strategies, int> &umpiresCount,
                      float totalUmpires, int generation, int numberOfGenerations);

void printHeader(std::ofstream &outfile);

void printParams(std::ofstream &outfile, float b, float c, float f, float h, float A, float B,
                 float playerExplorationProbability, float umpireExplorationProbability,
                 float imitationStrength, float p, float T);

void printParamHeaders(std::ofstream &outfile);

#endif //PROJECT2_LOGS_H
