#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <variant>

#include "agents/Player.h"
#include "agents/Umpire.h"

#include "payoffs/playerPayoffs.h"
#include "payoffs/umpirePayoffs.h"

#include "utils/utils.h"

int main() {
    std::cout << "Start program." << std::endl;
    std::ofstream outfile;
    std::string fileName = "output.csv";
    outfile.open(fileName);

    printHeader(outfile);

    float b, c, f, h, a, B;
    b = 1, c = 0.5, f = 0.2, B = 0.2, h = 0.1, a = 2;


    int numberOfGenerations = 100000 * 3;
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

                if (umpireExperimentationRealization < umpireExplorationProbability) {
                    Umpire::Strategies otherStrategy = getOtherUmpireStrategy(umpire.strategy, umpiresCount);
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
                    float umpireImitationProbability = imitationProbability(imitationStrength, fitnessUmpire,
                                                                            fitnessOtherUmpire);

                    if (umpireImitationRealization < umpireImitationProbability) {
                        umpiresCount[umpire.strategy]--;
                        umpiresCount[otherUmpire.strategy]++;
                        umpire = otherUmpire;
                    }
                }

                umpireIndex++;
            } else if (agent == Agents::Player) {
                Player &player = players[playerIndex];

                if (playerExperimentationRealization < playerExplorationProbability) {

                    Player::Strategies otherplayerStrategy = getOtherPlayerStrategy(player.strategy, playersCount);
                    playersCount[player.strategy]--;
                    playersCount[otherplayerStrategy]++;
                    player.strategy = otherplayerStrategy;
                } else {
                    int otherPlayerIndex = randomElement(otherIndexes(selectedPlayerIndexes, playerIndexes));
                    Player &otherPlayer = players[otherPlayerIndex];

                    float fitnessPlayer = playerFitness(player, totalNumberOfPlayers,
                                                        playersPayoff, totalNumberOfUmpires, playersCount,
                                                        umpiresCount);
                    float fitnessOtherPlayer = playerFitness(otherPlayer, totalNumberOfPlayers,
                                                             playersPayoff, totalNumberOfUmpires, playersCount,
                                                             umpiresCount);

                    float playerImitationProbability = imitationProbability(imitationStrength, fitnessPlayer,
                                                                            fitnessOtherPlayer);

                    if (playerImitationRealization < playerImitationProbability) {
                        playersCount[player.strategy]--;
                        playersCount[otherPlayer.strategy]++;
                        player = otherPlayer;
                    }
                }

                playerIndex++;
            }
        }

        shuffleAgents(umpires, players, agentSlots);
        if (generation % 1000 == 0) {
            printFrequencies(outfile, playersCount, totalNumberOfPlayers, umpiresCount, totalNumberOfUmpires,
                             generation);
        }
    }

    outfile.close();
    std::cout << "End program." << std::endl;
    return 0;
}