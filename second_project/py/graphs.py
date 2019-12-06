#!/usr/bin/env python3
import sys

import seaborn as sns
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.ticker import EngFormatter

print(sys.argv)
path = sys.argv[1]
print(path)
# path = f'../{directory}'

data = pd.read_csv(f'{path}/data.csv')
param = pd.read_csv(f'{path}/params.csv')

print(data.describe())

formatter = EngFormatter(places=0, sep="\N{THIN SPACE}")

a = param['a'][0]
b = param['b'][0]
c = param['c'][0]
f = param['f'][0]
h = param['h'][0]
B = param['B'][0]
playerExplorationProbability = param['playerExplorationProbability'][0]
umpireExplorationProbability = param['umpireExplorationProbability'][0]
imitationStrength = param['imitationStrength'][0]

pal = sns.color_palette("Set1")
linewidth = 0.65

data['Cooperator'] = data["OptimisticCooperator"] + data["PrudentCooperator"]
data['Defector'] = data["OptimisticDefector"] + data["PrudentDefector"]

aggregate_labels = ["Cooperator", "Defector"]
player_labels = ["OptimisticCooperator", "OptimisticDefector", "PrudentCooperator", "PrudentDefector"]
umpire_labels = ["Honest", "Corrupt"]

comparison_labels = player_labels + umpire_labels

plt.stackplot(data["Generation"], data[umpire_labels].T, labels=umpire_labels, colors=pal, alpha=0.4)
plt.plot(data["Generation"], data[player_labels], linewidth=linewidth)
ax = plt.gca()
values = ax.get_yticks()
ax.set_yticklabels(['{:,.0%}'.format(x) for x in values])
ax.set_ylim([0, 1])
ax.set_xlim([0, data["Generation"].max()])
plt.xlabel(fr'$n_{{gerações}}$')
plt.ylabel(r'$Frequências$')
plt.ticklabel_format(axis='x', style='sci')
ax.xaxis.set_major_formatter(formatter)
plt.legend(comparison_labels, loc='best', frameon=False)
plt.tight_layout()
plt.savefig(f'{path}/Comparison.png')
plt.clf()

comparison_labels = aggregate_labels + umpire_labels
plt.stackplot(data["Generation"], data[umpire_labels].T, labels=umpire_labels, colors=pal, alpha=0.4)
plt.plot(data["Generation"], data[aggregate_labels], linewidth=linewidth)
ax = plt.gca()
values = ax.get_yticks()
ax.set_yticklabels(['{:,.0%}'.format(x) for x in values])
ax.set_ylim([0, 1])
ax.set_xlim([0, data["Generation"].max()])
plt.xlabel(fr'$n_{{gerações}}$')
plt.ylabel(r'$Frequências$')
plt.ticklabel_format(axis='x', style='sci')
ax.xaxis.set_major_formatter(formatter)
plt.legend(comparison_labels, loc='best', frameon=False)
plt.tight_layout()
plt.savefig(f'{path}/AggregateComparison.png')
plt.clf()
