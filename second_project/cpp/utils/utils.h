//
// Created by Pedro Rio on 21/11/2019.
//

#ifndef PROJECT2_UTILS_H
#define PROJECT2_UTILS_H

#include <map>
#include <cmath>
#include <random>
#include "../agents/Player.h"
#include "../agents/Umpire.h"

enum class Agents {
    Umpire,
    Player,
    Last = Player
};

std::vector<int> randomElements(std::vector<int> otherPlayerIndexes, int number);

int randomElement(std::vector<int> otherPlayerIndexes);

int random(int begin, int end);

std::vector<int> range(int firstNumber, int lastNumber);

std::vector<int> otherIndexes(std::vector<int> existingIndexes, std::vector<int> allIndexes);

std::vector<Agents> setupAgentSlots(std::vector<Player> players, std::vector<Umpire> umpires);

float imitationProbability(float imitationStrength, float agentOneFitness, float agentTwoFitness);

std::map<Player::Strategies, int> countPlayers(std::vector<Player> players);

std::map<Player::Strategies, float> countPlayerFrequencies(std::vector<Player> players);

std::map<Umpire::Strategies, int> countUmpires(std::vector<Umpire> umpires);

std::map<Umpire::Strategies, float> countUmpireFrequencies(std::vector<Umpire> umpires);

float playerImitationProbability(Player player, Player otherPlayer, float totalNumberOfPlayers,
                                 std::map<Umpire::Strategies,
                                         std::map<Player::Strategies,
                                                 std::map<Player::Strategies, float>
                                         >
                                 > playersPayoff,
                                 float totalNumberOfUmpires, std::map<Player::Strategies, int> playersCount,
                                 std::map<Umpire::Strategies, int> umpiresCount, float imitationStrength);

float umpireImitationProbability(Umpire umpire, Umpire otherUmpire, float totalNumberOfUmpires,
                                 std::map<Umpire::Strategies,
                                         std::map<Player::Strategies,
                                                 std::map<Player::Strategies, float>
                                         >
                                 > umpiresPayoff,
                                 float totalNumberOfPlayers, std::map<Umpire::Strategies, int> umpiresCount,
                                 std::map<Player::Strategies, int> playersCount, float imitationStrength);

float playerFitness(Player player, float totalPlayers,
                    std::map<Umpire::Strategies,
                            std::map<Player::Strategies,
                                    std::map<Player::Strategies, float>
                            >
                    > playersPayoffMatrix, float totalUmpires, std::map<Player::Strategies, int> playerCount,
                    std::map<Umpire::Strategies, int> umpireCount);

float umpireFitness(Umpire umpire, float totalUmpires,
                    std::map<Umpire::Strategies,
                            std::map<Player::Strategies,
                                    std::map<Player::Strategies, float>
                            >
                    > umpiresPayoffMatrix,
                    float totalPlayers, std::map<Umpire::Strategies, int> umpireCount,
                    std::map<Player::Strategies, int> playerCount);

std::vector<Umpire> setupUmpires(std::map<Umpire::Strategies, int> populationMap);

std::vector<Player> setupPlayers(std::map<Player::Strategies, int> populationMap);

std::vector<Umpire> getUmpiresWithOtherStrategies(std::vector<Umpire> &umpires, Umpire &umpire);

std::vector<Player> getPlayersWithOtherStrategies(std::vector<Player> players, Player player);

void shuffleAgents(std::vector<Umpire> &umpires, std::vector<Player> &players, std::vector<Agents> &agentSlots);

void printFrequencies(std::ofstream &outfile,
                      std::map<Player::Strategies, int> &playersCount,
                      float totalPlayers,
                      std::map<Umpire::Strategies, int> &umpiresCount,
                      float totalUmpires,
                      int generation);

void printHeader(std::ofstream &outfile);

//std::map<Agents, std::variant<
//        std::map<Umpire::Strategies, int>,
//        std::map<Player::Strategies, int>
//>> setupPopulation(std::map<Agents,
//        std::variant<
//                std::map<Umpire::Strategies, int>,
//                std::map<Player::Strategies, int>
//        >
//> agentsNumber);

#endif //PROJECT2_UTILS_H
