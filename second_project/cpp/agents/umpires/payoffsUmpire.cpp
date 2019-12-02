//
// Created by Pedro Rio on 21/11/2019.
//

#include "payoffsUmpire.h"

std::map<Umpire::Strategies,
        std::map<Player::Strategies,
                std::map<Player::Strategies, float>
        >
> umpiresPayoffMatrix(float b, float c, float f, float h, float a, float B) {
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
