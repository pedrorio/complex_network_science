//
// Created by Pedro Rio on 21/11/2019.
//

#ifndef PROJECT2_UMPIREPAYOFFS_H
#define PROJECT2_UMPIREPAYOFFS_H

#include <map>
#include "Umpire.h"
#include "Player.h"

std::map<Umpire::Strategies,
        std::map<Player::Strategies,
                std::map<Player::Strategies, float>
        >
> umpiresPayoffMatrix(float b, float c, float f, float h, float a);

#endif //PROJECT2_UMPIREPAYOFFS_H
