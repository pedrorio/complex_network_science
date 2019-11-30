//
// Created by Pedro Rio on 30/11/2019.
//

#ifndef PROJECT2_FITNESS_H
#define PROJECT2_FITNESS_H

#include "../utils/random.h"
#include "../utils/utils.h"
#include "players/Player.h"
#include "umpires/Umpire.h"
#include "../utils/counts.h"

#include <vector>

float umpirePopulationFitness(float totalUmpires,
                              std::map<Umpire::Strategies,
                                      std::map<Player::Strategies,
                                              std::map<Player::Strategies, float>
                                      >
                              > umpiresPayoffMatrix,
                              float totalPlayers,
                              std::map<Umpire::Strategies, int> umpireCount,
                              std::map<Player::Strategies, int> playerCount);

float umpireFitness(Umpire umpire, float totalUmpires,
                    std::map<Umpire::Strategies,
                            std::map<Player::Strategies,
                                    std::map<Player::Strategies, float>
                            >
                    > umpiresPayoffMatrix,
                    float totalPlayers,
                    std::map<Umpire::Strategies, int> umpireCount,
                    std::map<Player::Strategies, int> playerCount);

float playerPopulationFitness(float totalPlayers,
                              std::map<Umpire::Strategies,
                                      std::map<Player::Strategies,
                                              std::map<Player::Strategies, float>
                                      >
                              > playersPayoffMatrix, float totalUmpires, std::map<Player::Strategies, int> playerCount,
                              std::map<Umpire::Strategies, int> umpireCount);

float playerFitness(Player player, float totalPlayers,
                    std::map<Umpire::Strategies,
                            std::map<Player::Strategies,
                                    std::map<Player::Strategies, float>
                            >
                    > playersPayoffMatrix, float totalUmpires, std::map<Player::Strategies, int> playerCount,
                    std::map<Umpire::Strategies, int> umpireCount);

#endif //PROJECT2_FITNESS_H