//
// Created by Pedro Rio on 30/11/2019.
//

#ifndef PROJECT2_RANDOM_H
#define PROJECT2_RANDOM_H

#include <map>
#include <cmath>
#include <random>
#include "../agents/players/Player.h"
#include "../agents/umpires/Umpire.h"
#include "../agents/agents.h"

std::vector<int> randomElements(std::vector<int> otherPlayerIndexes, int number);
int randomElement(std::vector<int> otherPlayerIndexes);

int random(int begin, int end);

void shuffleAgents(std::vector<Umpire> &umpires, std::vector<Player> &players, std::vector<Agents> &agentSlots);

std::vector<Agents> setupAgentSlots(const std::vector<Player> &players, const std::vector<Umpire> &umpires);

std::vector<Umpire> setupUmpires(std::map<Umpire::Strategies, int> populationMap);
std::vector<Player> setupPlayers(std::map<Player::Strategies, int> populationMap);

#endif //PROJECT2_RANDOM_H
