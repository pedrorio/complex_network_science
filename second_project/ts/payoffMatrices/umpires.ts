import { UmpireStrategies } from "../population/Umpire";
import { PlayerStrategies } from "../population/Player";

const { a, b, c, f, h } = { a: 2, b: 0.2, c: 0.5, f: 0.2, h: 0.1 }


export const umpirePayoffMatrix: {
  [key in keyof typeof UmpireStrategies]: {
    [key in keyof typeof PlayerStrategies]: {
      [key in keyof typeof PlayerStrategies]: number
    }
  }
} = {
  Honest: {
    OptimisticCooperator: {
      OptimisticCooperator: 2 * f,
      PrudentCooperator: 2 * f,
      OptimisticDefector: 2 * f,
      PrudentDefector: 0
    },
    PrudentCooperator: {
      OptimisticCooperator: 2 * f,
      PrudentCooperator: 2 * f,
      OptimisticDefector: 2 * f,
      PrudentDefector: 0
    },
    OptimisticDefector: {
      OptimisticCooperator: 2 * f,
      PrudentCooperator: 2 * f,
      OptimisticDefector: 2 * f,
      PrudentDefector: 0
    },
    PrudentDefector: {
      OptimisticCooperator: 0,
      PrudentCooperator: 0,
      OptimisticDefector: 0,
      PrudentDefector: 0
    }
  },
  Corrupt: {
    OptimisticCooperator: {
      OptimisticCooperator: 2 * f,
      PrudentCooperator: 0,
      OptimisticDefector: 2 * f + b,
      PrudentDefector: 2 * f + b
    },
    PrudentCooperator: {
      OptimisticCooperator: 0,
      PrudentCooperator: 0,
      OptimisticDefector: 0,
      PrudentDefector: 0
    },
    OptimisticDefector: {
      OptimisticCooperator: 2 * f + b,
      PrudentCooperator: 0,
      OptimisticDefector: 2 * f + 2 * b,
      PrudentDefector: 2 * f + 2 * b
    },
    PrudentDefector: {
      OptimisticCooperator: 2 * f + b,
      PrudentCooperator: 0,
      OptimisticDefector: 2 * f + 2 * b,
      PrudentDefector: 2 * f + 2 * b,
    }
  }
};
