import matplotlib.pyplot as plt

from models.watts_strogatz import WattsStrogatz


class WattsStrogatzClusteringCoefficientAndAveragePathLength:
    """
    Creates a visualization of the clustering coefficient
    and the average path length in the erdos_renyi model.
    """

    def __init__(self):
        self.number_of_simulations = 100
        # self.number_of_simulations = 1

        self.number_of_initial_nodes = 2000
        # self.number_of_initial_nodes = 100

        self.rewiring_probability = 0
        self.k_nearest_neighbours = 4

        self.probability_step = 0.001

        self.C0 = WattsStrogatz(
            self.number_of_simulations,
            self.number_of_initial_nodes,
            self.rewiring_probability,
            self.k_nearest_neighbours
        ).clustering_coefficient_mean()

        self.L0 = WattsStrogatz(
            self.number_of_simulations,
            self.number_of_initial_nodes,
            self.rewiring_probability,
            self.k_nearest_neighbours
        ).average_path_length()

        self.rewiring_probabilities = []
        self.average_clustering_coefficients = []
        self.average_path_length = []

        self.clustering_coefficient_and_average_path_length()
        self.plot()
        self.clean_plot()

    def clustering_coefficient_and_average_path_length(self):
        while self.rewiring_probability < 1:
            graphs = WattsStrogatz(
                self.number_of_simulations,
                self.number_of_initial_nodes,
                self.rewiring_probability,
                self.k_nearest_neighbours
            )

            clustering_coefficient = graphs.clustering_coefficient_mean() / self.C0
            average_path_length = graphs.average_path_length() / self.L0

            self.average_clustering_coefficients.append(clustering_coefficient)
            self.average_path_length.append(average_path_length)
            self.rewiring_probabilities.append(self.rewiring_probability)

            print(self.rewiring_probability)

            self.rewiring_probability += self.probability_step

    def plot(self):
        plt.axes(xscale='log')
        plt.xlabel('Rewiring probability')
        plt.ylabel('Clustering path length')
        plt.plot(self.rewiring_probabilities, self.average_clustering_coefficients,
                 label='L/L0')
        plt.plot(self.rewiring_probabilities, self.average_path_length,
                 label='C/C0')

        ax = plt.gca()
        plt.text(0.01, 0.12, f'Neighbours: {self.k_nearest_neighbours}',
                 horizontalalignment='left',
                 verticalalignment='baseline',
                 transform=ax.transAxes)

        plt.text(0.01, 0.07, f'Simulations: {self.number_of_simulations}',
                 horizontalalignment='left',
                 verticalalignment='baseline',
                 transform=ax.transAxes)

        plt.text(0.01, 0.02, f'Initial nodes: {self.number_of_initial_nodes}',
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
        plt.savefig('images/watts_strogatz_clustering_coefficient_and_average_path_length.png')
        plt.clf()
