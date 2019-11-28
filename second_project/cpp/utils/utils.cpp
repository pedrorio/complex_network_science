//
// Created by Pedro Rio on 21/11/2019.
//

#include <iostream>
#include <fstream>
#include <utility>
#include <variant>
#include "utils.h"

std::random_device rnd;
std::mt19937 generator(rnd());

std::vector<int> randomElements(std::vector<int> otherPlayerIndexes, int number) {

    std::vector<int> sampleIndexes;
    std::sample(otherPlayerIndexes.begin(), otherPlayerIndexes.end(), std::back_inserter(sampleIndexes), number,
                generator);

    return sampleIndexes;
}

int randomElement(std::vector<int> otherPlayerIndexes) {
    return randomElements(std::move(otherPlayerIndexes), 1)[0];
}

int random(int begin, int end) {
    std::uniform_int_distribution<int> distribution(begin, end);
    return distribution(generator);
}

std::vector<int> range(int firstNumber, int lastNumber) {
    std::vector<int> otherPlayerIndexes;
    for (int i = firstNumber; i <= lastNumber; i++)
        otherPlayerIndexes.push_back(i);

    return otherPlayerIndexes;
}

std::vector<int> otherIndexes(std::vector<int> existingIndexes, std::vector<int> allIndexes) {
    std::vector<int> diff;
    std::set_difference(allIndexes.begin(), allIndexes.end(), existingIndexes.begin(), existingIndexes.end(),
                        std::inserter(diff, diff.begin()));

    return diff;
}


std::vector<Agents> setupAgentSlots(const std::vector<Player> &players, const std::vector<Umpire> &umpires) {
    std::vector<Agents> umpireSlots(umpires.size(), Agents::Umpire);
    std::vector<Agents> playerSlots(players.size(), Agents::Player);
    std::vector<Agents> agentSlots;

    agentSlots.insert(agentSlots.end(), umpireSlots.begin(), umpireSlots.end());
    agentSlots.insert(agentSlots.end(), playerSlots.begin(), playerSlots.end());
    std::shuffle(std::begin(agentSlots), std::end(agentSlots), generator);
    return agentSlots;
}

float imitationProbability(float imitationStrength, float agentOneFitness, float agentTwoFitness) {
    return 1 / (1 + std::exp(imitationStrength * (agentOneFitness - agentTwoFitness)));
}

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

std::map<Player::Strategies, float> countPlayerFrequencies(const std::vector<Player> &players) {
    std::map<Player::Strategies, float> frequencies;
    float totalCount = players.size();
    std::map<Player::Strategies, int> count = countPlayers(players);

    for (const auto &entry: count) {
        frequencies[entry.first] = entry.second / totalCount;
    }
    return frequencies;
}

std::map<Umpire::Strategies, int> countUmpires(std::vector<Umpire> umpires) {
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

std::map<Umpire::Strategies, float> countUmpireFrequencies(const std::vector<Umpire> &umpires) {
    std::map<Umpire::Strategies, float> frequencies;
    float totalCount = umpires.size();
    std::map<Umpire::Strategies, int> count = countUmpires(umpires);

    for (const auto &entry: count) {
        frequencies[entry.first] = entry.second / totalCount;
    }
    return frequencies;
}

float playerImitationProbability(Player player,
                                 Player otherPlayer,
                                 float totalNumberOfPlayers,
                                 const std::map<Umpire::Strategies,
                                         std::map<Player::Strategies,
                                                 std::map<Player::Strategies, float>
                                         >
                                 > &playersPayoff,
                                 float totalNumberOfUmpires,
                                 const std::map<Player::Strategies, int> &playersCount,
                                 const std::map<Umpire::Strategies, int> &umpiresCount,
                                 float imitationStrength) {
    float fitnessPlayer = playerFitness(player, totalNumberOfPlayers,
                                        playersPayoff, totalNumberOfUmpires, playersCount,
                                        umpiresCount);
    float fitnessOtherPlayer = playerFitness(otherPlayer, totalNumberOfPlayers,
                                             playersPayoff, totalNumberOfUmpires, playersCount,
                                             umpiresCount);

    return imitationProbability(imitationStrength, fitnessPlayer, fitnessOtherPlayer);
}

float umpireImitationProbability(Umpire umpire,
                                 Umpire otherUmpire,
                                 float totalNumberOfUmpires,
                                 const std::map<Umpire::Strategies,
                                         std::map<Player::Strategies,
                                                 std::map<Player::Strategies, float>
                                         >
                                 > &umpiresPayoff,
                                 float totalNumberOfPlayers,
                                 const std::map<Umpire::Strategies, int> &umpiresCount,
                                 const std::map<Player::Strategies, int> &playersCount,
                                 float imitationStrength) {
    float fitnessPlayer = umpireFitness(umpire, totalNumberOfUmpires,
                                        umpiresPayoff, totalNumberOfPlayers, umpiresCount,
                                        playersCount);
    float fitnessOtherPlayer = umpireFitness(otherUmpire, totalNumberOfUmpires,
                                             umpiresPayoff, totalNumberOfPlayers, umpiresCount,
                                             playersCount);

    return imitationProbability(imitationStrength, fitnessPlayer, fitnessOtherPlayer);
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

std::vector<Umpire> setupUmpires(std::map<Umpire::Strategies, int> populationMap) {
    std::vector<Umpire> umpires;

    for (auto umpireStrategy = Umpire::Strategies(0);
         umpireStrategy <= Umpire::Strategies::Last;
         umpireStrategy = (Umpire::Strategies) ((int) (umpireStrategy) + 1)) {

        std::vector<Umpire> umpiresWithStrategy(populationMap[umpireStrategy], Umpire(umpireStrategy));
        umpires.insert(std::end(umpires), std::begin(umpiresWithStrategy), std::end(umpiresWithStrategy));
    }

    std::shuffle(std::begin(umpires), std::end(umpires), generator);

    return umpires;
}

std::vector<Player> setupPlayers(std::map<Player::Strategies, int> populationMap) {
    std::vector<Player> players;

    for (auto playerStrategy = Player::Strategies(0);
         playerStrategy <= Player::Strategies::Last;
         playerStrategy = (Player::Strategies) ((int) (playerStrategy) + 1)) {

        std::vector<Player> playersWithStrategy(populationMap[playerStrategy], Player(playerStrategy));
        players.insert(std::end(players), std::begin(playersWithStrategy), std::end(playersWithStrategy));
    }

    std::shuffle(std::begin(players), std::end(players), generator);

    return players;
}

Umpire::Strategies getOtherUmpireStrategy(Umpire::Strategies strategy,
                                          std::map<Umpire::Strategies, int> &umpiresCount) {

//    auto strategies = {Umpire::Strategies::Corrupt, Umpire::Strategies::Honest}
    std::vector<Umpire::Strategies> strategies;
    strategies.reserve(umpiresCount.size());
    for (auto &kvp : umpiresCount) {
        strategies.emplace_back(kvp.first);
    }
    std::remove_if(
            strategies.begin(),
            strategies.end(),
            [strategy](Umpire::Strategies s) {
                return strategy == s;
            });
    return strategies[random(0, 0)];
}

Player::Strategies getOtherPlayerStrategy(Player::Strategies strategy,
                                          std::map<Player::Strategies, int> &playersCount) {
    std::vector<Player::Strategies> strategies;
    strategies.reserve(playersCount.size());
    for (auto &kvp : playersCount) {
        strategies.emplace_back(kvp.first);
    }
    std::remove_if(
            strategies.begin(),
            strategies.end(),
            [strategy](Player::Strategies s) {
                return strategy == s;
            });
    return strategies[random(0, 2)];
}

// Error when there are no other strategies
std::vector<Umpire> getUmpiresWithOtherStrategies(std::vector<Umpire> &umpires, Umpire &umpire) {
//    std::vector<Umpire> umpiresWithOtherStrategies = umpires;
//    std::remove_if(
//            std::begin(umpiresWithOtherStrategies), std::end(umpiresWithOtherStrategies), [umpire](Umpire u) {
//                return u.strategy == umpire.strategy;
//            });

    std::vector<Umpire> umpiresWithOtherStrategies;
    std::copy_if(
            std::begin(umpires), std::end(umpires), std::back_inserter(umpiresWithOtherStrategies), [umpire](Umpire u) {
                return u.strategy != umpire.strategy;
            });

//    auto copyIfIterator = std::copy_if(
//            std::begin(umpires), std::end(umpires), std::begin(umpiresWithOtherStrategies), [umpire](Umpire u) {
//                return u.strategy != umpire.strategy;
//            });
//    umpiresWithOtherStrategies.erase(copyIfIterator, umpiresWithOtherStrategies.end());
    return umpiresWithOtherStrategies;
}

// Error when there are no other strategies
std::vector<Player> getPlayersWithOtherStrategies(std::vector<Player> &players, Player &player) {
    std::vector<Player> playersWithOtherStrategies;

    std::copy_if(
            std::begin(players), std::end(players), std::back_inserter(playersWithOtherStrategies), [player](Player p) {
                return p.strategy != player.strategy;
            });


//    std::vector<Player> playersWithOtherStrategies = players;
//    std::remove_if(
//            std::begin(playersWithOtherStrategies), std::end(playersWithOtherStrategies), [player](Player p) {
//                return p.strategy == player.strategy;
//            });

//    auto copyIfIterator = std::copy_if(
//            std::begin(players), std::end(players), std::begin(playersWithOtherStrategies), [player](Player p) {
//                return p.strategy != player.strategy;
//            });
//    playersWithOtherStrategies.erase(copyIfIterator, playersWithOtherStrategies.end());
    return playersWithOtherStrategies;
}

void shuffleAgents(std::vector<Umpire> &umpires, std::vector<Player> &players, std::vector<Agents> &agentSlots) {
    std::shuffle(std::begin(umpires), std::end(umpires), generator);
    std::shuffle(std::begin(players), std::end(players), generator);
    std::shuffle(std::begin(agentSlots), std::end(agentSlots), generator);
}

const std::map<Player::Strategies, std::string> playerStrings = {
        {Player::Strategies::OptimisticCooperator, "OptimisticCooperator"},
        {Player::Strategies::PrudentCooperator,    "PrudentCooperator"},
        {Player::Strategies::OptimisticDefector,   "OptimisticDefector"},
        {Player::Strategies::PrudentDefector,      "PrudentDefector"}
};

const std::map<Umpire::Strategies, std::string> umpireStrings = {
        {Umpire::Strategies::Honest,  "Honest"},
        {Umpire::Strategies::Corrupt, "Corrupt"}
};

void printFrequencies(std::ofstream &outfile,
                      std::map<Player::Strategies, int> &playersCount,
                      float totalPlayers,
                      std::map<Umpire::Strategies, int> &umpiresCount,
                      float totalUmpires,
                      int generation) {

    std::cout << generation;
    outfile << generation;

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

    std::cout << std::endl;
    outfile << std::endl;
}