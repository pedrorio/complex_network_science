#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <variant>
#include <sys/stat.h>
#include <sstream>

#include "agents/players/Player.h"
#include "agents/umpires/Umpire.h"
#include "agents/players/payoffsPlayer.h"
#include "agents/umpires/payoffsUmpire.h"
#include "agents/fitness.h"

#include "utils/utils.h"
#include "utils/logs.h"
#include "utils/counts.h"
#include "utils/other.h"
#include "utils/imitationProbabilities.h"

int main() {
    std::cout << "Start program." << std::endl;

    std::time_t time_t = std::time(nullptr);
    std::tm tm = *std::localtime(&time_t);

    std::stringstream directoryStream;
    directoryStream << "../simulations/" << std::put_time(&tm, "%H-%M-%S-%d-%m-%Y");

    std::string directoryPath;
    directoryPath = directoryStream.str();

    std::stringstream systemCommandStream;

    std::string systemCommand;
    systemCommand = systemCommandStream.str();

    int totalCharactersInSystemCommand = systemCommand.length();
    char charactersInSystemCommand[totalCharactersInSystemCommand + 1];
    strcpy(charactersInSystemCommand, systemCommand.c_str());

    system(charactersInSystemCommand);

    std::ofstream outfile;
    std::string fileName = directoryPath + "/" + "output.csv";
    outfile.open(fileName);

    printHeader(outfile);

    float b, c, f, h, a, B;
    b = 1, c = 0.5, f = 0.2, B = 0.2, h = 0.1, a = 2;

    int numberOfGenerations = pow(10, 5);
    float imitationStrength = pow(10, 10);

    float playerExplorationProbability = 0.001;
    float umpireExplorationProbability = 0.005;

    auto playersPayoff = playersPayoffMatrix(b, c, f, h, a, B);
    auto umpiresPayoff = umpiresPayoffMatrix(b, c, f, h, a, B);

    std::map<Player::Strategies, int> playersMap = {
            {Player::Strategies::OptimisticCooperator, 0},
            {Player::Strategies::OptimisticDefector,   50},
            {Player::Strategies::PrudentCooperator,    0},
            {Player::Strategies::PrudentDefector,      0}
    };

    std::map<Umpire::Strategies, int> umpiresMap = {
            {Umpire::Strategies::Corrupt, 10},
            {Umpire::Strategies::Honest,  0}
    };

    std::vector<Player> players = setupPlayers(playersMap);
    std::vector<Umpire> umpires = setupUmpires(umpiresMap);
    std::vector<Agents> agentSlots = setupAgentSlots(players, umpires);

    int numberOfPlayers = players.size();
    auto totalNumberOfPlayers = (float) (numberOfPlayers);

    int numberOfUmpires = umpires.size();
    auto totalNumberOfUmpires = (float) (numberOfUmpires);

    int totalNumberOfAgents = numberOfPlayers + numberOfUmpires;

    auto playerIndexes = range(0, numberOfPlayers - 1);
    auto umpireIndexes = range(0, numberOfUmpires - 1);
    auto agentIndexes = range(0, totalNumberOfAgents - 1);

    std::map<Player::Strategies, int> initialPlayersCount = countPlayers(players);
    std::map<Umpire::Strategies, int> initialUmpiresCount = countUmpires(umpires);

    printFrequencies(outfile, initialPlayersCount, totalNumberOfPlayers, initialUmpiresCount, totalNumberOfUmpires,
                         0, b, c, f, h, a, B, playerExplorationProbability, umpireExplorationProbability, imitationStrength);

    for (auto generation: range(1, numberOfGenerations)) {

        int umpireIndex = 0;
        int playerIndex = 0;

        std::vector<int> selectedUmpireIndexes = {umpireIndex};
        std::vector<int> selectedPlayerIndexes = {playerIndex};

        std::map<Player::Strategies, int> playersCount = countPlayers(players);
        std::map<Umpire::Strategies, int> umpiresCount = countUmpires(umpires);

        for (auto agent: agentSlots) {
            float playerImitationRealization = random(0, 100) / 100.0;
            float umpireImitationRealization = random(0, 100) / 100.0;
            float umpireExperimentationRealization = random(0, 100) / 100.0;
            float playerExperimentationRealization = random(0, 100) / 100.0;

            if (agent == Agents::Umpire) {
                Umpire &umpire = umpires[umpireIndex];

                if (umpireExperimentationRealization > umpireExplorationProbability) {
                    Umpire::Strategies otherStrategy = getOtherUmpireStrategy(umpire.strategy, umpiresCount);
//                    int otherUmpireIndex = getUmpireIndexFromOtherStrategies(umpires, umpireIndexes, otherStrategy);
//                    Umpire &otherUmpire = umpires[otherUmpireIndex];

//                    umpiresCount[umpire.strategy]++;
//                    umpiresCount[otherStrategy]--;
//                    otherUmpire = umpire;

                    umpiresCount[umpire.strategy]--;
                    umpiresCount[otherStrategy]++;
                    umpire.strategy = otherStrategy;
                } else {
                    int otherUmpireIndex = randomElement(otherIndexes(selectedUmpireIndexes, umpireIndexes));
                    Umpire &otherUmpire = umpires[otherUmpireIndex];

                    float fitnessUmpire = umpireFitness(umpire, totalNumberOfUmpires, umpiresPayoff,
                                                        totalNumberOfPlayers, umpiresCount,
                                                        playersCount);
                    float fitnessOtherUmpire = umpireFitness(otherUmpire, totalNumberOfUmpires, umpiresPayoff,
                                                             totalNumberOfPlayers, umpiresCount,
                                                             playersCount);

//                    float fitnessPopulationUmpire = umpirePopulationFitness(totalNumberOfUmpires, umpiresPayoff, totalNumberOfPlayers, umpiresCount, playersCount);

//                    float umpireImitationProbability = imitationProbability(imitationStrength, fitnessUmpire,
//                                                                            fitnessPopulationUmpire);

                    float umpireImitationProbability = imitationProbability(imitationStrength, fitnessUmpire,
                                                                            fitnessOtherUmpire);

                    if (umpireImitationRealization < umpireImitationProbability) {

//                        int otherUmpireIndex = randomElement(otherIndexes(selectedUmpireIndexes, umpireIndexes));
//                        Umpire &otherUmpire = umpires[otherUmpireIndex];

//                        umpiresCount[umpire.strategy]++;
//                        umpiresCount[otherUmpire.strategy]--;
//                        otherUmpire = umpire;


                        umpiresCount[umpire.strategy]--;
                        umpiresCount[otherUmpire.strategy]++;
                        umpire = otherUmpire;
                    }
                }

                umpireIndex++;
            } else if (agent == Agents::Player) {
                Player &player = players[playerIndex];

                if (playerExperimentationRealization < playerExplorationProbability) {

                    Player::Strategies otherStrategy = getOtherPlayerStrategy(player.strategy, playersCount);

//                    Player otherPlayer = getPlayerIndexFromOtherStrategies(players, otherStrategy);
//                    int otherPlayerIndex = getPlayerIndexFromOtherStrategies(players, playerIndexes, otherStrategy);
//                    Player &otherPlayer = players[otherPlayerIndex];

//                    playersCount[player.strategy]++;
//                    playersCount[otherStrategy]--;
//                    otherPlayer.strategy = player.strategy;

                    playersCount[player.strategy]--;
                    playersCount[otherStrategy]++;
                    player.strategy = otherStrategy;
                } else {
//                    int otherPlayerIndex = randomElement(otherIndexes(selectedPlayerIndexes, playerIndexes));
//                    Player &otherPlayer = players[otherPlayerIndex];

                    float fitnessPlayer = playerFitness(player, totalNumberOfPlayers,
                                                        playersPayoff, totalNumberOfUmpires, playersCount,
                                                        umpiresCount);

//                    float fitnessOtherPlayer = playerFitness(otherPlayer, totalNumberOfPlayers,
//                                                             playersPayoff, totalNumberOfUmpires, playersCount,
//                                                             umpiresCount);

                    float fitnessPopulationPlayer = playerPopulationFitness(totalNumberOfPlayers, playersPayoff,
                                                                            totalNumberOfUmpires, playersCount,
                                                                            umpiresCount);

//                    float playerImitationProbability = imitationProbability(imitationStrength, fitnessPlayer,
//                                                                            fitnessOtherPlayer);

                    float playerImitationProbability = imitationProbability(imitationStrength, fitnessPlayer,
                                                                            fitnessPopulationPlayer);

                    if (playerImitationRealization < playerImitationProbability) {

                        int otherPlayerIndex = randomElement(otherIndexes(selectedPlayerIndexes, playerIndexes));
                        Player &otherPlayer = players[otherPlayerIndex];

                        playersCount[player.strategy]++;
                        playersCount[otherPlayer.strategy]--;
                        otherPlayer = player;

//                        playersCount[player.strategy]--;
//                        playersCount[otherPlayer.strategy]++;
//                        player = otherPlayer;
                    }
                }

                playerIndex++;
            }
        }

        shuffleAgents(umpires, players, agentSlots);
        if (generation % 25 == 0) {
            printFrequencies(outfile, initialPlayersCount, totalNumberOfPlayers, initialUmpiresCount, totalNumberOfUmpires,
                             0, b, c, f, h, a, B, playerExplorationProbability, umpireExplorationProbability, imitationStrength);
        }
    }

    outfile.close();
    std::cout << "End program." << std::endl;
    return 0;
}