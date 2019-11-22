export enum PlayerStrategies {
  OptimisticCooperator = "OptimisticCooperator",
  PrudentCooperator = "PrudentCooperator",
  OptimisticDefector = "OptimisticDefector",
  PrudentDefector = "PrudentDefector",
}

export class Player {
  strategy: PlayerStrategies;
  
  constructor(strategy: PlayerStrategies) {
    this.strategy = strategy;
  }
  
}
