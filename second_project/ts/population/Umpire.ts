export enum UmpireStrategies {
  Honest = "Honest",
  Corrupt = "Corrupt",
}

export class Umpire {
  strategy: UmpireStrategies;
  
  constructor(strategy: UmpireStrategies) {
    this.strategy = strategy;
  }
  
}
