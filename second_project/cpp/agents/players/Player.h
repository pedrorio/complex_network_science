//
// Created by Pedro Rio on 15/11/2019.
//

#ifndef PROJECT2_PLAYER_H
#define PROJECT2_PLAYER_H

class Player {
public:
    enum class Strategies {
        OptimisticCooperator,
        PrudentCooperator,
        OptimisticDefector,
        PrudentDefector,
        Last = PrudentDefector
    };

    Strategies strategy;

    Player(Strategies strategy) {
        this->strategy = strategy;
    }

};

#endif //PROJECT2_PLAYER_H
