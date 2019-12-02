//
// Created by Pedro Rio on 30/11/2019.
//

#include "counts.h"

std::map<Player::Strategies, int> countPlayers(std::vector<Player> players) {
    std::map<Player::Strategies, int> count;
    for (auto strategy = Player::Strategies(0);
         strategy <= Player::Strategies::Last;
         strategy = (Player::Strategies) ((int) (strategy) + 1)
            ) {

        count[strategy] = std::count_if(
                players.begin(), players.end(),
                [strategy](Player player) { return (player.strategy == strategy); }
        );
    }
    return count;
}

std::map<Umpire::Strategies, int> countUmpires(std::vector <Umpire> umpires) {
    std::map<Umpire::Strategies, int> count;
    for (auto strategy = Umpire::Strategies(0);
         strategy <= Umpire::Strategies::Last;
         strategy = (Umpire::Strategies) ((int) (strategy) + 1)) {

        count[strategy] = std::count_if(
                umpires.begin(), umpires.end(),
                [strategy](Umpire umpire) { return (umpire.strategy == strategy); }
        );
    }
    return count;
}