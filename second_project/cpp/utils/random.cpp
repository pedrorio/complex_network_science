#include <iostream>
#include "random.h"

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

void shuffleAgents(std::vector<Umpire> &umpires, std::vector<Player> &players, std::vector<Agents> &agentSlots) {
    std::shuffle(std::begin(umpires), std::end(umpires), generator);
    std::shuffle(std::begin(players), std::end(players), generator);
    std::shuffle(std::begin(agentSlots), std::end(agentSlots), generator);
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