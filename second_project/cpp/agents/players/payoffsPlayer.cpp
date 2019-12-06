//
// Created by Pedro Rio on 21/11/2019.
//

#include "payoffsPlayer.h"

std::map<Umpire::Strategies, std::map<Player::Strategies, std::map<Player::Strategies, float>>>
playersPayoffMatrix(float b, float c, float f, float h, float A, float B) {
    return {
            {Umpire::Strategies::Honest,  {
                                                  {Player::Strategies::OptimisticCooperator,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, b - c - f},
                                                                  {Player::Strategies::PrudentCooperator,
                                                                                                          b - c - f -
                                                                                                          h},
                                                                  {Player::Strategies::OptimisticDefector, b - f - A},
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
                                                                  {Player::Strategies::OptimisticDefector, b - f - A},
                                                                  {Player::Strategies::PrudentDefector, -h},
                                                          }
                                                  },
                                                  {Player::Strategies::OptimisticDefector,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, -c - f},
                                                                  {Player::Strategies::PrudentCooperator, -c - f - h},
                                                                  {Player::Strategies::OptimisticDefector, -f - A},
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
                                                                  {Player::Strategies::OptimisticDefector, b - f - B},
                                                                  {Player::Strategies::PrudentDefector, b - f - B - h},
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
                                                                  {Player::Strategies::OptimisticDefector, -f - B},
                                                                  {Player::Strategies::PrudentDefector, -f - B - h},
                                                          }
                                                  },
                                                  {Player::Strategies::PrudentDefector,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, -c - f},
                                                                  {Player::Strategies::PrudentCooperator, -h},
                                                                  {Player::Strategies::OptimisticDefector, -f - B},
                                                                  {Player::Strategies::PrudentDefector, -f - B - h},
                                                          }
                                                  },
                                          }
            }
    };
}


std::map<Umpire::Strategies, std::map<Player::Strategies, std::map<Player::Strategies, float>>>
uncertainPlayersPayoffMatrix(float b, float c, float f, float h, float A, float B, float p) {
    return {
            {Umpire::Strategies::Honest,  {
                                                  {Player::Strategies::OptimisticCooperator,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, b - c - f},
                                                                  {Player::Strategies::PrudentCooperator,
                                                                                                          p *
                                                                                                          (b - c - f)},
                                                                  {Player::Strategies::OptimisticDefector, -c - f},
                                                                  {Player::Strategies::PrudentDefector,
                                                                                                        (1 - p) *
                                                                                                        (-c - f)},
                                                          }
                                                  },
                                                  {
                                                          Player::Strategies::PrudentCooperator,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator,
                                                                                                             p *
                                                                                                             (b - c -
                                                                                                              f - h) -
                                                                                                             (1 - p) *
                                                                                                             h},
                                                                  {Player::Strategies::PrudentCooperator,
                                                                                                          p *
                                                                                                          (b - c -
                                                                                                           f - h) -
                                                                                                          (1 - p) *
                                                                                                          h},
                                                                  {Player::Strategies::OptimisticDefector, p *
                                                                                                           (b - c -
                                                                                                            f - h) -
                                                                                                           (1 - p) *
                                                                                                           h},
                                                                  {Player::Strategies::PrudentDefector, -h},
                                                          }
                                                  },
                                                  {Player::Strategies::OptimisticDefector,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, b - f - A},
                                                                  {Player::Strategies::PrudentCooperator,
                                                                                                          p *
                                                                                                          (b - f - A)},
                                                                  {Player::Strategies::OptimisticDefector, -f - A},
                                                                  {Player::Strategies::PrudentDefector,
                                                                                                        (1 - p) *
                                                                                                        (-f - A)},
                                                          }
                                                  },
                                                  {Player::Strategies::PrudentDefector,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator,
                                                                                                             -p * h +
                                                                                                             (1 - p) *
                                                                                                             (b - f -
                                                                                                              A - h)},
                                                                  {Player::Strategies::PrudentCooperator, -h},
                                                                  {Player::Strategies::OptimisticDefector, -p * h +
                                                                                                           (1 - p) *
                                                                                                           (-f -
                                                                                                            A - h)},
                                                                  {Player::Strategies::PrudentDefector, -p * h +
                                                                                                        (1 - p) *
                                                                                                        (-f -
                                                                                                         A - h)},
                                                          }
                                                  },
                                          }
            },
            {Umpire::Strategies::Corrupt, {
                                                  {Player::Strategies::OptimisticCooperator,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, b - c - f},
                                                                  {Player::Strategies::PrudentCooperator, (1 - p) *
                                                                                                          (b - c - f)},
                                                                  {Player::Strategies::OptimisticDefector, -c - f},
                                                                  {Player::Strategies::PrudentDefector, p * (-c - f)},
                                                          }
                                                  },
                                                  {       Player::Strategies::PrudentCooperator,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, -p * h +
                                                                                                             (1 - p) *
                                                                                                             (b - c -
                                                                                                              f - h)},
                                                                  {Player::Strategies::PrudentCooperator, -p * h +
                                                                                                          (1 - p) *
                                                                                                          (b - c -
                                                                                                           f - h)},
                                                                  {Player::Strategies::OptimisticDefector, -p * h +
                                                                                                           (1 - p) *
                                                                                                           (-c - f -
                                                                                                            h)},
                                                                  {Player::Strategies::PrudentDefector, -h},
                                                          }
                                                  },
                                                  {Player::Strategies::OptimisticDefector,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, b - f - B},
                                                                  {Player::Strategies::PrudentCooperator, (1 - p) *
                                                                                                          (b - f - B)},
                                                                  {Player::Strategies::OptimisticDefector, -f - B},
                                                                  {Player::Strategies::PrudentDefector, p * (-f - B)},
                                                          }
                                                  },
                                                  {Player::Strategies::PrudentDefector,
                                                          {
                                                                  {Player::Strategies::OptimisticCooperator, p *
                                                                                                             (b - f -
                                                                                                              B - h) +
                                                                                                             (1 - p) *
                                                                                                             (-h)},
                                                                  {Player::Strategies::PrudentCooperator, -h},
                                                                  {Player::Strategies::OptimisticDefector, p *
                                                                                                           (-f -
                                                                                                            B - h) +
                                                                                                           (1 - p) *
                                                                                                           (-h)},
                                                                  {Player::Strategies::PrudentDefector, p *
                                                                                                        (-f -
                                                                                                         B - h) +
                                                                                                        (1 - p) *
                                                                                                        (-h)},
                                                          }
                                                  },
                                          }
            }
    };
}