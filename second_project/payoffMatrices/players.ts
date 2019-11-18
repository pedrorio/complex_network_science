import { UmpireStrategies } from "../population/Umpire";
import { PlayerStrategies } from "../population/Player";

const { a, b, c, f, h } = { a: 2, b: 0.2, c: 0.5, f: 0.2, h: 0.1 }

export const playerPayoffMatrix: {
  [key in keyof typeof UmpireStrategies]: {
    [key in keyof typeof PlayerStrategies]: {
      [key in keyof typeof PlayerStrategies]: number
    }
  }
} = {
  Honest: {
    OptimisticCooperator: {
      OptimisticCooperator: b - c - f,
      PrudentCooperator: b - c - f - h,
      OptimisticDefector: b - f - a,
      PrudentDefector: -h
    },
    PrudentCooperator: {
      OptimisticCooperator: b - c - f,
      PrudentCooperator: b - c - f - h,
      OptimisticDefector: b - f - a,
      PrudentDefector: -h
    },
    OptimisticDefector: {
      OptimisticCooperator: -c - f,
      PrudentCooperator: -c - f - h,
      OptimisticDefector: -f - a,
      PrudentDefector: -h
    },
    PrudentDefector: {
      OptimisticCooperator: 0,
      PrudentCooperator: -h,
      OptimisticDefector: 0,
      PrudentDefector: -h
    }
  },
  Corrupt: {
    OptimisticCooperator: {
      OptimisticCooperator: b - c - f,
      PrudentCooperator: -h,
      OptimisticDefector: b - f - b,
      PrudentDefector: b - f - b - h
    },
    PrudentCooperator: {
      OptimisticCooperator: 0,
      PrudentCooperator: -h,
      OptimisticDefector: 0,
      PrudentDefector: -h
    },
    OptimisticDefector: {
      OptimisticCooperator: -c - f,
      PrudentCooperator: -h,
      OptimisticDefector: -f - b,
      PrudentDefector: -f - b - h
    },
    PrudentDefector: {
      OptimisticCooperator: -c - f,
      PrudentCooperator: -h,
      OptimisticDefector: -f - b,
      PrudentDefector: -f - b - h
    }
  }
};
