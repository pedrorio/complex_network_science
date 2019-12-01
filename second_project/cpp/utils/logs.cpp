//
// Created by Pedro Rio on 30/11/2019.
//

#include "logs.h"

void printFrequencies(std::ofstream &outfile,
                      std::map<Player::Strategies, int> &playersCount,
                      float totalPlayers,
                      std::map<Umpire::Strategies, int> &umpiresCount,
                      float totalUmpires,
                      int generation, int numberOfGenerations) {

    float completion = (generation / float(numberOfGenerations) * 100);

    std::cout << generation;
    outfile << generation;

    for (const auto &entry: umpiresCount) {
        float umpireFrequency = entry.second / totalUmpires;
        std::cout << "," << umpireFrequency;
        outfile << "," << umpireFrequency;
    }

    for (const auto &entry: playersCount) {
        float playerFrequency = entry.second / totalPlayers;
        std::cout << "," << playerFrequency;
        outfile << "," << playerFrequency;
    }

    std::cout << "," << completion << '%' << std::endl;
    outfile << "," << completion << '%' << std::endl;
}

void printHeader(std::ofstream &outfile) {
    std::cout << "Generation";
    outfile << "Generation";

    for (const auto &entry: umpireStrings) {
        std::string umpireString = entry.second;
        std::cout << "," << umpireString;
        outfile << "," << umpireString;
    }

    for (const auto &entry: playerStrings) {
        std::string playerString = entry.second;
        std::cout << "," << playerString;
        outfile << "," << playerString;
    }

    std::cout << "," << "Completion" << std::endl;
    outfile << "," << "Completion" << std::endl;
}

void printParamHeaders(std::ofstream &outfile) {

    std::cout << "b" << "," << "c" << "," << "f" << "," << "h" << "," << "a" << "," << "B" << ","
              << "playerExplorationProbability" << "," << "umpireExplorationProbability" << "," << "imitationStrength"
              << std::endl;
    outfile << "b" << "," << "c" << "," << "f" << "," << "h" << "," << "a" << "," << "B" << ","
            << "playerExplorationProbability" << "," << "umpireExplorationProbability" << ","
            << "imitationStrength << std::endl";
}

void printParams(std::ofstream &outfile, float b, float c, float f, float h, float a, float B,
                 float playerExplorationProbability, float umpireExplorationProbability,
                 float imitationStrength) {
    std::cout << "," << b << "," << c << "," << f << "," << h << "," << a << "," << B << ","
              << playerExplorationProbability << "," << umpireExplorationProbability << "," << imitationStrength
              << std::endl;
    outfile << "," << b << "," << c << "," << f << "," << h << "," << a << "," << B << ","
            << playerExplorationProbability << "," << umpireExplorationProbability << "," << imitationStrength
            << std::endl;
}