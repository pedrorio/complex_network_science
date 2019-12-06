# -*- coding: utf-8 -*-
"""
Created on Mon Nov 25 17:14:29 2019

@author: Regina Duarte
"""
import numpy as np


class Game(object):
    def __init__(self, N, beta, f, b, c, h, B, A, p, T):
        self.N = N
        self.Qc = np.array([
            [b - c - f, (1 - p) * (b - c - f), -c - f, p * (-c - f)],
            [-p * h + (1 - p) * (b - c - f - h), -p * h + (1 - p) * (b - c - f - h), -p * h + (1 - p) * (-c - f - h),
             -h],
            [b - f - B, (1 - p) * (b - f - B), -f - B, p * (-f - B)],
            [p * (b - f - B - h) + (1 - p) * (-h), -h, p * (-f - B - h) + (1 - p) * (-h),
             p * (-f - B - h) + (1 - p) * (-h)]
        ])
        self.Qh = np.array([
            [b - c - f, (b - c - f) * p, -c - f, (1 - p) * (-c - f)],
            [p * (b - c - f - h) - (1 - p) * h, p * (b - c - f - h) - (1 - p) * h, p * (-c - f - h) - (1 - p) * h, -h],
            [b - f - A, p * (b - f - A), -f - A, (1 - p) * (-f - A)],
            [-p * h + (1 - p) * (b - f - A - h), -h, -p * h + (1 - p) * (-f - A - h), -p * h + (1 - p) * (-f - A - h)]
        ])
        self.beta = beta
        self.Hc = np.array([2 * f, 2 * (1 - p) * f - T, 2 * (f + B) - T, 2 * (f + B) * p - T])
        self.Hh = np.array([2 * f, 2 * f * p, 2 * f, 2 * (1 - p) * f])


GameC = Game(40, 2, 0.2, 1, 0.5, 0.1, 0.2, 2, 1, 0.3)


def fit(s1, s2, j, Game, s, umpire):
    """s1 e s2 sao dois estados de players, onde s1 é a mutação
    j é o numero de players s1,
    s pode ser 0 ou 1 consoante queremos fazer o fit do estado
    mutação ou o estado residente"""

    N = Game.N
    if s == 0:
        if umpire == 'c':
            return Game.Qc[s1][s1] * (j - 1) + (N - j) * Game.Qc[s1][s2]
        else:
            return Game.Qh[s1][s1] * (j - 1) + (N - j) * Game.Qh[s1][s2]
    else:
        if umpire == 'c':
            return Game.Qc[s2][s1] * (j - 1) + (N - j) * Game.Qc[s2][s2]
        else:
            return Game.Qh[s2][s1] * (j - 1) + (N - j) * Game.Qh[s2][s2]


def fit_umpires(s1, ump1, j, Game, s):
    """s1 é a estrategia  dos players (0-4)
    ump1 a estratéria dos umpires mutante
    j numero de umpires mutantes
    s pode ser 0 ou 1 consoante queremos fazer o fit do estado
    mutação ou o estado residente"""

    N = Game.N
    if s == 0 and ump1 == 'c':
        return (j - 1) * Game.Hc[s1] + (N - j) * Game.Hh[s1]

    elif s == 0 and ump1 == 'h':
        return (j - 1) * Game.Hh[s1] + (N - j) * Game.Hc[s1]

    elif s == 1 and ump1 == 'c':
        return j * Game.Hc[s1] + (N - j - 1) * Game.Hh[s1]

    else:
        return j * Game.Hh[s1] + (N - j - 1) * Game.Hc[s1]


def T(sinal, ump, s1, s2, j, Game):
    """sinal -> 'mais' ou 'menos'
    ump -> 'c' ou 'h' é a estratégia unica se s1!=s2 ou a estratégia mutante se s1=s2
    s1 -> estrategia mutante
    s2 -> estrategia residente
    j-> numero de mutantes"""
    N = Game.N
    if s1 == s2:
        if sinal == 'mais':
            t = (j / N) * ((N - j) / (N - 1)) * 1 / (
                    1 + np.exp(-Game.beta * (fit_umpires(s1, ump, j, Game, 0) - fit_umpires(s1, ump, j, Game, 1))))
        else:
            t = (j / N) * ((N - j) / (N - 1)) * 1 / (
                    1 + np.exp(-Game.beta * (fit_umpires(s1, ump, j, Game, 0) + fit_umpires(s1, ump, j, Game, 1))))
    else:
        if sinal == 'mais':
            t = (j / N) * ((N - j) / (N - 1)) * 1 / (
                    1 + np.exp(-Game.beta * (fit(s1, s2, j, Game, 0, ump) - fit(s1, s2, j, Game, 1, ump))))
        else:
            t = (j / N) * ((N - j) / (N - 1)) * 1 / (
                    1 + np.exp(-Game.beta * (fit(s1, s2, j, Game, 0, ump) + fit(s1, s2, j, Game, 1, ump))))
    return t


def prob_fix(S1, S2, ump1, Game):
    prob = 0
    memoria = np.ones(Game.N - 1)
    for i in range(1, Game.N):
        # print('T PARA ESCLARECER:', 'MAIS:',T('mais',ump1,S1,S2,i,Game),'MENOS:',T('menos',ump1,S1,S2,i,Game))
        memoria[i - 1] = (T('menos', ump1, S1, S2, i, Game) / T('mais', ump1, S1, S2, i, Game))
        prob += np.prod(memoria)
    # print(memoria)
    return (prob + 1) ** -1


#    soma=0
#    prod=1
#    for k in range(1,Game.N):
#        a=T('menos',ump1,S1,S2,k,Game)/T('mais',ump1, S1, S2, k, Game)
#        prod=prod*a
#        soma=soma+prod
#    return 1/(1+soma)


def estacionaria(Game):
    matrix = np.zeros((8, 8))
    ###CONSTRUÇÃO DA MATRIZ DE TRANSIÇÃO
    for a in range(8):
        for b in range(8):
            if 0 <= a < 4 and 0 <= b < 4 and a != b:
                matrix[a][b] = prob_fix(a, b, 'h', GameC) / 7
            if 4 <= a <= 7 and 4 <= b <= 7 and a != b:
                matrix[a][b] = prob_fix(a - 4, b - 4, 'c', GameC) / 7
            elif ((0 <= a < 4 and 4 <= b <= 7) or (4 <= a <= 7 and 0 <= b < 4)) and (a == b + 4 or a + 4 == b):
                if a < 4:
                    matrix[a][b] = prob_fix(a, b - 4, 'h', GameC) / 7
                else:
                    matrix[a][b] = prob_fix(a - 4, b, 'c', GameC) / 7

    for i in range(8):
        matrix[i][i] = 1 - np.sum(matrix[i])

    eigan_vector = np.linalg.eig(np.transpose(matrix))

    for i in range(len(eigan_vector[0])):

        if np.round(eigan_vector[0][i], 10) == 1.0:
            print(i, 'vamos ver')
            distribuicao_estacionaria = eigan_vector[1][:, i]

    vetor = distribuicao_estacionaria / sum(distribuicao_estacionaria)

    return (matrix, vetor)


a = estacionaria(GameC)

# b=np.array([[0.7,0,0.3,0],[0.5,0,0.5,0],[0,0.4,0,0.6],[0,0.2,0,0.8]])
# c=np.linalg.eig(np.transpose(b))
#
# f=-c[1][:,0]
# print(f)
# print(f/sum(f))

# eigan_vector=np.linalg.eig(np.transpose(a))
