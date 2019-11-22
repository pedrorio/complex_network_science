//
// Created by Pedro Rio on 21/11/2019.
//

#include "utils.h"

int randomElement(std::vector<int> otherPlayerIndexes) {
    std::vector<int> sampleIndexes;
    std::sample(
            otherPlayerIndexes.begin(),
            otherPlayerIndexes.end(),
            std::back_inserter(sampleIndexes),
            1,
            std::mt19937{std::random_device{}()}
    );
    return sampleIndexes[0];
}

int random(int begin, int end) {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(begin, end);
    return std::bind(distribution, generator)();
}

std::vector<int> range(int firstNumber, int lastNumber) {
    std::vector<int> otherPlayerIndexes;
    for (int i = firstNumber; i <= lastNumber; i++)
        otherPlayerIndexes.push_back(i);

    return otherPlayerIndexes;
}

float imitationProbability(float imitationStrength, float agentOneFitness, float agentTwoFitness) {
    return 1 / (1 + std::exp(imitationStrength * (agentOneFitness - agentTwoFitness)));
}

float playerPayoff(
        Player playerOne, Player playerTwo, Umpire umpire,
        std::map<Umpire::Strategies,
                std::map<Player::Strategies,
                        std::map<Player::Strategies, float>
                >

        > playersPayoffMatrix
) {
    return playersPayoffMatrix[umpire.strategy][playerOne.strategy][playerTwo.strategy];
}

float umpirePayoff(
        Player playerOne, Player playerTwo, Umpire umpire,
        std::map<Umpire::Strategies,
                std::map<Player::Strategies,
                        std::map<Player::Strategies, float>
                >

        > umpiresPayoffMatrix
) {
    return umpiresPayoffMatrix[umpire.strategy][playerOne.strategy][playerTwo.strategy];
}

std::map<Player::Strategies, int> countPlayers(std::vector<Player> players) {
    std::map<Player::Strategies, int> count;
    for (Player::Strategies strategy = Player::Strategies(0);
         strategy <= Player::Strategies::Last;
         strategy = static_cast<Player::Strategies>(static_cast<int>(strategy) + 1)) {

        count[strategy] = std::count_if(
                players.begin(), players.end(),
                [strategy](Player player) { return (player.strategy == strategy); }
        );
    }
    return count;
}


std::map<Umpire::Strategies, int> countUmpires(std::vector<Umpire> umpires) {
    std::map<Umpire::Strategies, int> count;
    for (Umpire::Strategies strategy = Umpire::Strategies(0);
         strategy <= Umpire::Strategies::Last;
         strategy = static_cast<Umpire::Strategies>(static_cast<int>(strategy) + 1)) {

        count[strategy] = std::count_if(
                umpires.begin(), umpires.end(),
                [strategy](Umpire umpire) { return (umpire.strategy == strategy); }
        );
    }
    return count;
}

float playerFitness(Player playerOne, Player playerTwo, std::vector<Player> players, Umpire umpire,
                    std::map<Umpire::Strategies,
                            std::map<Player::Strategies,
                                    std::map<Player::Strategies, float>
                            >
                    > playersPayoffMatrix) {
    std::map<Player::Strategies, int> count = countPlayers(players);

    float playerOnePayoff = playerPayoff(playerOne, playerTwo, umpire, playersPayoffMatrix);
    float playerTwoPayoff = playerPayoff(playerTwo, playerOne, umpire, playersPayoffMatrix);

    return count[playerOne.strategy] * playerOnePayoff + count[playerTwo.strategy] * playerTwoPayoff;
}

float umpireFitness(Player playerOne, Player playerTwo, std::vector<Player> players, Umpire umpireOne, Umpire umpireTwo, std::vector<Umpire> umpires,
                    std::map<Umpire::Strategies,
                            std::map<Player::Strategies,
                                    std::map<Player::Strategies, float>
                            >
                    > umpiresPayoffMatrix) {

    std::map<Umpire::Strategies, int> count = countUmpires(umpires);

    float umpireOnePayoff = umpirePayoff(playerOne, playerTwo, umpireOne, umpiresPayoffMatrix);
    float umpireTwoPayoff = umpirePayoff(playerTwo, playerOne, umpireTwo, umpiresPayoffMatrix);

    return count[umpireOne.strategy] * umpireOnePayoff + count[umpireTwo.strategy] * umpireTwoPayoff;

}