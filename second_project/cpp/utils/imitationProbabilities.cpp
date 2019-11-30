//
// Created by Pedro Rio on 30/11/2019.
//

#include <cmath>
#include "imitationProbabilities.h"

float imitationProbability(float imitationStrength, float agentOneFitness, float agentTwoFitness) {
    return 1 / (1 + std::exp(imitationStrength * (agentOneFitness - agentTwoFitness)));
}