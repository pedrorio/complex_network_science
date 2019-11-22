//
// Created by Pedro Rio on 15/11/2019.
//

#ifndef PROJECT2_UMPIRE_H
#define PROJECT2_UMPIRE_H

class Umpire {

public:
    enum class Strategies {
        Honest,
        Corrupt,
        Last = Corrupt
    };
    Strategies strategy;

    Umpire(Strategies strategy) {
        this->strategy = strategy;
    }
};

#endif //PROJECT2_UMPIRE_H
