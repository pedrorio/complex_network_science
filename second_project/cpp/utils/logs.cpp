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
                      float imitationStrength) {

    std::cout << generation;
    outfile << generation;

    for (const auto &entry: playersCount) {
        float playerFrequency = entry.second / totalPlayers;
        std::cout << "," << std::setprecision(2) << playerFrequency;
        outfile << "," << std::setprecision(2) << playerFrequency;
    }

    for (const auto &entry: umpiresCount) {
        float umpireFrequency = entry.second / totalUmpires;
        std::cout << "," << std::setprecision(2) << umpireFrequency;
        outfile << "," << std::setprecision(2) << umpireFrequency;
    }

    std::cout << "," << b << "," << c << "," << f << "," << h << "," << a << "," << B << ","
              << playerExplorationProbability << "," << umpireExplorationProbability << "," << imitationStrength;
    outfile << "," << b << "," << c << "," << f << "," << h << "," << a << "," << B << ","
            << playerExplorationProbability << "," << umpireExplorationProbability << "," << imitationStrength;


    std::cout << std::endl;
    outfile << std::endl;
}


void printHeader(std::ofstream &outfile) {
    std::cout << "Generation";
    outfile << "Generation";

    for (const auto &entry: playerStrings) {
        std::string playerString = entry.second;
        std::cout << "," << std::setprecision(2) << playerString;
        outfile << "," << std::setprecision(2) << playerString;
    }

    for (const auto &entry: umpireStrings) {
        std::string umpireString = entry.second;
        std::cout << "," << std::setprecision(2) << umpireString;
        outfile << "," << std::setprecision(2) << umpireString;
    }

    std::cout << "," << "b" << "," << "c" << "," << "f" << "," << "h" << "," << "a" << "," << "B" << ","
            << "playerExplorationProbability" << "umpireExplorationProbability" << "imitationStrength";
    outfile << "," << "b" << "," << "c" << "," << "f" << "," << "h" << "," << "a" << "," << "B" << ","
            << "playerExplorationProbability" << "," << "umpireExplorationProbability" << "," << "imitationStrength";

    std::cout << std::endl;
    outfile << std::endl;
}