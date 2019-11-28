import seaborn as sns
import pandas as pd
import matplotlib.pyplot as plt

# data = pd.read_csv('../cpp/output.csv', index_col="Generation")
data = pd.read_csv('../cpp/output.csv')
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
plt.legend(loc='upper right')
plt.savefig('Players.png')
plt.clf()

plt.plot(data["Generation"], data[player_labels])
plt.legend(player_labels, loc='upper right')
plt.savefig('PlayerLines.png')
plt.clf()

plt.stackplot(data["Generation"], data[aggregate_labels].T, labels=aggregate_labels, colors=pal, alpha=0.4)
plt.legend(loc='upper right')
plt.savefig('Aggregate.png')
plt.clf()

plt.plot(data["Generation"], data[aggregate_labels])
plt.legend(aggregate_labels, loc='upper right')
plt.savefig('AggregateLines.png')
plt.clf()

umpire_labels = ["Honest", "Corrupt"]
plt.stackplot(data["Generation"], data[umpire_labels].T, labels=umpire_labels, colors=pal, alpha=0.4)
plt.legend(loc='upper right')
plt.savefig('Umpires.png')
plt.clf()

plt.plot(data["Generation"], data[umpire_labels])
plt.legend(umpire_labels, loc='upper right')
plt.savefig('UmpireLines.png')
plt.clf()

comparison_labels = umpire_labels + aggregate_labels
print(comparison_labels)
plt.plot(data["Generation"], data[comparison_labels])
plt.legend(comparison_labels, loc='upper right')
plt.savefig('ComparisonLines.png')
plt.clf()
