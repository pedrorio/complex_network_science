//
// Created by Pedro Rio on 30/11/2019.
//

#include "fitness.h"

std::map<Umpire::Strategies, float> countUmpireFrequencies(const std::vector<Umpire> &umpires) {
    std::map<Umpire::Strategies, float> frequencies;
    float totalCount = umpires.size();
    std::map<Umpire::Strategies, int> count = countUmpires(umpires);

    for (const auto &entry: count) {
        frequencies[entry.first] = entry.second / totalCount;
    }
    return frequencies;
}

float playerFitness(Player player, float totalPlayers,
                    std::map<Umpire::Strategies,
                            std::map<Player::Strategies,
                                    std::map<Player::Strategies, float>
                            >
                    > playersPayoffMatrix, float totalUmpires, std::map<Player::Strategies, int> playerCount,
                    std::map<Umpire::Strategies, int> umpireCount) {

    float averagePayoff = 0;

    for (const auto &umpirePair: playersPayoffMatrix) {

        int numberOfUmpires = umpireCount[umpirePair.first];
        float umpireFrequency = numberOfUmpires / totalUmpires;

        for (const auto &playerPair: umpirePair.second) {

            int numberOfPlayers = playerCount[playerPair.first];
            float playerFrequency = numberOfPlayers / totalPlayers;

            int numberOfOtherPlayers;
            float otherPlayerFrequency;

            if (playerPair.first == player.strategy) {
                numberOfOtherPlayers = playerCount[player.strategy] - 1;
                otherPlayerFrequency = numberOfOtherPlayers / (totalPlayers - 1);
            } else {
                numberOfOtherPlayers = playerCount[player.strategy];
                otherPlayerFrequency = numberOfOtherPlayers / totalPlayers;
            }
            averagePayoff += umpireFrequency * playerFrequency * otherPlayerFrequency *
                             playersPayoffMatrix[umpirePair.first][playerPair.first][player.strategy];
        }
    }

    return averagePayoff;
}

float playerPopulationFitness(float totalPlayers,
                              std::map<Umpire::Strategies,
                                      std::map<Player::Strategies,
                                              std::map<Player::Strategies, float>
                                      >
                              > playersPayoffMatrix, float totalUmpires, std::map<Player::Strategies, int> playerCount,
                              std::map<Umpire::Strategies, int> umpireCount) {

    float averagePayoff = 0;

    for (const auto &umpirePair: playersPayoffMatrix) {

        int numberOfUmpires = umpireCount[umpirePair.first];
        float umpireFrequency = numberOfUmpires / totalUmpires;

        for (const auto &playerPair: umpirePair.second) {

            int numberOfPlayers = playerCount[playerPair.first];
            float playerFrequency = numberOfPlayers / totalPlayers;

            for (const auto &otherPlayerPair: playerPair.second) {
                int numberOfOtherPlayers;
                float otherPlayerFrequency;

                if (playerPair.first == otherPlayerPair.first) {
                    numberOfOtherPlayers = playerCount[otherPlayerPair.first] - 1;
                    otherPlayerFrequency = numberOfOtherPlayers / (totalPlayers - 1);
                } else {
                    numberOfOtherPlayers = playerCount[otherPlayerPair.first];
                    otherPlayerFrequency = numberOfOtherPlayers / totalPlayers;
                }
                averagePayoff += umpireFrequency * playerFrequency * otherPlayerFrequency *
                                 playersPayoffMatrix[umpirePair.first][playerPair.first][otherPlayerPair.first];
            }

        }
    }

    return averagePayoff;
}

float umpireFitness(Umpire umpire, float totalUmpires,
                    std::map<Umpire::Strategies,
                            std::map<Player::Strategies,
                                    std::map<Player::Strategies, float>
                            >
                    > umpiresPayoffMatrix,
                    float totalPlayers,
                    std::map<Umpire::Strategies, int> umpireCount,
                    std::map<Player::Strategies, int> playerCount) {

    float averagePayoff = 0;

    int numberOfUmpires = umpireCount[umpire.strategy];
    float umpireFrequency = numberOfUmpires / totalUmpires;

    for (const auto &playerPair: umpiresPayoffMatrix[umpire.strategy]) {

        int numberOfPlayers = playerCount[playerPair.first];
        float playerFrequency = numberOfPlayers / totalPlayers;

        for (const auto &otherPlayerPair: playerPair.second) {

            int numberOfOtherPlayers;
            float otherPlayerFrequency;

            if (playerPair.first == otherPlayerPair.first) {
                numberOfOtherPlayers = playerCount[otherPlayerPair.first] - 1;
                otherPlayerFrequency = numberOfOtherPlayers / (totalPlayers - 1);
            } else {
                numberOfOtherPlayers = playerCount[otherPlayerPair.first];
                otherPlayerFrequency = numberOfOtherPlayers / totalPlayers;
            }

            averagePayoff += umpireFrequency * playerFrequency * otherPlayerFrequency *
                             umpiresPayoffMatrix[umpire.strategy][playerPair.first][otherPlayerPair.first];
        }

    }

    return averagePayoff;
}

float umpirePopulationFitness(float totalUmpires,
                              std::map<Umpire::Strategies,
                                      std::map<Player::Strategies,
                                              std::map<Player::Strategies, float>
                                      >
                              > umpiresPayoffMatrix,
                              float totalPlayers,
                              std::map<Umpire::Strategies, int> umpireCount,
                              std::map<Player::Strategies, int> playerCount) {

    float averagePayoff = 0;

    for (const auto &umpirePair: umpiresPayoffMatrix) {

        int numberOfUmpires = umpireCount[umpirePair.first];
        float umpireFrequency = numberOfUmpires / totalUmpires;

        for (const auto &playerPair: umpirePair.second) {

            int numberOfPlayers = playerCount[playerPair.first];
            float playerFrequency = numberOfPlayers / totalPlayers;

            for (const auto &otherPlayerPair: playerPair.second) {

                int numberOfOtherPlayers;
                float otherPlayerFrequency;

                if (playerPair.first == otherPlayerPair.first) {
                    numberOfOtherPlayers = playerCount[otherPlayerPair.first] - 1;
                    otherPlayerFrequency = numberOfOtherPlayers / (totalPlayers - 1);
                } else {
                    numberOfOtherPlayers = playerCount[otherPlayerPair.first];
                    otherPlayerFrequency = numberOfOtherPlayers / totalPlayers;
                }

                averagePayoff += umpireFrequency * playerFrequency * otherPlayerFrequency *
                                 umpiresPayoffMatrix[umpirePair.first][playerPair.first][otherPlayerPair.first];
            }

        }
    }

    return averagePayoff;
}
