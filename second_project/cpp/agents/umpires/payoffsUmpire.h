//
// Created by Pedro Rio on 21/11/2019.
//

#ifndef PROJECT2_PAYOFFSUMPIRE_H
#define PROJECT2_PAYOFFSUMPIRE_H

#include <map>

#include "Umpire.h"
#include "../players/Player.h"

std::map<Umpire::Strategies,
        std::map<Player::Strategies,
                std::map<Player::Strategies, float>
        >
> umpiresPayoffMatrix(float b, float c, float f, float h, float a, float B);

std::map<Umpire::Strategies,
        std::map<Player::Strategies,
                std::map<Player::Strategies, float>
        >
> uncertainUmpiresPayoffMatrix(float b, float c, float f, float h, float A, float B, float p);


std::map<Umpire::Strategies,
        std::map<Player::Strategies,
                std::map<Player::Strategies, float>
        >
> punishmentUmpiresPayoffMatrix(float b, float c, float f, float h, float A, float B, float T);

#endif //PROJECT2_PAYOFFSUMPIRE_H
