//
// Created by Pedro Rio on 21/11/2019.
//

#include "payoffsUmpire.h"

std::map<Umpire::Strategies,
        std::map<Player::Strategies,
                std::map<Player::Strategies, float>
        >
> umpiresPayoffMatrix(float b, float c, float f, float h, float A, float B) {
    return {
            {Umpire::Strategies::Honest,  {
                                                  {Player::Strategies::OptimisticCooperator,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, 2 * f},
                                                                  {Player::Strategies::PrudentCooperator, 2 * f},
                                                                  {Player::Strategies::OptimisticDefector, 2 * f},
                                                                  {Player::Strategies::PrudentDefector, 0.0},
                                                          }
                                                  },
                                                  {
                                                          Player::Strategies::PrudentCooperator,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, 2 * f},
                                                                  {Player::Strategies::PrudentCooperator, 2 * f},
                                                                  {Player::Strategies::OptimisticDefector, 2 * f},
                                                                  {Player::Strategies::PrudentDefector, 0.0},
                                                          }
                                                  },
                                                  {Player::Strategies::OptimisticDefector,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, 2 * f},
                                                                  {Player::Strategies::PrudentCooperator, 2 * f},
                                                                  {Player::Strategies::OptimisticDefector, 2 * f},
                                                                  {Player::Strategies::PrudentDefector, 0.0},
                                                          }
                                                  },
                                                  {Player::Strategies::PrudentDefector,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, 0.0},
                                                                  {Player::Strategies::PrudentCooperator, 0.0},
                                                                  {Player::Strategies::OptimisticDefector, 0.0},
                                                                  {Player::Strategies::PrudentDefector, 0.0},
                                                          }
                                                  },
                                          }
            },
            {Umpire::Strategies::Corrupt, {
                                                  {Player::Strategies::OptimisticCooperator,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, 2 * f},
                                                                  {Player::Strategies::PrudentCooperator, 0.0},
                                                                  {Player::Strategies::OptimisticDefector, 2 * f + B},
                                                                  {Player::Strategies::PrudentDefector, 2 * f + B},
                                                          }
                                                  },
                                                  {
                                                          Player::Strategies::PrudentCooperator,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, 0.0},
                                                                  {Player::Strategies::PrudentCooperator, 0.0},
                                                                  {Player::Strategies::OptimisticDefector, 0.0},
                                                                  {Player::Strategies::PrudentDefector, 0.0},
                                                          }
                                                  },
                                                  {Player::Strategies::OptimisticDefector,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, 2 * f + B},
                                                                  {Player::Strategies::PrudentCooperator, 0.0},
                                                                  {Player::Strategies::OptimisticDefector, 2 * f +
                                                                                                           2 * B},
                                                                  {Player::Strategies::PrudentDefector, 2 * f + 2 * B},
                                                          }
                                                  },
                                                  {Player::Strategies::PrudentDefector,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, 2 * f + B},
                                                                  {Player::Strategies::PrudentCooperator, 0.0},
                                                                  {Player::Strategies::OptimisticDefector, 2 * f +
                                                                                                           2 * B},
                                                                  {Player::Strategies::PrudentDefector, 2 * f + 2 * B},
                                                          }
                                                  },
                                          }
            }
    };
}

std::map<Umpire::Strategies,
        std::map<Player::Strategies,
                std::map<Player::Strategies, float>
        >
> uncertainUmpiresPayoffMatrix(float b, float c, float f, float h, float A, float B, float p) {
    return {
            {Umpire::Strategies::Honest,  {
                                                  {Player::Strategies::OptimisticCooperator,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, 2 * f},
                                                                  {Player::Strategies::PrudentCooperator, 2 * f},
                                                                  {Player::Strategies::OptimisticDefector, 2 * f},
                                                                  {Player::Strategies::PrudentDefector,
                                                                                                        2 * (1 - p) *
                                                                                                        f},
                                                          }
                                                  },
                                                  {
                                                          Player::Strategies::PrudentCooperator,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, 2 * p * f},
                                                                  {Player::Strategies::PrudentCooperator, 2 * p * f},
                                                                  {Player::Strategies::OptimisticDefector, 2 * p * f},
                                                                  {Player::Strategies::PrudentDefector, 0.0},
                                                          }
                                                  },
                                                  {Player::Strategies::OptimisticDefector,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, 2 * p * f},
                                                                  {Player::Strategies::PrudentCooperator, 2 * p * f},
                                                                  {Player::Strategies::OptimisticDefector, 2 * f},
                                                                  {Player::Strategies::PrudentDefector, 2 * (1 - p) *
                                                                                                        f},
                                                          }
                                                  },
                                                  {Player::Strategies::PrudentDefector,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator,
                                                                                                             2 *
                                                                                                             (1 - p) *
                                                                                                             f},
                                                                  {Player::Strategies::PrudentCooperator, 0.0},
                                                                  {Player::Strategies::OptimisticDefector, 2 * (1 - p) *
                                                                                                           f},
                                                                  {Player::Strategies::PrudentDefector, 2 * (1 - p) *
                                                                                                        f},
                                                          }
                                                  },
                                          }
            },
            {Umpire::Strategies::Corrupt, {
                                                  {Player::Strategies::OptimisticCooperator,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, 2 * f},
                                                                  {Player::Strategies::PrudentCooperator, 2 * (1 - p) *
                                                                                                          f},
                                                                  {Player::Strategies::OptimisticDefector, 2 * f + B},
                                                                  {Player::Strategies::PrudentDefector, 2 * p * f +
                                                                                                        p * B},
                                                          }
                                                  },
                                                  {
                                                          Player::Strategies::PrudentCooperator,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, 2 *
                                                                                                             (1 - p) *
                                                                                                             f},
                                                                  {Player::Strategies::PrudentCooperator, 2 * (1 - p) *
                                                                                                          f},
                                                                  {Player::Strategies::OptimisticDefector, 2 * (1 - p) *
                                                                                                           f + (1 - p) *
                                                                                                               B},
                                                                  {Player::Strategies::PrudentDefector, 0.0},
                                                          }
                                                  },
                                                  {Player::Strategies::OptimisticDefector,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, 2 * f + B},
                                                                  {Player::Strategies::PrudentCooperator, 2 * (1 - p) *
                                                                                                          f + (1 - p) *
                                                                                                              B},
                                                                  {Player::Strategies::OptimisticDefector, 2 * (f + B)},
                                                                  {Player::Strategies::PrudentDefector, 2 * p *
                                                                                                        (f + B)},
                                                          }
                                                  },
                                                  {Player::Strategies::PrudentDefector,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, 2 * p * f +
                                                                                                             p * B},
                                                                  {Player::Strategies::PrudentCooperator, 0.0},
                                                                  {Player::Strategies::OptimisticDefector, 2 * p *
                                                                                                           (f + B)},
                                                                  {Player::Strategies::PrudentDefector, 2 * p *
                                                                                                        (f + B)},
                                                          }
                                                  },
                                          }
            }
    };
}

std::map<Umpire::Strategies,
        std::map<Player::Strategies,
                std::map<Player::Strategies, float>
        >
> punishmentUmpiresPayoffMatrix(float b, float c, float f, float h, float A, float B, float T) {
    return {
            {Umpire::Strategies::Honest,  {
                                                  {Player::Strategies::OptimisticCooperator,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, 2 * f},
                                                                  {Player::Strategies::PrudentCooperator, 2 * f},
                                                                  {Player::Strategies::OptimisticDefector, 2 * f},
                                                                  {Player::Strategies::PrudentDefector, 0.0},
                                                          }
                                                  },
                                                  {
                                                          Player::Strategies::PrudentCooperator,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, 2 * f},
                                                                  {Player::Strategies::PrudentCooperator, 2 * f},
                                                                  {Player::Strategies::OptimisticDefector, 2 * f},
                                                                  {Player::Strategies::PrudentDefector, 0.0},
                                                          }
                                                  },
                                                  {Player::Strategies::OptimisticDefector,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, 2 * f},
                                                                  {Player::Strategies::PrudentCooperator, 2 * f},
                                                                  {Player::Strategies::OptimisticDefector, 2 * f},
                                                                  {Player::Strategies::PrudentDefector, 0.0},
                                                          }
                                                  },
                                                  {Player::Strategies::PrudentDefector,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, 0.0},
                                                                  {Player::Strategies::PrudentCooperator, 0.0},
                                                                  {Player::Strategies::OptimisticDefector, 0.0},
                                                                  {Player::Strategies::PrudentDefector, 0.0},
                                                          }
                                                  },
                                          }
            },
            {Umpire::Strategies::Corrupt, {
                                                  {Player::Strategies::OptimisticCooperator,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, 2 * f},
                                                                  {Player::Strategies::PrudentCooperator, -T},
                                                                  {Player::Strategies::OptimisticDefector, 2 * f + B -
                                                                                                           T},
                                                                  {Player::Strategies::PrudentDefector, 2 * f + B -
                                                                                                        T},
                                                          }
                                                  },
                                                  {
                                                          Player::Strategies::PrudentCooperator,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, -T},
                                                                  {Player::Strategies::PrudentCooperator, -T},
                                                                  {Player::Strategies::OptimisticDefector, -T},
                                                                  {Player::Strategies::PrudentDefector, -T},
                                                          }
                                                  },
                                                  {Player::Strategies::OptimisticDefector,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, 2 * f + B -
                                                                                                             T},
                                                                  {Player::Strategies::PrudentCooperator, -T},
                                                                  {Player::Strategies::OptimisticDefector, 2 * f + B -
                                                                                                           T},
                                                                  {Player::Strategies::PrudentDefector, 2 * f + B -
                                                                                                        T},
                                                          }
                                                  },
                                                  {Player::Strategies::PrudentDefector,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, 2 * f + B -
                                                                                                             T},
                                                                  {Player::Strategies::PrudentCooperator, -T},
                                                                  {Player::Strategies::OptimisticDefector, 2 * f + B -
                                                                                                           T},
                                                                  {Player::Strategies::PrudentDefector, 2 * f + B -
                                                                                                        T},
                                                          }
                                                  },
                                          }
            }
    };
}