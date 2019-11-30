//
// Created by Pedro Rio on 30/11/2019.
//

#ifndef PROJECT2_OTHER_H
#define PROJECT2_OTHER_H


#include <vector>
#include "../agents/players/Player.h"
#include "../agents/umpires/Umpire.h"
#include "./random.h"

std::vector<int> otherIndexes(std::vector<int> existingIndexes, std::vector<int> allIndexes);

Umpire::Strategies getOtherUmpireStrategy(Umpire::Strategies strategy,
                                          std::map<Umpire::Strategies, int> &umpiresCount);

Player::Strategies getOtherPlayerStrategy(Player::Strategies strategy,
                                          std::map<Player::Strategies, int> &playersCount);


#endif //PROJECT2_OTHER_H
