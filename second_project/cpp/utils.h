//
// Created by Pedro Rio on 21/11/2019.
//

#ifndef PROJECT2_UTILS_H
#define PROJECT2_UTILS_H

#include <map>
#include <cmath>
#include <random>
#include "Player.h"
#include "Umpire.h"

int randomElement(std::vector<int> otherPlayerIndexes);

int random(int begin, int end);

std::vector<int> range(int firstNumber, int lastNumber);

float imitationProbability(float imitationStrength, float agentOneFitness, float agentTwoFitness);

float playerPayoff(
        Player playerOne, Player playerTwo, Umpire umpire,
        std::map<Umpire::Strategies,
                std::map<Player::Strategies,
                        std::map<Player::Strategies, float>
                >

        > playersPayoffMatrix
);

float umpirePayoff(
        Player playerOne, Player playerTwo, Umpire umpire,
        std::map<Umpire::Strategies,
                std::map<Player::Strategies,
                        std::map<Player::Strategies, float>
                >

        > umpiresPayoffMatrix
);

std::map<Player::Strategies, int> countPlayers(std::vector<Player> players);

std::map<Umpire::Strategies, int> countUmpires(std::vector<Umpire> umpires);

float playerFitness(Player playerOne, Player playerTwo, std::vector<Player> players, Umpire umpire,
                    std::map<Umpire::Strategies,
                            std::map<Player::Strategies,
                                    std::map<Player::Strategies, float>
                            >
                    > playersPayoffMatrix);

float umpireFitness(Player playerOne, Player playerTwo, std::vector<Player> players, Umpire umpireOne, Umpire umpireTwo,
                    std::vector<Umpire> umpires,
                    std::map<Umpire::Strategies,
                            std::map<Player::Strategies,
                                    std::map<Player::Strategies, float>
                            >
                    > umpiresPayoffMatrix);

#endif //PROJECT2_UTILS_H
