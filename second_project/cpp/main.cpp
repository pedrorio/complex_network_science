#include <iostream>
#include <vector>
#include <random>
#include <map>
#include <fstream>

#include "Player.h"
#include "Umpire.h"

#include "playerPayoffs.h"
#include "umpirePayoffs.h"
#include "utils.h"

std::vector<Umpire> setupUmpires(std::map<Umpire::Strategies, int> populationMap) {
    std::vector<Umpire> umpires;

    for (Umpire::Strategies umpireStrategy = Umpire::Strategies(0);
         umpireStrategy <= Umpire::Strategies::Last;
         umpireStrategy = static_cast<Umpire::Strategies>(static_cast<int>(umpireStrategy) + 1)) {

        std::vector<Umpire> umpiresWithStrategy(populationMap[umpireStrategy], Umpire(umpireStrategy));
        umpires.insert(std::end(umpires), std::begin(umpiresWithStrategy), std::end(umpiresWithStrategy));
    }

    auto random = std::default_random_engine{};
    std::shuffle(std::begin(umpires), std::end(umpires), random);

    return umpires;
}

std::vector<Player> setupPlayers(std::map<Player::Strategies, int> populationMap) {
    std::vector<Player> players;

    for (Player::Strategies playerStrategy = Player::Strategies(0);
         playerStrategy <= Player::Strategies::Last;
         playerStrategy = static_cast<Player::Strategies>(static_cast<int>(playerStrategy) + 1)) {

        std::vector<Player> playersWithStrategy(populationMap[playerStrategy], Player(playerStrategy));
        players.insert(std::end(players), std::begin(playersWithStrategy), std::end(playersWithStrategy));
    }

    auto random = std::default_random_engine{};
    std::shuffle(std::begin(players), std::end(players), random);

    return players;
}

int main() {

    std::cout << "Start program." << std::endl;

    std::ofstream outfile;
    outfile.open("output.txt");
    outfile << "Start program." << std::endl;

    float b, c, f, h, a;
    a = 2, b = 0.2, c = 0.5, f = 0.2, h = 0.1;

    std::map<Umpire::Strategies,
            std::map<Player::Strategies,
                    std::map<Player::Strategies, float>
            >
    > playersPayoff = playersPayoffMatrix(b, c, f, h, a);
    std::map<Umpire::Strategies,
            std::map<Player::Strategies,
                    std::map<Player::Strategies, float>
            >
    > umpiresPayoff = umpiresPayoffMatrix(b, c, f, h, a);

    int numberOfGenerations = 1000;
    float imitationStrength = 1.0;

    float explorationProbability = 0.5;

    std::map<Player::Strategies, int> playersMap = {
            {Player::Strategies::OptimisticCooperator, 10},
            {Player::Strategies::OptimisticDefector,   10},
            {Player::Strategies::PrudentCooperator,    10},
            {Player::Strategies::PrudentDefector,      10}
    };

    std::map<Umpire::Strategies, int> umpiresMap = {
            {Umpire::Strategies::Corrupt, 10},
            {Umpire::Strategies::Honest,  10}
    };

    std::vector<Player> players = setupPlayers(playersMap);
    std::vector<Umpire> umpires = setupUmpires(umpiresMap);

//    std::ofstream outfile;
//    outfile.open("output.txt");
//    outfile << "HELLO WORLD";
//    outfile.close();

    std::vector<int> playerIndexes = range(0, players.size() - 1);
    std::vector<int> umpireIndexes = range(0, umpires.size() - 1);

    for (auto g: range(1, numberOfGenerations)) {
        std::cout << "players size " << players.size() << std::endl;
        std::cout << "umpires size " << umpires.size() << std::endl;

        for (auto j: umpireIndexes) {
            Umpire umpireOne = umpires[j];

            std::vector<int> otherUmpireIndexes(umpireIndexes.size() - 1);
            std::copy_if(umpireIndexes.begin(), umpireIndexes.end(),
                         otherUmpireIndexes.begin(),
                         [j](int i) { return (i != j); });

            int umpireTwoIndex = randomElement(otherUmpireIndexes);
            Umpire umpireTwo = umpires[umpireTwoIndex];

            int playerOneIndex = randomElement(playerIndexes);
            Player playerOne = players[playerOneIndex];

            std::vector<int> otherPlayerIndexes(playerIndexes.size() - 1);
            std::copy_if(playerIndexes.begin(), playerIndexes.end(),
                         otherPlayerIndexes.begin(),
                         [playerOneIndex](int i) { return (i != playerOneIndex); });

            int playerTwoIndex = randomElement(otherPlayerIndexes);
            Player playerTwo = players[playerTwoIndex];

            float umpireOneFitness = umpireFitness(playerOne, playerTwo, players, umpireOne, umpireTwo, umpires,
                                                   umpiresPayoff);
            float umpireTwoFitness = umpireFitness(playerOne, playerTwo, players, umpireTwo, umpireOne, umpires,
                                                   umpiresPayoff);

            float umpireOneImitationProbability = imitationProbability(imitationStrength, umpireOneFitness,
                                                                       umpireTwoFitness);

            float imitationRealization = random(0, 100) / 100.0;
            float experimentationRealization = random(0, 100) / 100.0;

            if (imitationRealization < umpireOneImitationProbability) {
                umpires[j] = umpires[umpireTwoIndex];
            }

            if (experimentationRealization < explorationProbability) {
                umpires[j] = umpires[umpireTwoIndex];
            }

        }

        for (auto i: playerIndexes) {
            Player playerOne = players[i];

            std::vector<int> otherPlayerIndexes(playerIndexes.size() - 1);
            std::copy_if(playerIndexes.begin(), playerIndexes.end(),
                         otherPlayerIndexes.begin(),
                         [i](int j) { return (j != i); });

            int playerTwoIndex = randomElement(otherPlayerIndexes);
            Player playerTwo = players[playerTwoIndex];

            int umpireOneIndex = randomElement(umpireIndexes);
            Umpire umpireOne = umpires[umpireOneIndex];

            float playerOneFitness = playerFitness(playerOne, playerTwo, players, umpireOne, playersPayoff);
            float playerTwoFitness = playerFitness(playerTwo, playerOne, players, umpireOne, playersPayoff);

            float playerOneImitationProbability = imitationProbability(imitationStrength, playerOneFitness,
                                                                       playerTwoFitness);

            float imitationRealization = random(0, 100) / 100.0;
            float experimentationRealization = random(0, 100) / 100.0;

            if (imitationRealization < playerOneImitationProbability) {
                players[i] = players[playerTwoIndex];
            }

            if (experimentationRealization < explorationProbability) {
                players[i] = players[playerTwoIndex];
            }
        }

        auto random = std::default_random_engine{};
        std::shuffle(std::begin(umpires), std::end(umpires), random);
        std::shuffle(std::begin(players), std::end(players), random);


        std::cout << "G " << g << " UMPIRES";
        outfile << "G " << g << " UMPIRES";
        for (Umpire agent: umpires) {
            std::cout << " | " << static_cast<int>(agent.strategy);
            outfile << " | " << static_cast<int>(agent.strategy);
        }
        std::cout << std::endl;
        outfile << std::endl;

        std::cout << "G " << g << " PLAYERS";
        outfile << "G " << g << " PLAYERS";
        for (Player agent: players) {
            std::cout << " | " << static_cast<int>(agent.strategy);
            outfile << " | " << static_cast<int>(agent.strategy);
        }
        std::cout << std::endl;
        outfile << std::endl;

    }

    outfile << "End program." << std::endl;
    outfile.close();

    std::cout << "End program." << std::endl;
    return 0;
}