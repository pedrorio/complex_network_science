import networkx as nx
import numpy as np
import matplotlib.pyplot as plt

seed_number = 356


def degree_distribution(graphs):
    final_degree_count = np.zeros([0])

    for graph in graphs:

        degree_count = np.asarray(nx.degree_histogram(graph))

        final_degree_count_length = len(final_degree_count)
        degree_count_length = len(degree_count)

        length_differential = final_degree_count_length - degree_count_length

        if length_differential > 0:
            degree_count = np.append(degree_count, np.zeros([abs(length_differential)]))
        elif length_differential < 0:
            final_degree_count = np.append(final_degree_count, np.zeros([abs(length_differential)]))

        final_degree_count = np.add(final_degree_count, degree_count)

    final_degree_count = final_degree_count / len(graphs)
    print(final_degree_count)

    return final_degree_count


def simulation(
        number_of_simulations,
        number_of_initial_nodes,
        probability_of_rewiring_each_node
):
    graphs = []

    # generate a graph n times
    for simulation_number in range(number_of_simulations):
        # for number_of_initial_nodes in initial_nodes_numbers:
        # for probability_of_rewiring_each_node in probabilities_of_rewiring_each_node:
        erdos_renyi = nx.erdos_renyi_graph(
            number_of_initial_nodes,
            probability_of_rewiring_each_node,
            seed_number
        )

        graphs.append(erdos_renyi)

    # compute the degree distribution for all the graphs
    return degree_distribution(graphs)


# number_of_simulations = range(10, 101)[-1]
# number_of_initial_nodes = range(500, 5000, 500)[0]
# probability_of_rewiring_each_node = np.arange(0.05, 1.0, 0.05)[0]

# count = simulation(number_of_simulations, number_of_initial_nodes, probability_of_rewiring_each_node)

# understand the effect of the number of simulations
# ==================================================
number_of_simulation_runs = [10, 100, 1000]
number_of_initial_nodes = 100
probability_of_rewiring_each_node = 0.01
for number_of_simulations in number_of_simulation_runs:
    count = simulation(number_of_simulations, number_of_initial_nodes, probability_of_rewiring_each_node)
    degrees = [index for index, value in enumerate(count)]
    plt.scatter(degrees, count, label=f'{number_of_simulations} runs')

# degrees = [index for index, value in enumerate(count)]
# plt.scatter(degrees, count, label=f'{number_of_simulations} runs')
plt.legend(loc='upper left')
plt.savefig('number_of_simulation_runs.png')
# plt.show()
plt.clf()

# understand the effect of the number of initial nodes
# ====================================================
number_of_simulation_runs = 100
number_of_initial_nodes = [10, 100, 1000]
probability_of_rewiring_each_node = 0.01
for number_of_nodes in number_of_initial_nodes:
    count = simulation(number_of_simulation_runs, number_of_nodes, probability_of_rewiring_each_node)
    degrees = [index for index, value in enumerate(count)]
    plt.scatter(degrees, count, label=f'{number_of_nodes} initial nodes')

plt.legend(loc='upper left')
plt.savefig('number_of_initial_nodes.png')
# plt.show()
plt.clf()

# understand the effect of the probability of rewiring each node
# ==============================================================
number_of_simulation_runs = 100
number_of_initial_nodes = 100
probability_of_rewiring_each_node = [0.05, 0.5, 1]
for probability in probability_of_rewiring_each_node:
    count = simulation(number_of_simulation_runs, number_of_initial_nodes, probability)
    degrees = [index for index, value in enumerate(count)]
    plt.scatter(degrees, count, label=f'P[rewiring each node] = {probability*100}%')

plt.legend(loc='upper left')
plt.savefig('probability_of_rewiring_each_node.png')
# plt.show()
plt.clf()

# fig = plt.figure()
# ax1 = fig.add_subplot(111)
# ax1.scatter(degrees, count, s=10, c='b', marker="s", label='first')
# ax1.scatter(degrees, count, s=10, c='r', marker="o", label='second')
# plt.legend(loc='upper left');
# plt.show()

# for a list of number of simulations
# for a list of initial node numbers
# for a list
