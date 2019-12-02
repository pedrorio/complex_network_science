//
// Created by Pedro Rio on 30/11/2019.
//

#ifndef PROJECT2_COUNTS_H
#define PROJECT2_COUNTS_H

#include <map>
#include <vector>
#include "../agents/players/Player.h"
#include "../agents/umpires/Umpire.h"

std::map<Player::Strategies, int> countPlayers(std::vector<Player> players);
std::map<Umpire::Strategies, int> countUmpires(std::vector<Umpire> umpires);

#endif //PROJECT2_COUNTS_H
