import networkx as nx
import numpy as np


class Model:
    """
    Groups several functions (degree_distribution, clustering_coefficient_mean
    and average_path_length) to be used with several models.
    """

    def __init__(self, graphs):
        self.graphs = graphs

    def average_degree(self):
        """
        :return: average_degree
        """
        average_degrees = 0
        for graph in self.graphs:
            nodes, links = graph.order(), graph.size()
            average_degrees += links / nodes

        return average_degrees / len(self.graphs)

    def degree_distribution(self):
        """
        :return: degree_distribution
        """

        final_degree_count = np.zeros([0])

        for graph in self.graphs:

            degree_count = np.asarray(nx.degree_histogram(graph))

            final_degree_count_length = len(final_degree_count)
            degree_count_length = len(degree_count)

            length_differential = final_degree_count_length - degree_count_length

            if length_differential > 0:
                degree_count = np.append(degree_count, np.zeros([abs(length_differential)]))
            elif length_differential < 0:
                final_degree_count = np.append(final_degree_count, np.zeros([abs(length_differential)]))

            final_degree_count = np.add(final_degree_count, degree_count)

        final_degree_count = final_degree_count / len(self.graphs)

        probabilities_final_degree_count = final_degree_count / sum(final_degree_count)

        return probabilities_final_degree_count

    def clustering_coefficient_mean(self):
        """
        :return: clustering_coefficient_mean
        """
        averages = 0
        for graph in self.graphs:
            clustering_of_all_nodes = nx.clustering(graph)
            averages += sum(clustering_of_all_nodes.values()) / nx.number_of_nodes(graph)

        return averages / len(self.graphs)

    def average_path_length(self):
        """
        :return: average_shortest_path_length
        """
        average_path_length = 0
        for graph in self.graphs:
            average_path_length += nx.average_shortest_path_length(graph)

        return average_path_length / len(self.graphs)
