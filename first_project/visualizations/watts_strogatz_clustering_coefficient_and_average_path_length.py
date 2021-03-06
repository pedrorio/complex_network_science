import matplotlib.pyplot as plt
from matplotlib import rc

from models.watts_strogatz import WattsStrogatz


class WattsStrogatzClusteringCoefficientAndAveragePathLength:
    """
    Creates a visualization of the clustering coefficient
    and the average path length in the erdos_renyi model.
    """

    def __init__(self):
        self.number_of_simulations = 100
        self.number_of_nodes = 200
        self.rewiring_probability = 0
        self.k_nearest_neighbours = 4

        self.probability_step = 0.001

        self.C_0_GRAPHS = WattsStrogatz(
            self.number_of_simulations,
            self.number_of_nodes,
            self.rewiring_probability,
            self.k_nearest_neighbours
        )

        self.C0 = self.C_0_GRAPHS.clustering_coefficient_mean()

        self.L_0_GRAPH = WattsStrogatz(
            self.number_of_simulations,
            self.number_of_nodes,
            self.rewiring_probability,
            self.k_nearest_neighbours
        )
        self.L0 = self.L_0_GRAPH.average_path_length()

        self.rewiring_probabilities = []
        self.average_clustering_coefficients = []
        self.average_path_lengths = []

        self.clustering_coefficient_and_average_path_length()
        self.plot()
        self.clean_plot()

    def clustering_coefficient_and_average_path_length(self):
        while self.rewiring_probability <= 1:
            print("REWIRING PROBABILITY", self.rewiring_probability)
            graphs = WattsStrogatz(
                self.number_of_simulations,
                self.number_of_nodes,
                self.rewiring_probability,
                self.k_nearest_neighbours
            )

            clustering_coefficient = graphs.clustering_coefficient_mean() / self.C0
            average_path_length = graphs.average_path_length() / self.L0

            self.average_clustering_coefficients.append(clustering_coefficient)
            self.average_path_lengths.append(average_path_length)
            self.rewiring_probabilities.append(self.rewiring_probability)

            self.rewiring_probability += self.probability_step

    def plot(self):
        plt.axes(xscale='log')

        plt.xlabel(r'$p_{{ligação}}$')
        plt.ylabel(r'$<d> e <C> relativos$')

        plt.plot(self.rewiring_probabilities, self.average_clustering_coefficients,
                 label=r'$\frac{<C>_p}{<C>_0},\,centralidade$')

        plt.plot(self.rewiring_probabilities, self.average_path_lengths,
                 label=r'$\frac{<d>_p}{<d>_0},\,localidade$')

        ax = plt.gca()

        plt.text(0.01, 0.12, fr'$n_{{vizinhos}}={self.k_nearest_neighbours}$',
                 horizontalalignment='left',
                 verticalalignment='baseline',
                 transform=ax.transAxes)

        plt.text(0.01, 0.07, fr'$n_{{simulações}}={self.number_of_simulations}$',
                 horizontalalignment='left',
                 verticalalignment='baseline',
                 transform=ax.transAxes)

        plt.text(0.01, 0.02, fr'$n_{{nodos}}={self.number_of_nodes}$',
                 horizontalalignment='left',
                 verticalalignment='baseline',
                 transform=ax.transAxes)

        plt.legend(loc='best', frameon=False)
        plt.tight_layout()

    @staticmethod
    def clean_plot():
        """
        saves the image and cleans the plot
        """
        plt.savefig('report/images/watts_strogatz_clustering_coefficient_and_average_path_length.png')
        plt.clf()
