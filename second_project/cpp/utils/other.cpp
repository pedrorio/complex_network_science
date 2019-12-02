//
// Created by Pedro Rio on 30/11/2019.
//

#include "other.h"

Umpire::Strategies getOtherUmpireStrategy(Umpire::Strategies strategy,
                                          std::map<Umpire::Strategies, int> &umpiresCount) {

    std::vector<Umpire::Strategies> strategies;
    strategies.reserve(umpiresCount.size());
    for (auto &kvp : umpiresCount) {
        strategies.emplace_back(kvp.first);
    }
    std::remove_if(
            strategies.begin(),
            strategies.end(),
            [strategy](Umpire::Strategies s) {
                return strategy == s;
            });
    return strategies[0];
}

Player::Strategies getOtherPlayerStrategy(Player::Strategies strategy,
                                          std::map<Player::Strategies, int> &playersCount) {
    std::vector<Player::Strategies> strategies;
    strategies.reserve(playersCount.size());
    for (auto &kvp : playersCount) {
        strategies.emplace_back(kvp.first);
    }
    std::remove_if(
            strategies.begin(),
            strategies.end(),
            [strategy](Player::Strategies s) {
                return strategy == s;
            });
    return strategies[random(0, 2)];
}

std::vector<int> otherIndexes(std::vector<int> existingIndexes, std::vector<int> allIndexes) {
    std::vector<int> diff;
    std::set_difference(allIndexes.begin(), allIndexes.end(), existingIndexes.begin(), existingIndexes.end(),
                        std::inserter(diff, diff.begin()));

    return diff;
}