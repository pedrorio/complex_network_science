import networkx as nx

from model import Model


class ErdosRenyi(Model):

    def __init__(
            self,
            number_of_simulations,
            number_of_initial_nodes,
            probability_of_rewiring_each_node
    ):
        self.graphs = []
        self.number_of_simulations = number_of_simulations
        self.number_of_initial_nodes = number_of_initial_nodes
        self.probability_of_rewiring_each_node = probability_of_rewiring_each_node

        self.generate_graphs()

    def generate_graphs(
            self
    ):
        # generate a graph n times
        for simulation_number in range(self.number_of_simulations):
            # for number_of_initial_nodes in initial_nodes_numbers:
            # for probability_of_rewiring_each_node in probabilities_of_rewiring_each_node:
            watts_strogatz = nx.erdos_renyi_graph(
                self.number_of_initial_nodes,
                self.probability_of_rewiring_each_node
            )

            self.graphs.append(watts_strogatz)

        return self.graphs
