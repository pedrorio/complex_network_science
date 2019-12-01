import os
import seaborn as sns
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.ticker import EngFormatter

directories = sorted(os.listdir('../simulations'))
directory = directories[-1]

data = pd.read_csv(f'../simulations/{directory}/data.csv')
param = pd.read_csv(f'../simulations/{directory}/params.csv')

print(data.min())
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

# plt.stackplot(data["Generation"], data[player_labels].T, labels=player_labels, colors=pal, alpha=0.4)
# ax = plt.gca()
# values = ax.get_yticks()
# ax.set_yticklabels(['{:,.0%}'.format(x) for x in values])
# ax.set_ylim([0, 1])
# ax.set_xlim([0, data["Generation"].max()])
# plt.xlabel(fr'$n_{{gerações}}$')
# plt.ylabel(r'$Frequências$')
# plt.text(0.01, 0.03, fr'$a={a}$',
#          horizontalalignment='left',
#          verticalalignment='baseline',
#          transform=ax.transAxes)
# plt.text(0.01, 0.08, fr'$b={b}$',
#          horizontalalignment='left',
#          verticalalignment='baseline',
#          transform=ax.transAxes)
# plt.text(0.01, 0.13, fr'$c={c}$',
#          horizontalalignment='left',
#          verticalalignment='baseline',
#          transform=ax.transAxes)
# plt.text(0.01, 0.18, fr'$f={f}$',
#          horizontalalignment='left',
#          verticalalignment='baseline',
#          transform=ax.transAxes)
# plt.text(0.01, 0.23, fr'$h={h}$',
#          horizontalalignment='left',
#          verticalalignment='baseline',
#          transform=ax.transAxes)
# plt.text(0.01, 0.28, fr'$B={B}$',
#          horizontalalignment='left',
#          verticalalignment='baseline',
#          transform=ax.transAxes)
# plt.text(0.01, 0.33, fr'$playerExplorationProbability={playerExplorationProbability}$',
#          horizontalalignment='left',
#          verticalalignment='baseline',
#          transform=ax.transAxes)
# plt.text(0.01, 0.38, fr'$UmpireExplorationProbability={umpireExplorationProbability}$',
#          horizontalalignment='left',
#          verticalalignment='baseline',
#          transform=ax.transAxes)
# plt.text(0.01, 0.43, fr'$ImitationStrength={imitationStrength:.1E}$',
#          horizontalalignment='left',
#          verticalalignment='baseline',
#          transform=ax.transAxes)
# plt.ticklabel_format(axis='x', style='sci')
# ax.xaxis.set_major_formatter(formatter)
# plt.legend(loc='best', frameon=False)
# plt.tight_layout()
# plt.savefig(f"../simulations/{directory}/Players.png")
# plt.clf()
#
# plt.plot(data["Generation"], data[player_labels], linewidth=linewidth)
# ax = plt.gca()
# values = ax.get_yticks()
# ax.set_yticklabels(['{:,.0%}'.format(x) for x in values])
# ax.set_ylim([0, 1])
# ax.set_xlim([0, data["Generation"].max()])
# plt.xlabel(fr'$n_{{gerações}}$')
# plt.ylabel(r'$Frequências$')
# plt.ticklabel_format(axis='x', style='sci')
# ax.xaxis.set_major_formatter(formatter)
# plt.legend(player_labels, loc='best', frameon=False)
# plt.tight_layout()
# plt.savefig(f'../simulations/{directory}/PlayerLines.png')
# plt.clf()

# plt.stackplot(data["Generation"], data[aggregate_labels].T, labels=aggregate_labels, colors=pal, alpha=0.4)
# ax = plt.gca()
# values = ax.get_yticks()
# ax.set_yticklabels(['{:,.0%}'.format(x) for x in values])
# ax.set_ylim([0, 1])
# ax.set_xlim([0, data["Generation"].max()])
# plt.xlabel(fr'$n_{{gerações}}$')
# plt.ylabel(r'$Frequências$')
# plt.ticklabel_format(axis='x', style='sci')
# ax.xaxis.set_major_formatter(formatter)
# plt.legend(aggregate_labels, loc='best', frameon=False)
# plt.tight_layout()
# plt.savefig(f'../simulations/{directory}/Aggregate.png')
# plt.clf()

# plt.plot(data["Generation"], data[aggregate_labels], linewidth=linewidth)
# ax = plt.gca()
# values = ax.get_yticks()
# ax.set_yticklabels(['{:,.0%}'.format(x) for x in values])
# ax.set_ylim([0, 1])
# ax.set_xlim([0, data["Generation"].max()])
# plt.xlabel(fr'$n_{{gerações}}$')
# plt.ylabel(r'$Frequências$')
# plt.ticklabel_format(axis='x', style='sci')
# ax.xaxis.set_major_formatter(formatter)
# plt.legend(aggregate_labels, loc='best', frameon=False)
# plt.tight_layout()
# plt.savefig(f'../simulations/{directory}/AggregateLines.png')
# plt.clf()

umpire_labels = ["Honest", "Corrupt"]

# plt.stackplot(data["Generation"], data[umpire_labels].T, labels=umpire_labels, colors=pal, alpha=0.4)
# ax = plt.gca()
# values = ax.get_yticks()
# ax.set_yticklabels(['{:,.0%}'.format(x) for x in values])
# ax.set_ylim([0, 1])
# ax.set_xlim([0, data["Generation"].max()])
# plt.xlabel(fr'$n_{{gerações}}$')
# plt.ylabel(r'$Frequências$')
#
# plt.text(0.01, 0.03, fr'$a={a}$',
#          horizontalalignment='left',
#          verticalalignment='baseline',
#          transform=ax.transAxes)
#
# plt.text(0.01, 0.08, fr'$b={b}$',
#          horizontalalignment='left',
#          verticalalignment='baseline',
#          transform=ax.transAxes)
#
# plt.text(0.01, 0.13, fr'$c={c}$',
#          horizontalalignment='left',
#          verticalalignment='baseline',
#          transform=ax.transAxes)
#
# plt.text(0.01, 0.18, fr'$f={f}$',
#          horizontalalignment='left',
#          verticalalignment='baseline',
#          transform=ax.transAxes)
#
# plt.text(0.01, 0.23, fr'$h={h}$',
#          horizontalalignment='left',
#          verticalalignment='baseline',
#          transform=ax.transAxes)
#
# plt.text(0.01, 0.28, fr'$B={B}$',
#          horizontalalignment='left',
#          verticalalignment='baseline',
#          transform=ax.transAxes)
#
# plt.text(0.01, 0.33, fr'$playerExplorationProbability={playerExplorationProbability}$',
#          horizontalalignment='left',
#          verticalalignment='baseline',
#          transform=ax.transAxes)
#
# plt.text(0.01, 0.38, fr'$UmpireExplorationProbability={umpireExplorationProbability}$',
#          horizontalalignment='left',
#          verticalalignment='baseline',
#          transform=ax.transAxes)
#
# plt.text(0.01, 0.43, fr'$ImitationStrength={imitationStrength:.1E}$',
#          horizontalalignment='left',
#          verticalalignment='baseline',
#          transform=ax.transAxes)
#
# plt.ticklabel_format(axis='x', style='sci')
# ax.xaxis.set_major_formatter(formatter)
# plt.legend(umpire_labels, loc='best', frameon=False)
# plt.tight_layout()
# plt.savefig(f'../simulations/{directory}/Umpires.png')
# plt.clf()
#
# plt.plot(data["Generation"], data[umpire_labels], linewidth=linewidth)
# ax = plt.gca()
# values = ax.get_yticks()
# ax.set_yticklabels(['{:,.0%}'.format(x) for x in values])
# ax.set_ylim([0, 1])
# ax.set_xlim([0, data["Generation"].max()])
# plt.xlabel(fr'$n_{{gerações}}$')
# plt.ylabel(r'$Frequências$')
# plt.ticklabel_format(axis='x', style='sci')
# ax.xaxis.set_major_formatter(formatter)
# plt.legend(umpire_labels, loc='best', frameon=False)
# plt.tight_layout()
# plt.savefig(f'../simulations/{directory}/UmpireLines.png')
# plt.clf()

# comparison_labels = umpire_labels + aggregate_labels
# plt.plot(data["Generation"], data[comparison_labels], linewidth=linewidth)
# ax = plt.gca()
# values = ax.get_yticks()
# ax.set_yticklabels(['{:,.0%}'.format(x) for x in values])
# ax.set_ylim([0, 1])
# ax.set_xlim([0, data["Generation"].max()])
# plt.xlabel(fr'$n_{{gerações}}$')
# plt.ylabel(r'$Frequências$')
# plt.ticklabel_format(axis='x', style='sci')
# ax.xaxis.set_major_formatter(formatter)
# plt.legend(comparison_labels, loc='best', frameon=False)
# plt.tight_layout()
# plt.savefig(f'../simulations/{directory}/ComparisonLines.png')
# plt.clf()

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
plt.savefig(f'../simulations/{directory}/Comparison.png')
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
plt.savefig(f'../simulations/{directory}/AggregateComparison.png')
plt.clf()

comparison_labels = umpire_labels + player_labels
sns.pairplot(data[comparison_labels], diag_kind="kde")
# plt.plot(data["Generation"], data[comparison_labels])
plt.legend(comparison_labels, loc='upper right')
plt.savefig(f'../simulations/{directory}/Pairplot.png')
plt.clf()
