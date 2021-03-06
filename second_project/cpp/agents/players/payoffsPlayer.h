//
// Created by Pedro Rio on 21/11/2019.
//

#ifndef PROJECT2_PAYOFFSPLAYER_H
#define PROJECT2_PAYOFFSPLAYER_H

#include <map>
#include "../umpires/Umpire.h"
#include "Player.h"

std::map<Umpire::Strategies, std::map<Player::Strategies, std::map<Player::Strategies, float>>>
playersPayoffMatrix(float b, float c, float f, float h, float A, float B);

std::map<Umpire::Strategies, std::map<Player::Strategies, std::map<Player::Strategies, float>>>
uncertainPlayersPayoffMatrix(float b, float c, float f, float h, float A, float B, float p);

#endif //PROJECT2_PAYOFFSPLAYER_H
