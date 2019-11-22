//
// Created by Pedro Rio on 21/11/2019.
//

#include "playerPayoffs.h"

std::map<Umpire::Strategies, std::map<Player::Strategies, std::map<Player::Strategies, float>>>
playersPayoffMatrix(float b, float c, float f, float h, float a) {
    return {
            {Umpire::Strategies::Honest,  {
                                                  {Player::Strategies::OptimisticCooperator,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, b - c - f},
                                                                  {Player::Strategies::PrudentCooperator,
                                                                                                          b - c - f -
                                                                                                          h},
                                                                  {Player::Strategies::OptimisticDefector, b - f - a},
                                                                  {Player::Strategies::PrudentDefector, -h},
                                                          }
                                                  },
                                                  {
                                                          Player::Strategies::PrudentCooperator,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, b - c - f},
                                                                  {Player::Strategies::PrudentCooperator,
                                                                                                          b - c - f -
                                                                                                          h},
                                                                  {Player::Strategies::OptimisticDefector, b - f - a},
                                                                  {Player::Strategies::PrudentDefector, -h},
                                                          }
                                                  },
                                                  {Player::Strategies::OptimisticDefector,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, -c - f},
                                                                  {Player::Strategies::PrudentCooperator, -c - f - h},
                                                                  {Player::Strategies::OptimisticDefector, -f - a},
                                                                  {Player::Strategies::PrudentDefector, -h},
                                                          }
                                                  },
                                                  {Player::Strategies::PrudentDefector,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, 0.0},
                                                                  {Player::Strategies::PrudentCooperator, -h},
                                                                  {Player::Strategies::OptimisticDefector, 0.0},
                                                                  {Player::Strategies::PrudentDefector, -h},
                                                          }
                                                  },
                                          }
            },
            {Umpire::Strategies::Corrupt, {
                                                  {Player::Strategies::OptimisticCooperator,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, b - c - f},
                                                                  {Player::Strategies::PrudentCooperator, -h},
                                                                  {Player::Strategies::OptimisticDefector, b - f - b},
                                                                  {Player::Strategies::PrudentDefector, b - f - b - h},
                                                          }
                                                  },
                                                  {
                                                          Player::Strategies::PrudentCooperator,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, 0.0},
                                                                  {Player::Strategies::PrudentCooperator, -h},
                                                                  {Player::Strategies::OptimisticDefector, 0.0},
                                                                  {Player::Strategies::PrudentDefector, -h},
                                                          }
                                                  },
                                                  {Player::Strategies::OptimisticDefector,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, -c - f},
                                                                  {Player::Strategies::PrudentCooperator, -h},
                                                                  {Player::Strategies::OptimisticDefector, -f - b},
                                                                  {Player::Strategies::PrudentDefector, -f - b - h},
                                                          }
                                                  },
                                                  {Player::Strategies::PrudentDefector,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, -c - f},
                                                                  {Player::Strategies::PrudentCooperator, -h},
                                                                  {Player::Strategies::OptimisticDefector, -f - b},
                                                                  {Player::Strategies::PrudentDefector, -f - b - h},
                                                          }
                                                  },
                                          }
            }
    };
}