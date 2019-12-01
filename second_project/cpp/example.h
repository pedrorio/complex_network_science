//
// Created by Pedro Rio on 21/11/2019.
//

#ifndef PROJECT2_EXAMPLE_H
#define PROJECT2_EXAMPLE_H

#include <map>
#include <cmath>
#include <random>
#include "agents/players/Player.h"
#include "agents/umpires/Umpire.h"

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

std::vector<Agents> setupAgentSlots(const std::vector<Player> &players, const std::vector<Umpire> &umpires);

float imitationProbability(float imitationStrength, float agentOneFitness, float agentTwoFitness);

std::map<Player::Strategies, int> countPlayers(std::vector<Player> players);

std::map<Umpire::Strategies, int> countUmpires(std::vector<Umpire> umpires);

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
                                 float imitationStrength);

float umpireImitationProbability(Umpire umpire, Umpire otherUmpire,
                                 float totalNumberOfUmpires,
                                 const std::map<Umpire::Strategies,
                                         std::map<Player::Strategies,
                                                 std::map<Player::Strategies, float>
                                         >
                                 > &umpiresPayoff,
                                 float totalNumberOfPlayers,
                                 const std::map<Umpire::Strategies, int> &umpiresCount,
                                 const std::map<Player::Strategies, int> &playersCount,
                                 float imitationStrength);

float playerFitness(Player player,
                    float totalPlayers,
                    std::map<Umpire::Strategies,
                            std::map<Player::Strategies,
                                    std::map<Player::Strategies, float>
                            >
                    > playersPayoffMatrix,
                    float totalUmpires,
                    std::map<Player::Strategies, int> playerCount,
                    std::map<Umpire::Strategies, int> umpireCount);

float playerPopulationFitness(float totalPlayers,
                              std::map<Umpire::Strategies,
                                      std::map<Player::Strategies,
                                              std::map<Player::Strategies, float>
                                      >
                              > playersPayoffMatrix,
                              float totalUmpires,
                              std::map<Player::Strategies, int> playerCount,
                              std::map<Umpire::Strategies, int> umpireCount);

float umpireFitness(Umpire umpire, float totalUmpires,
                    std::map<Umpire::Strategies,
                            std::map<Player::Strategies,
                                    std::map<Player::Strategies, float>
                            >
                    > umpiresPayoffMatrix,
                    float totalPlayers,
                    std::map<Umpire::Strategies, int> umpireCount,
                    std::map<Player::Strategies, int> playerCount);

float umpirePopulationFitness(float totalUmpires,
                              std::map<Umpire::Strategies,
                                      std::map<Player::Strategies,
                                              std::map<Player::Strategies, float>
                                      >
                              > umpiresPayoffMatrix,
                              float totalPlayers,
                              std::map<Umpire::Strategies, int> umpireCount,
                              std::map<Player::Strategies, int> playerCount);

std::vector<Umpire> setupUmpires(std::map<Umpire::Strategies, int> populationMap);

std::vector<Player> setupPlayers(std::map<Player::Strategies, int> populationMap);

Umpire::Strategies getOtherUmpireStrategy(Umpire::Strategies strategy,
                                          std::map<Umpire::Strategies, int> &umpiresCount);

Player::Strategies getOtherPlayerStrategy(Player::Strategies strategy,
                                          std::map<Player::Strategies, int> &playersCount);

int getUmpireIndexFromOtherStrategies(std::vector<Umpire> &umpires, std::vector<int> &umpireIndexes,
                                      Umpire::Strategies &otherStrategy);

int getPlayerIndexFromOtherStrategies(std::vector<Player> &players, std::vector<int> &playerIndexes,
                                      Player::Strategies &otherStrategy);

void shuffleAgents(std::vector<Umpire> &umpires, std::vector<Player> &players, std::vector<Agents> &agentSlots);

void printFrequencies(std::ofstream &outfile,
                      std::map<Player::Strategies, int> &playersCount,
                      float totalPlayers,
                      std::map<Umpire::Strategies, int> &umpiresCount,
                      float totalUmpires, int generation, int numberOfGenerations);

void printHeader(std::ofstream &outfile);

void printParams(std::ofstream &outfile, float b, float c, float f, float h, float a, float B,
                 float playerExplorationProbability, float umpireExplorationProbability,
                 float imitationStrength);

void printParamHeaders(std::ofstream &outfile);

#endif //PROJECT2_EXAMPLE_H