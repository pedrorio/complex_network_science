import networkx as nx

from models.model import Model


class ErdosRenyi(Model):
    """
    Generates and stores erdos_renyi graphs.
    Is able to compute the degree_distribution, clustering_coefficient_mean
    and average_path_length.
    """

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
        """
        :return: generated erdos renyi graphs
        """
        for simulation_number in range(self.number_of_simulations):
            erdos_renyi = nx.erdos_renyi_graph(
                self.number_of_initial_nodes,
                self.probability_of_rewiring_each_node
            )

            self.graphs.append(erdos_renyi)

        return self.graphs
