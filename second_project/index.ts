import {Umpire, UmpireStrategies} from "./population/Umpire";
import {Player, PlayerStrategies} from "./population/Player";
import {count, randomInt, randomIntInc, shuffle} from "./utils";
import {playerPayoffMatrix} from "./payoffMatrices/players";
import {umpirePayoffMatrix} from "./payoffMatrices/umpires";

const setupPopulation = (
    umpireNumbers: { [key in keyof typeof UmpireStrategies]: number },
    playerNumbers: { [key in keyof typeof PlayerStrategies]: number },
): { umpires: Umpire[], players: Player[] } => {
    // decide the number of players in all player strategies
    // decide the number of umpires in all umpire strategies
    // get the list of strategies and for each strategy
    // create an array with elements of similar strategy
    // merge the arrays
    // shuffle the arrays

    const umpireEnumKeys = Object.keys(UmpireStrategies);
    const playerEnumKeys = Object.keys(PlayerStrategies);

    const umpires = shuffle(
        umpireEnumKeys
            .map(umpireEnumKey => Array(umpireNumbers[umpireEnumKey]).fill(new Umpire(UmpireStrategies[umpireEnumKey])))
            .flat());
    const players = shuffle(playerEnumKeys.map(playerEnumKey => Array(playerNumbers[playerEnumKey]).fill(new Player(PlayerStrategies[playerEnumKey]))).flat());
    return {umpires, players};
};


// const setupGamePayoffs = ({ a, b, c, d, e, f, g, h }: { [key: any]: number }) => { a, b, c, d, e, f, g, h }
const numberOfUmpires = 1000;
const numberOfPlayers = 5000;
const generations = 100;

const imitationStrength = 10000;

const playerExplorationRate = 0.01;
const umpireExplorationRate = 0.05;

const imitationRate = (imitationStrength, agentOnePayoff, agentTwoPayoff) => 1 / (1 + Math.exp(imitationStrength * (agentOnePayoff - agentTwoPayoff)));

let umpireNumbers: { [key in keyof typeof UmpireStrategies]: number } = {
    Honest: 50 / 100 * numberOfUmpires,
    Corrupt: 50 / 100 * numberOfUmpires
};
const playerNumbers: { [key in keyof typeof PlayerStrategies]: number } = {
    PrudentCooperator: 0 * numberOfPlayers,
    PrudentDefector: 0 * numberOfPlayers,
    OptimisticCooperator: 100 / 100 * numberOfPlayers,
    OptimisticDefector: 0 / 100 * numberOfPlayers
};

const {umpires, players} = setupPopulation(
    umpireNumbers,
    playerNumbers
);

const totalPlayers = Object.values(playerNumbers).reduce((a, b) => a + b, 0);
const totalUmpires = Object.values(umpireNumbers).reduce((a, b) => a + b, 0);

const playerPayoff = (umpire: Umpire, players: Player[]) => playerPayoffMatrix[umpire.strategy][players[0].strategy][players[1].strategy];
const umpirePayoff = (umpire: Umpire, players: Player[]) => umpirePayoffMatrix[umpire.strategy][players[0].strategy][players[1].strategy];

// let population: Umpire[] | Player[];

// for a given number of generations where all players and umpires are able to change their behaviour
for (let i = 0; i < numberOfPlayers * numberOfUmpires * generations; i++) {
    if (randomIntInc(0, 100) / 100 < 50 / 100) {

        // TODO: PRA: NOT numberOfPlayers * numberOfUmpires * generations
        // TODO: PRA: JUST generations
        // TODO: PRA: UMPIRES PLAY AFTER PLAYERS
        // TODO: PRA: SHUFFLE after the loop
        // console.log("UMPIRES");
        // choose 2 umpires
        const j = randomInt(0, umpires.length);
        const k = randomInt(0, umpires.length);

        // if they are the same or their strategies are the same, continue
        // if (k === j || umpires[j].strategy === umpires[k].strategy) {
        //   continue;
        // }

        const umpireOne = umpires[j];
        const umpireTwo = umpires[k];

        // choose 2 players
        const l = randomInt(0, players.length);
        const m = randomInt(0, players.length);

        const playerOne = players[l];
        // const playerTwo = l === m ? playerOne : players[m]
        const playerTwo = players[m];

        // compute the umpire payoffs
        const umpireOnePayoff = umpirePayoff(umpireOne, [playerOne, playerTwo]);
        const umpireTwoPayoff = umpirePayoff(umpireTwo, [playerOne, playerTwo]);

        // if (umpireOnePayoff > umpireTwoPayoff) {

        if (randomIntInc(0, 100) / 100 < umpireExplorationRate) {
            // exploration
            const availableUmpireStrategies: UmpireStrategies[] = Object.values(UmpireStrategies).filter(strategy => strategy !== umpires[j].strategy) as UmpireStrategies[];
            umpires[j].strategy = availableUmpireStrategies[randomInt(0, availableUmpireStrategies.length)];
            // console.log(`Umpire ${umpires[j].strategy} explores ${umpires[k].strategy}`);

            continue;
        }

        // TODO: PRA: SHOULD BE THE FIT, NOT THE PAYOFF

        if (randomIntInc(0, 100) / 100 < imitationRate(imitationStrength, umpireOnePayoff, umpireTwoPayoff)) {
            // imitation
            umpires[j] = umpires[k];
            // console.log(`Umpire ${umpires[j].strategy} imitates ${umpires[k].strategy}`);
            continue;
        }

        // }

    } else {
        // choose 2 players
        const l = randomInt(0, players.length);
        const m = randomInt(0, players.length);

        // if they are the same or their strategies are the same, continue
        // if (l === m || players[l].strategy === players[m].strategy) {
        //   continue;
        // }

        const playerOne = players[l];
        // const playerTwo = l === m ? playerOne : players[m]
        const playerTwo = players[m];

        // choose an umpire
        const j = randomInt(0, umpires.length);
        const umpire = umpires[j];

        // compute the umpire payoffs
        const playerOnePayoff = playerPayoff(umpire, [playerOne, playerTwo]);
        const playerTwoPayoff = playerPayoff(umpire, [playerOne, playerTwo].reverse());

        // if (playerOnePayoff > playerTwoPayoff) {

        if (randomIntInc(0, 100) / 100 < playerExplorationRate) {
            // exploration
            const availablePlayerStrategies: PlayerStrategies[] = Object.values(PlayerStrategies).filter(strategy => strategy !== players[l].strategy) as PlayerStrategies[];
            players[l].strategy = availablePlayerStrategies[randomInt(0, availablePlayerStrategies.length)];
            // console.log(`Player ${players[l].strategy} explores ${players[l].strategy}`);
            continue;
        }

        if (randomIntInc(0, 100) / 100 < imitationRate(imitationStrength, playerOnePayoff, playerTwoPayoff)) {
            // imitation
            players[l] = players[m];
            // console.log(`Player ${players[l].strategy} imitates ${players[l].strategy}`);
            continue;
        }

        // }
    }

    if (i % 10 == 0) {
        const playerCount = count(players);
        const umpireCount = count(umpires);
        const playerStrategyCount = Object.keys(playerNumbers).map((key) => `${key}: ${playerCount[key] || `   0`}`).join(" | ");
        const umpireStrategyCount = Object.keys(umpireNumbers).map((key) => `${key}: ${umpireCount[key] || `   0`}`).join(" | ");
        console.log(`i = ${i} | ${playerStrategyCount} | ${umpireStrategyCount}`);
        // console.log(`i = ${i}`);
    }


// if umpires are chosen
// i need 2 umpires to compare them
// and 2 players to use in both

// if players are chosen
// i need 2 players
// but only 1 umpire

// choose 2 indexes

// console.log(totalPlayers * totalUmpires * generations)

// compute the fitness of the players


}
