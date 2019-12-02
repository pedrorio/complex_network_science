//
// Created by Pedro Rio on 21/11/2019.
//

#ifndef PROJECT2_UTILS_H
#define PROJECT2_UTILS_H

#include <map>
#include "./random.h"
#include "../agents/players/Player.h"
#include "../agents/umpires/Umpire.h"

static const std::map<Player::Strategies, std::string> playerStrings = {
        {Player::Strategies::OptimisticCooperator, "OptimisticCooperator"},
        {Player::Strategies::PrudentCooperator,    "PrudentCooperator"},
        {Player::Strategies::OptimisticDefector,   "OptimisticDefector"},
        {Player::Strategies::PrudentDefector,      "PrudentDefector"}
};

static const std::map<Umpire::Strategies, std::string> umpireStrings = {
        {Umpire::Strategies::Honest,  "Honest"},
        {Umpire::Strategies::Corrupt, "Corrupt"}
};

std::vector<int> range(int firstNumber, int lastNumber);

#endif //PROJECT2_UTILS_H