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

    float b, c, f, h, a;
    a = 2, b = 0.2, c = 0.5, f = 0.2, h = 0.1;

    int numberOfGenerations = 200;
    float imitationStrength = 1.0;

    float explorationProbability = 0.10;

    auto playersPayoff = playersPayoffMatrix(b, c, f, h, a);
    auto umpiresPayoff = umpiresPayoffMatrix(b, c, f, h, a);

    std::map<Player::Strategies, int> playersMap = {
            {Player::Strategies::OptimisticCooperator, 100},
            {Player::Strategies::OptimisticDefector,   100},
            {Player::Strategies::PrudentCooperator,    100},
            {Player::Strategies::PrudentDefector,      100}
    };

    std::map<Umpire::Strategies, int> umpiresMap = {
            {Umpire::Strategies::Corrupt, 100},
            {Umpire::Strategies::Honest,  100}
    };

    std::vector<Player> players = setupPlayers(playersMap);
    std::vector<Umpire> umpires = setupUmpires(umpiresMap);
    std::vector<Agents> agentSlots = setupAgentSlots(players, umpires);

    int numberOfPlayers = players.size();
    float totalNumberOfPlayers = static_cast<float>(numberOfPlayers);

    int numberOfUmpires = umpires.size();
    float totalNumberOfUmpires = static_cast<float>(numberOfUmpires);

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
            float imitationRealization = random(0, 100) / 100.0;
            float experimentationRealization = random(0, 100) / 100.0;

            if (agent == Agents::Umpire) {
                Umpire &umpire = umpires[umpireIndex];

                if (experimentationRealization < explorationProbability) {
                    std::vector<Umpire> umpiresWithOtherStrategies = getUmpiresWithOtherStrategies(umpires, umpire);
                    Umpire &otherUmpire = umpiresWithOtherStrategies[random(0, umpiresWithOtherStrategies.size() - 1)];
                    umpire = otherUmpire;

                    umpiresCount[umpire.strategy]--;
                    umpiresCount[otherUmpire.strategy]++;
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

                    if (imitationRealization < (1 - explorationProbability) * umpireImitationProbability) {
                        umpire = otherUmpire;
                        umpiresCount[umpire.strategy]--;
                        umpiresCount[otherUmpire.strategy]++;
                    }
                }

                umpireIndex++;
            } else if (agent == Agents::Player) {
                Player &player = players[playerIndex];

                if (experimentationRealization < explorationProbability) {
                    std::vector<Player> playersWithOtherStrategies = getPlayersWithOtherStrategies(players, player);
                    Player &otherPlayer = playersWithOtherStrategies[random(0, playersWithOtherStrategies.size() - 1)];

                    player = otherPlayer;
                    playersCount[player.strategy]++;
                    playersCount[otherPlayer.strategy]--;
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

                    if (imitationRealization < (1 - explorationProbability) * playerImitationProbability) {
                        player = otherPlayer;
                        playersCount[player.strategy]--;
                        playersCount[otherPlayer.strategy]++;
                    }
                }

                playerIndex++;
            }
        }

        shuffleAgents(umpires, players, agentSlots);
//        if (generation % 10 == 0) {
            printFrequencies(outfile, playersCount, totalNumberOfPlayers, umpiresCount, totalNumberOfUmpires,
                             generation);
//        }
    }

    outfile.close();
    std::cout << "End program." << std::endl;
    return 0;
}