# -*- coding: utf-8 -*-
"""
Created on Mon Nov 18 18:25:23 2019

@author: Regina Duarte
"""
import numpy as np

player_strategy_numbers = {
    (0, 1): 0,
    (0, 2): 1,
    (0, 3): 2,

    (1, 0): 3,
    (1, 2): 4,
    (1, 3): 5,

    (2, 0): 6,
    (2, 1): 7,
    (2, 3): 8,

    (3, 0): 9,
    (3, 1): 10,
    (3, 2): 11,
}

umpire_strategy_numbers = {
    (0, 'c'): 0,
    (1, 'c'): 1,
    (2, 'c'): 2,
    (3, 'c'): 3,

    (0, 'h'): 4,
    (1, 'h'): 5,
    (2, 'h'): 6,
    (3, 'h'): 7,
}


def fit(s1, s2, j, umpire, Qh, Qc, N):
    if umpire == 'c':
        return Qc[s1][s1] * (j - 1) + (N - j ) * Qc[s1][s2]
    else:
        return Qh[s1][s1] * (j - 1) + (N - j ) * Qh[s1][s2]


def fit_umpires(s, ump1, j, N, UMc, UMh):
    if ump1 == 'c':
        return (j - 1) * UMc[s] + (N - j + 1) * UMh[s]
    else:
        return (j - 1) * UMh[s] + (N - j + 1) * UMc[s]


def markovMatrix(N, f, b, B, A, h, c, beta):
    Qh = np.array([
        [b - c - f, b - c - f, -c - f, 0]
        [b - c - f - h, b - c - f - h, -c - f - h, -h]
        [b - f - A, b - f - A, -f - A, 0],
        [-h, -h, -h, -h]
    ])
    Qc = np.array([
        [b - c - f, 0, -c - f, -c - f],
        [-h, -h, -h, -h],
        [b - f - B, 0, -f - B, -f - B],
        [b - f - B - h, -h, -f - B - h, -f - B - h]
    ])

    UMc = np.array([2 * f, 0, 2 * (f + B), 2 * (f + B)])
    UMh = np.array([2 * f, 2 * f, 2 * f, 0])

    tc_plus = -np.ones((12, N - 1))
    tc_minus = -np.ones((12, N - 1))

    th_plus = -np.ones((12, N - 1))
    th_minus = -np.ones((12, N - 1))

    fit_c = -np.ones((12, N - 1))
    fit_h = -np.ones((12, N - 1))

    # fit = [fit_c, fit_h]

    t_plus_ump = -np.ones((8, N - 1))
    t_minus_ump = -np.ones((8, N - 1))

    fit_um = -np.ones((8, N - 1))

    umpire_strategies = ['h', 'c']
    player_strategies = ['OC', 'PC', 'OD', 'PD']

    player_strategy_values = {player_strategies[index]: index for index in range(0, len(player_strategies))}
    umpire_strategy_values = {umpire_strategies[index]: index for index in range(0, len(umpire_strategies))}

    for j in range(N):

        # [c, h]
        # [OC, PC, OD, PD]

        # OC => [PC, OD, PD]
        # d['OC'], d['PC']

        # COC, COD
        # np.array([[COC, COD], [])

        for umpire_strategy in umpire_strategies:
            for player_strategy in player_strategies:

                other_player_strategies = player_strategies.remove(player_strategy)

                for other_player_strategy in other_player_strategies:
                    fit_player_index = player_strategy_numbers[(player_strategy, other_player_strategy)]
                    fit_umpire_index = umpire_strategy_numbers[(player_strategy, umpire_strategy)]

                    fit_c[fit_player_index][j] = fit(
                        player_strategy_values[player_strategy],
                        player_strategy_values[other_player_strategy],
                        j + 1, umpire_strategy, Qh, Qc, N
                    )

                    fit_h[fit_player_index][j] = fit(
                        player_strategy_values[player_strategy],
                        player_strategy_values[other_player_strategy],
                        j + 1, umpire_strategy, Qh, Qc, N
                    )

                    fit_um[fit_umpire_index][j] = fit_umpires(player_strategy, umpire_strategy, j + 1, N, UMc, UMh)

    for j in range(N):
        tc_plus[0][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[0][j] - fit_c[3][N - j - 1])))
        tc_plus[1][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[1][j] - fit_c[6][N - j - 1])))
        tc_plus[2][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[2][j] - fit_c[9][N - j - 1])))
        tc_plus[3][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[3][j] - fit_c[0][N - j - 1])))
        tc_plus[4][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[4][j] - fit_c[7][N - j - 1])))
        tc_plus[5][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[5][j] - fit_c[10][N - j - 1])))
        tc_plus[6][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[6][j] - fit_c[1][N - j - 1])))
        tc_plus[7][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[7][j] - fit_c[4][N - j - 1])))
        tc_plus[8][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[8][j] - fit_c[11][N - j - 1])))
        tc_plus[9][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[9][j] - fit_c[2][N - j - 1])))
        tc_plus[10][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[10][j] - fit_c[5][N - j - 1])))
        tc_plus[11][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[11][j] - fit_c[8][N - j - 1])))
        tc_minus[0][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[0][j] - fit_c[3][N - j - 1])))
        tc_minus[1][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[1][j] - fit_c[6][N - j - 1])))
        tc_minus[2][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[2][j] - fit_c[9][N - j - 1])))
        tc_minus[3][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[3][j] - fit_c[0][N - j - 1])))
        tc_minus[4][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[4][j] - fit_c[7][N - j - 1])))
        tc_minus[5][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[5][j] - fit_c[10][N - j - 1])))
        tc_minus[6][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[6][j] - fit_c[1][N - j - 1])))
        tc_minus[7][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[7][j] - fit_c[4][N - j - 1])))
        tc_minus[8][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[8][j] - fit_c[11][N - j - 1])))
        tc_minus[9][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[9][j] - fit_c[2][N - j - 1])))
        tc_minus[10][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[10][j] - fit_c[5][N - j - 1])))
        tc_minus[11][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[11][j] - fit_c[8][N - j - 1])))

        th_plus[0][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[0][j] - fit_c[3][N - j - 1])))
        th_plus[1][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[1][j] - fit_c[6][N - j - 1])))
        th_plus[2][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[2][j] - fit_c[9][N - j - 1])))
        th_plus[3][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[3][j] - fit_c[0][N - j - 1])))
        th_plus[4][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[4][j] - fit_c[7][N - j - 1])))
        th_plus[5][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[5][j] - fit_c[10][N - j - 1])))
        th_plus[6][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[6][j] - fit_c[1][N - j - 1])))
        th_plus[7][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[7][j] - fit_c[4][N - j - 1])))
        th_plus[8][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[8][j] - fit_c[11][N - j - 1])))
        th_plus[9][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[9][j] - fit_c[2][N - j - 1])))
        th_plus[10][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[10][j] - fit_c[5][N - j - 1])))
        th_plus[11][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_c[11][j] - fit_c[8][N - j - 1])))
        th_minus[0][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(beta * (fit_c[0][j] - fit_c[3][N - j - 1])))
        th_minus[1][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(beta * (fit_c[1][j] - fit_c[6][N - j - 1])))
        th_minus[2][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(beta * (fit_c[2][j] - fit_c[9][N - j - 1])))
        th_minus[3][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(beta * (fit_c[3][j] - fit_c[0][N - j - 1])))
        th_minus[4][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(beta * (fit_c[4][j] - fit_c[7][N - j - 1])))
        th_minus[5][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(beta * (fit_c[5][j] - fit_c[10][N - j - 1])))
        th_minus[6][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(beta * (fit_c[6][j] - fit_c[1][N - j - 1])))
        th_minus[7][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(beta * (fit_c[7][j] - fit_c[4][N - j - 1])))
        th_minus[8][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(beta * (fit_c[8][j] - fit_c[11][N - j - 1])))
        th_minus[9][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(beta * (fit_c[9][j] - fit_c[2][N - j - 1])))
        th_minus[10][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(beta * (fit_c[10][j] - fit_c[5][N - j - 1])))
        th_minus[11][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(beta * (fit_c[11][j] - fit_c[8][N - j - 1])))

        t_plus_ump[0][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_um[0][j] - fit_c[4][N - j - 1])))
        t_plus_ump[1][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_um[1][j] - fit_c[5][N - j - 1])))
        t_plus_ump[2][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_um[2][j] - fit_c[6][N - j - 1])))
        t_plus_ump[3][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_um[3][j] - fit_c[7][N - j - 1])))
        t_plus_ump[4][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_um[4][j] - fit_c[0][N - j - 1])))
        t_plus_ump[5][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_um[5][j] - fit_c[1][N - j - 1])))
        t_plus_ump[6][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_um[6][j] - fit_c[2][N - j - 1])))
        t_plus_ump[7][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(-beta * (fit_um[7][j] - fit_c[3][N - j - 1])))
        t_minus_ump[0][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(beta * (fit_um[0][j] - fit_c[4][N - j - 1])))
        t_minus_ump[1][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(beta * (fit_um[1][j] - fit_c[5][N - j - 1])))
        t_minus_ump[2][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(beta * (fit_um[2][j] - fit_c[6][N - j - 1])))
        t_minus_ump[3][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(beta * (fit_um[3][j] - fit_c[7][N - j - 1])))
        t_minus_ump[4][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(beta * (fit_um[4][j] - fit_c[0][N - j - 1])))
        t_minus_ump[5][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(beta * (fit_um[5][j] - fit_c[1][N - j - 1])))
        t_minus_ump[6][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(beta * (fit_um[6][j] - fit_c[2][N - j - 1])))
        t_minus_ump[7][j] = ((j + 1) / N) * (N - (j + 1) / (N - 1)) * 1 / (
            np.exp(beta * (fit_um[7][j] - fit_c[3][N - j - 1])))

    matrix = np.zeros((8, 8))
    def prob_fix_c(s1, s2, N):
        prob=0
        for i in range(1, N - 1):
        
            for j in range(1, i):
                produto = np.prod((tc_minus[player_strategy_numbers[s1,s2]][0:j])/(tc_plus[player_strategy_numbers[s1,s2]][0:j]))
            
            prob+=produto
        return prob
        
    def prob_fix_h(s1, s2, N):
        prob=0
        for i in range(1, N - 1):
            for j in range(1, i):
                produto = np.prod((th_minus[player_strategy_numbers[s1,s2]][0:j])/(th_plus[player_strategy_numbers[s1,s2]][0:j]))
            prob+=produto
        return prob
    
    def prob_fix_UM(s1, um, N):
        prob=0
        for i in range(1, N - 1):
            for j in range(1, i):
                produto = np.prod((t_minus_ump[umpire_strategy_numbers[s1,um]][0:j])/(t_plus_ump[umpire_strategy_numbers[s1,um]][0:j]))
            prob+=produto
        return prob

    for a in range(8):
        for b in range(8):
            if 0 <= a < 4 and 0 < b < 4 and a!=b:
                matrix[a][b]=prob_fix_h(a,b,N)
            if 4<= a <=7 and 4<= b <= 7 and a!=b:
                matrix[a][b]=prob_fix_c(a-4,b-4,N)
            elif ((0 <= a < 4 and 4<= b <= 7) or (4<= a <=7 and 0 < b < 4)) and (a==b+4 or a+4==b):
                if a<4:
                    um='h'
                    matrix[a][b]=prob_fix_UM(a,'h',N)
                else:
                    matrix[a][b]=prob_fix_UM(a-4,'c',N)
        
                    





