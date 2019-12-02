#include <iostream>
#include <vector>
#include <map>
#include <sys/stat.h>
#include <sstream>
#include <fstream>

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

    std::stringstream directoryStream;
    std::time_t time_t = std::time(nullptr);
    directoryStream << "../simulations/" << time_t;
    std::string directoryPath = directoryStream.str();

    std::stringstream systemCommandStream;
    systemCommandStream << "mkdir" << " " << directoryPath;
    std::string systemCommand = systemCommandStream.str();

    int totalCharactersInSystemCommand = systemCommand.length();
    char charactersInSystemCommand[totalCharactersInSystemCommand + 1];
    strcpy(charactersInSystemCommand, systemCommand.c_str());

    system(charactersInSystemCommand);

    int timeStep = 10000;

    float b, c, f, h, a, B;
    b = 1, c = f = 0.5, B = 0.2, h = 0.1, a = 2;

    int numberOfGenerations = pow(10, 5) * 3;
    float imitationStrength = pow(10, 10);

    float playerExplorationProbability = 0.001;
    float umpireExplorationProbability = 0.005;

    std::ofstream paramFile;
    std::string paramFileName = directoryPath + "/" + "params.csv";
    paramFile.open(paramFileName);
    printParamHeaders(paramFile);
    printParams(paramFile, b, c, f, h, a, B, playerExplorationProbability, umpireExplorationProbability,
                imitationStrength);
    paramFile.close();

    std::ofstream dataFile;
    std::string dataFileName = directoryPath + "/" + "data.csv";
    dataFile.open(dataFileName);
    printHeader(dataFile);

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

    printFrequencies(dataFile, initialPlayersCount, totalNumberOfPlayers, initialUmpiresCount, totalNumberOfUmpires,
                     0,
                     numberOfGenerations);

    for (auto generation: range(1, numberOfGenerations)) {

        int umpireIndex = 0;
        int playerIndex = 0;

        std::vector<int> selectedUmpireIndexes = {umpireIndex};
        std::vector<int> selectedPlayerIndexes = {playerIndex};

        std::map<Player::Strategies, int> playersCount = countPlayers(players);
        std::map<Umpire::Strategies, int> umpiresCount = countUmpires(umpires);

        for (auto agent: agentSlots) {

            float playerImitationRealization, umpireImitationRealization, playerExperimentationRealization, umpireExperimentationRealization;
            playerImitationRealization = umpireImitationRealization = random(0, 100) / 100.0;
            playerExperimentationRealization = umpireExperimentationRealization = random(0, 100) / 100.0;

            if (agent == Agents::Umpire) {
                Umpire &umpire = umpires[umpireIndex];

                if (umpireExperimentationRealization < umpireExplorationProbability) {
                    Umpire::Strategies otherStrategy = getOtherUmpireStrategy(umpire.strategy, umpiresCount);
                    umpiresCount[umpire.strategy]--;
                    umpiresCount[otherStrategy]++;
                    umpire.strategy = otherStrategy;
                } else {
                    float fitnessUmpire = umpireFitness(umpire, totalNumberOfUmpires, umpiresPayoff,
                                                        totalNumberOfPlayers, umpiresCount,
                                                        playersCount);
                    float fitnessPopulationUmpire = umpirePopulationFitness(totalNumberOfUmpires, umpiresPayoff, totalNumberOfPlayers, umpiresCount, playersCount);
                    float umpireImitationProbability = imitationProbability(imitationStrength, fitnessUmpire,
                                                                            fitnessPopulationUmpire);

                    if (umpireImitationRealization < umpireImitationProbability) {
                        int otherUmpireIndex = randomElement(otherIndexes(selectedUmpireIndexes, umpireIndexes));
                        Umpire &otherUmpire = umpires[otherUmpireIndex];

                        umpiresCount[umpire.strategy]++;
                        umpiresCount[otherUmpire.strategy]--;
                        otherUmpire = umpire;
                    }
                }

                umpireIndex++;
            } else if (agent == Agents::Player) {
                Player &player = players[playerIndex];

                if (playerExperimentationRealization < playerExplorationProbability) {
                    Player::Strategies otherStrategy = getOtherPlayerStrategy(player.strategy, playersCount);
                    playersCount[player.strategy]--;
                    playersCount[otherStrategy]++;
                    player.strategy = otherStrategy;
                } else {
                    float fitnessPlayer = playerFitness(player, totalNumberOfPlayers,
                                                        playersPayoff, totalNumberOfUmpires, playersCount,
                                                        umpiresCount);
                    float fitnessPopulationPlayer = playerPopulationFitness(totalNumberOfPlayers, playersPayoff,
                                                                            totalNumberOfUmpires, playersCount,
                                                                            umpiresCount);
                    float playerImitationProbability = imitationProbability(imitationStrength, fitnessPlayer,
                                                                            fitnessPopulationPlayer);

                    if (playerImitationRealization < playerImitationProbability) {
                        int otherPlayerIndex = randomElement(otherIndexes(selectedPlayerIndexes, playerIndexes));
                        Player &otherPlayer = players[otherPlayerIndex];

                        playersCount[player.strategy]++;
                        playersCount[otherPlayer.strategy]--;
                        otherPlayer = player;
                    }
                }

                playerIndex++;
            }
        }

        shuffleAgents(umpires, players, agentSlots);
        if (generation % timeStep == 0) {
            printFrequencies(dataFile, playersCount, totalNumberOfPlayers, umpiresCount, totalNumberOfUmpires,
                             generation, numberOfGenerations);
        }
    }

    dataFile.close();
    std::cout << "End program." << std::endl;
    return 0;
}