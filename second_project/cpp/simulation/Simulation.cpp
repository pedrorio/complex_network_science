//
// Created by Pedro Rio on 06/12/2019.
//

#include "Simulation.h"


void simulation(float b, float c, float f, float h, float A, float B, float p, float T, float imitationStrength,
                float playerExplorationProbability, float umpireExplorationProbability,
                int timeStep, int numberOfGenerations, int OC, int PC, int OD, int PD, int H, int C, std::string subPath
) {

    std::stringstream directoryStream;
    std::stringstream systemCommandStream;
    std::ofstream paramFile;
    std::ofstream dataFile;
    std::stringstream pythonScriptStream;

    std::cout << "Start program." << std::endl;

    std::time_t start_time = std::time(nullptr);
    directoryStream << "./simulations/" << subPath << start_time;
    std::string directoryPath = directoryStream.str();

    systemCommandStream << "mkdir" << " " << directoryPath;
    std::string systemCommand = systemCommandStream.str();

    int totalCharactersInSystemCommand = systemCommand.length();
    char charactersInSystemCommand[totalCharactersInSystemCommand + 1];
    strcpy(charactersInSystemCommand, systemCommand.c_str());

    system(charactersInSystemCommand);

    std::string paramFileName = directoryPath + "/" + "params.csv";
    paramFile.open(paramFileName);
    printParamHeaders(paramFile);
    printParams(paramFile, b, c, f, h, A, B, playerExplorationProbability, umpireExplorationProbability,
                imitationStrength, p, T);
    paramFile.close();

    std::string dataFileName = directoryPath + "/" + "data.csv";
    dataFile.open(dataFileName);
    printHeader(dataFile);

    auto playersPayoff = uncertainPlayersPayoffMatrix(b, c, f, h, A, B, p);
    auto umpiresPayoff = uncertainUmpiresPayoffMatrix(b, c, f, h, A, B, p);
//    auto umpiresPayoff = punishmentUmpiresPayoffMatrix(b, c, f, h, A, B, T);

    std::map<Player::Strategies, int> playersMap = {
            {Player::Strategies::OptimisticCooperator, OC},
            {Player::Strategies::OptimisticDefector,   OD},
            {Player::Strategies::PrudentCooperator,    PC},
            {Player::Strategies::PrudentDefector,      PD}
    };

    std::map<Umpire::Strategies, int> umpiresMap = {
            {Umpire::Strategies::Corrupt, C},
            {Umpire::Strategies::Honest,  H}
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
    std::map<Player::Strategies, int> playersCount = countPlayers(players);
    std::map<Umpire::Strategies, int> umpiresCount = countUmpires(umpires);
    printFrequencies(dataFile, playersCount, totalNumberOfPlayers, umpiresCount, totalNumberOfUmpires,
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
            float imitationRealization, experimentationRealization;
            imitationRealization = random(0, 100) / 100.0;
            experimentationRealization = random(0, 100) / 100.0;
            if (agent == Agents::Umpire) {
                Umpire &umpire = umpires[umpireIndex];
                if (experimentationRealization < umpireExplorationProbability) {
                    Umpire::Strategies otherStrategy = getOtherUmpireStrategy(umpire.strategy, umpiresCount);
                    umpiresCount[umpire.strategy]--;
                    umpiresCount[otherStrategy]++;
                    umpire.strategy = otherStrategy;
                } else {
                    int otherUmpireIndex = randomElement(otherIndexes({umpireIndex}, umpireIndexes));
                    Umpire &otherUmpire = umpires[otherUmpireIndex];
                    if (umpire.strategy == otherUmpire.strategy) {
                        umpireIndex++;
                        continue;
                    }
                    float fitnessUmpire = umpireFitness(umpire, totalNumberOfUmpires, umpiresPayoff,
                                                        totalNumberOfPlayers, umpiresCount,
                                                        playersCount);
                    float fitnessPopulationUmpire = umpirePopulationFitness(totalNumberOfUmpires, umpiresPayoff,
                                                                            totalNumberOfPlayers, umpiresCount,
                                                                            playersCount);
                    float umpireImitationProbability = imitationProbability(imitationStrength, fitnessUmpire,
                                                                            fitnessPopulationUmpire);
                    if (imitationRealization < umpireImitationProbability) {
                        umpiresCount[umpire.strategy]++;
                        umpiresCount[otherUmpire.strategy]--;
                        otherUmpire = umpire;
                    }
                }
                umpireIndex++;
            } else if (agent == Agents::Player) {
                Player &player = players[playerIndex];
                if (experimentationRealization < playerExplorationProbability) {
                    Player::Strategies otherStrategy = getOtherPlayerStrategy(player.strategy, playersCount);
                    playersCount[player.strategy]--;
                    playersCount[otherStrategy]++;
                    player.strategy = otherStrategy;
                } else {
                    int otherPlayerIndex = randomElement(otherIndexes({playerIndex}, playerIndexes));
                    Player &otherPlayer = players[otherPlayerIndex];
                    if (player.strategy == otherPlayer.strategy) {
                        playerIndex++;
                        continue;
                    }
                    float fitnessPlayer = playerFitness(player, totalNumberOfPlayers,
                                                        playersPayoff, totalNumberOfUmpires, playersCount,
                                                        umpiresCount);
                    float fitnessPopulationPlayer = playerPopulationFitness(totalNumberOfPlayers, playersPayoff,
                                                                            totalNumberOfUmpires, playersCount,
                                                                            umpiresCount);
                    float playerImitationProbability = imitationProbability(imitationStrength, fitnessPlayer,
                                                                            fitnessPopulationPlayer);
                    if (imitationRealization < playerImitationProbability) {
                        playersCount[player.strategy]++;
                        playersCount[otherPlayer.strategy]--;
                        otherPlayer = player;
                    }
                }
                playerIndex++;
            };
        }
        shuffleAgents(umpires, players, agentSlots);
        if (generation % timeStep == 0) {
            printFrequencies(dataFile, playersCount, totalNumberOfPlayers, umpiresCount, totalNumberOfUmpires,
                             generation, numberOfGenerations);
        }
    }

//    std::time_t end_time = std::time(nullptr);
//    std::cout << (start_time - end_time) << std::endl;
//    std::cout << (end_time - start_time) / (float) (numberOfGenerations * totalNumberOfAgents) << " per generation"
//              << std::endl;
//    std::cout << (end_time - start_time) / (float) numberOfGenerations << " per generation" << std::endl;
//    std::cout << (end_time - start_time) / (float) timeStep << " per time step" << std::endl;

    dataFile.close();
    std::cout << "End program." << std::endl;
//    std::cout << start_time;


    pythonScriptStream << "./py/graphs.py" << " " << directoryPath;
    std::string pythonScriptCommand = pythonScriptStream.str();

    int totalCharactersInPythonScriptCommand = pythonScriptCommand.length();
    char charactersInPythonScriptCommand[totalCharactersInPythonScriptCommand + 1];
    strcpy(charactersInPythonScriptCommand, pythonScriptCommand.c_str());
    system(charactersInPythonScriptCommand);
}