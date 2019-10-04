import networkx as nx
import numpy as np


def graph_simulation(graph_list):

    final_degree_count = np.zeros([0])

    for graph in graph_list:

        degree_count = np.asarray(nx.degree_histogram(graph))

        final_degree_count_length = len(final_degree_count)
        degree_count_length = len(degree_count)

        length_differential = final_degree_count_length - degree_count_length

        if length_differential > 0:
            degree_count = np.append(degree_count, np.zeros([abs(length_differential)]))
        elif length_differential < 0:
            final_degree_count = np.append(final_degree_count, np.zeros([abs(length_differential)]))

        final_degree_count = np.add(final_degree_count, degree_count)

    final_degree_count = final_degree_count / len(graph_list)

    return final_degree_count


def simulation_per_simulation_number(
        simulation_numbers,
        initial_nodes_numbers,
        probabilities_of_rewiring_each_node
):
    graphs_per_simulation_number = []
    # graphs_per_initial_node_number = []
    # graphs_per_probability_of_rewiring_each_node = []

    for simulation_number in simulation_numbers:
        probability_of_rewiring_each_node = probabilities_of_rewiring_each_node[1]
        initial_nodes_number = initial_nodes_numbers[-1]

        # for initial_nodes_number in initial_nodes_numbers:
        # for probability_of_rewiring_each_node in probabilities_of_rewiring_each_node:
        erdos_renyi = nx.erdos_renyi_graph(
            initial_nodes_number,
            probability_of_rewiring_each_node
        )

        graphs_per_simulation_number.append(erdos_renyi)

    graph_simulation(graphs_per_simulation_number)


simulation_numbers = range(10, 100)
initial_nodes_numbers = range(500, 5000, 500)
probabilities_of_rewiring_each_node = np.arange(0.05, 1.0, 0.05)

simulation_per_simulation_number(simulation_numbers, initial_nodes_numbers, probabilities_of_rewiring_each_node)
