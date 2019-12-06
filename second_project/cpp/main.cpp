#include "simulation/Simulation.h"

int main() {
    float b, c, f, h, A, B, p, T, imitationStrength, playerExplorationProbability, umpireExplorationProbability;
    int timeStep, numberOfGenerations, OC, PC, OD, PD, H, C;
    std::string subPath;

    subPath = "";
    timeStep = 1000;
    b = 1, c = f = 0.5, B = 0.2, h = 0.1, A = 2, p = 1.0, T = 0.3;
    playerExplorationProbability = umpireExplorationProbability = 0.001;
    numberOfGenerations = pow(10, 5) * 1;
    imitationStrength = pow(10, 10);
    OC = PC = OD = PD = 10;
    H = C = 20;

    simulation(b, c, f, h, A, B, p, T, imitationStrength,
               playerExplorationProbability, umpireExplorationProbability,
               timeStep, numberOfGenerations, OC, PC, OD, PD, H, C, subPath);

    return 0;
}