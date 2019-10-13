import networkx as nx

from model import Model


class WattsStrogatz(Model):

    def __init__(
            self,
            number_of_simulations,
            number_of_initial_nodes,
            probability_of_rewiring_each_node,
            k_nearest_neighbours
    ):
        self.graphs = []

        self.number_of_simulations = number_of_simulations
        self.number_of_initial_nodes = number_of_initial_nodes
        self.probability_of_rewiring_each_node = probability_of_rewiring_each_node
        self.k_nearest_neighbours = k_nearest_neighbours

        self.generate_graphs()

    def generate_graphs(
            self
    ):
        # generate a graph n times
        for simulation_number in range(self.number_of_simulations):
            # for number_of_initial_nodes in initial_nodes_numbers:
            # for probability_of_rewiring_each_node in probabilities_of_rewiring_each_node:
            erdos_renyi = nx.watts_strogatz_graph(
                self.number_of_initial_nodes,
                self.k_nearest_neighbours,
                self.probability_of_rewiring_each_node
            )

            self.graphs.append(erdos_renyi)

        return self.graphs
