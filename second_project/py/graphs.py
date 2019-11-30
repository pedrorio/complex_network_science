import os
import seaborn as sns
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.ticker import EngFormatter

directories = sorted(os.listdir('../simulations'))
directory = directories[-1]

data = pd.read_csv(f'../simulations/{directory}/output.csv')

formatter = EngFormatter(places=0, sep="\N{THIN SPACE}")  # U+2009

# print(data)

# sns.relplot(x="Generation", y="OptimisticCooperator", kind="line", data=data)
# sns.relplot(x="Generation", y="OptimisticDefector", kind="line", data=data)
# sns.relplot(x="Generation", y="PrudentCooperator", kind="line", data=data)
# sns.relplot(x="Generation", y="PrudentDefector", kind="line", data=data)
# sns.relplot(x="Generation", y="Honest", kind="line", data=data)
# sns.relplot(x="Generation", y="Corrupt", kind="line", data=data)
# plt.show()
# sns.lineplot(data=data)

# data.plot.area()
# data[["OptimisticCooperator", "OptimisticDefector", "PrudentCooperator", "PrudentDefector"]].plot.area()
# data[["Honest", "Corrupt"]].plot.area()
# plt.stackplot(x=data["Generation"], y=data[])

pal = sns.color_palette("Set1")

data['Cooperator'] = data["OptimisticCooperator"] + data["PrudentCooperator"]
data['Defector'] = data["OptimisticDefector"] + data["PrudentDefector"]
aggregate_labels = ["Cooperator", "Defector"]

player_labels = ["OptimisticCooperator", "OptimisticDefector", "PrudentCooperator", "PrudentDefector"]
plt.stackplot(data["Generation"], data[player_labels].T, labels=player_labels, colors=pal, alpha=0.4)


ax = plt.gca()
values = ax.get_yticks()
ax.set_yticklabels(['{:,.0%}'.format(x) for x in values])
ax.set_ylim([0, 1])
ax.set_xlim([0, data["Generation"].max()])

plt.xlabel(fr'$n_{{gerações}}$')
plt.ylabel(r'$Frequências$')
# plt.text(0.01, 0.07, fr'$a=$',
#                  horizontalalignment='left',
#                  verticalalignment='baseline',
#                  transform=ax.transAxes)

plt.ticklabel_format(axis='x', style='sci')
ax.xaxis.set_major_formatter(formatter)

plt.legend(loc='best', frameon=False)
plt.tight_layout()

plt.savefig(f"../simulations/{directory}/Players.png")
plt.clf()

plt.plot(data["Generation"], data[player_labels])
plt.legend(player_labels, loc='upper right')
plt.savefig(f'../simulations/{directory}/PlayerLines.png')
plt.clf()

plt.stackplot(data["Generation"], data[aggregate_labels].T, labels=aggregate_labels, colors=pal, alpha=0.4)
plt.legend(loc='upper right')
plt.savefig(f'../simulations/{directory}/Aggregate.png')
plt.clf()

plt.plot(data["Generation"], data[aggregate_labels])
plt.legend(aggregate_labels, loc='upper right')
plt.savefig(f'../simulations/{directory}/AggregateLines.png')
plt.clf()

umpire_labels = ["Honest", "Corrupt"]
plt.stackplot(data["Generation"], data[umpire_labels].T, labels=umpire_labels, colors=pal, alpha=0.4)
plt.legend(loc='upper right')
plt.savefig(f'../simulations/{directory}/Umpires.png')
plt.clf()

plt.plot(data["Generation"], data[umpire_labels])
plt.legend(umpire_labels, loc='upper right')
plt.savefig(f'../simulations/{directory}/UmpireLines.png')
plt.clf()

comparison_labels = umpire_labels + aggregate_labels
plt.plot(data["Generation"], data[comparison_labels])
plt.legend(comparison_labels, loc='upper right')
plt.savefig(f'../simulations/{directory}/ComparisonLines.png')
plt.clf()

comparison_labels = player_labels
sns.pairplot(data[comparison_labels], diag_kind="reg")
# plt.plot(data["Generation"], data[comparison_labels])
# # plt.legend(comparison_labels, loc='upper right')
plt.savefig(f'../simulations/{directory}/Pairplot.png')
plt.clf()
