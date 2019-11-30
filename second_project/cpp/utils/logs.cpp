//
// Created by Pedro Rio on 30/11/2019.
//

#include "logs.h"

void printFrequencies(std::ofstream &outfile,
                      std::map<Player::Strategies, int> &playersCount,
                      float totalPlayers,
                      std::map<Umpire::Strategies, int> &umpiresCount,
                      float totalUmpires,
                      int generation, float b, float c, float f, float h, float a, float B,
                      float playerExplorationProbability, float umpireExplorationProbability,
                      float imitationStrength, int numberOfGenerations) {

    float completion = (generation / float(numberOfGenerations) * 100);

    std::cout << generation;
    outfile << generation;

    std::cout << std::fixed;
    std::cout << std::setprecision(4);

    outfile << std::fixed;
    outfile << std::setprecision(4);

    for (const auto &entry: playersCount) {
        float playerFrequency = entry.second / totalPlayers;
        std::cout << "," << playerFrequency;
        outfile << "," << playerFrequency;
    }

    for (const auto &entry: umpiresCount) {
        float umpireFrequency = entry.second / totalUmpires;
        std::cout << "," << umpireFrequency;
        outfile << "," << umpireFrequency;
    }

    std::cout << "," << b << "," << c << "," << f << "," << h << "," << a << "," << B << ","
              << playerExplorationProbability << "," << umpireExplorationProbability << "," << imitationStrength
              << "," << completion << '%';
    outfile << "," << b << "," << c << "," << f << "," << h << "," << a << "," << B << ","
            << playerExplorationProbability << "," << umpireExplorationProbability << "," << imitationStrength
            << "," << completion << '%';

    std::cout << std::endl;
    outfile << std::endl;
}


void printHeader(std::ofstream &outfile) {
    std::cout << "Generation";
    outfile << "Generation";

    for (const auto &entry: playerStrings) {
        std::string playerString = entry.second;
        std::cout << "," << playerString;
        outfile << "," << playerString;
    }

    for (const auto &entry: umpireStrings) {
        std::string umpireString = entry.second;
        std::cout << "," << umpireString;
        outfile << "," << umpireString;
    }

    std::cout << "," << "b" << "," << "c" << "," << "f" << "," << "h" << "," << "a" << "," << "B" << ","
              << "playerExplorationProbability" << "," << "umpireExplorationProbability" << "," << "imitationStrength"
              << "," << "Completion";
    outfile << "," << "b" << "," << "c" << "," << "f" << "," << "h" << "," << "a" << "," << "B" << ","
            << "playerExplorationProbability" << "," << "umpireExplorationProbability" << "," << "imitationStrength"
            << "," << "Completion";

    std::cout << std::endl;
    outfile << std::endl;
}