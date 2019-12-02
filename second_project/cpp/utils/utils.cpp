//
// Created by Pedro Rio on 30/11/2019.
//

#include "utils.h"

std::vector<int> range(int firstNumber, int lastNumber) {
    std::vector<int> otherPlayerIndexes;
    for (int i = firstNumber; i <= lastNumber; i++)
        otherPlayerIndexes.push_back(i);

    return otherPlayerIndexes;
}
