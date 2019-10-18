import matplotlib.pyplot as plt

from models.erdos_renyi import ErdosRenyi
from models.watts_strogatz import WattsStrogatz


class ErdosRenyiAndWattsStrogatzDegreeDistributions:
    """
    Creates a graphical comparison between the degree distributions
    for the erdos_renyi and the watts_strogatz models varying the model probabilities.
    """

    def __init__(self):
        self.number_of_simulations = 100
        self.number_of_simulations = 10

        self.number_of_initial_nodes = 10000
        self.number_of_initial_nodes = 1000

        self.k_nearest_neighbours = 4

        self.watts_strogatz_probabilities = [0, 0.1, 0.3]
        self.erdos_renyi_probabilities = [0.0001, 0.001, 0.0015]

        self.fig, self.axes = self.setup_figure()

        self.watts_strogatz_degree_distribution()
        self.erdos_renyi_degree_distribution()

        self.clean_figure()

    @staticmethod
    def setup_figure():
        """
        creates the subplots
        :return:the figures and the axis
        """
        return plt.subplots(nrows=1, ncols=2, figsize=(20, 5))

    def clean_figure(self):
        """
        saves the image and cleans the plots
        """
        self.fig.tight_layout()
        plt.savefig('images/erdos_renyi_and_watts_strogatz_degree_distributions.png')
        plt.clf()

    def watts_strogatz_degree_distribution(self):
        for probability in self.watts_strogatz_probabilities:
            print(probability)

            graphs = WattsStrogatz(
                self.number_of_simulations,
                self.number_of_initial_nodes,
                probability,
                self.k_nearest_neighbours
            )
            watts_strogatz_degree_histogram = graphs.degree_distribution()
            watts_strogatz_degrees = list((index for index, value in enumerate(watts_strogatz_degree_histogram)))

            self.axes[0].plot(
                watts_strogatz_degrees,
                watts_strogatz_degree_histogram,
                '-o',
                linewidth=2,
                markersize=8,
                label=f'p={probability}'
            )
        self.axes[0].legend(loc='best', frameon=False)
        self.axes[0].title.set_text('Watts Strogatz Degree Distribution')

    def erdos_renyi_degree_distribution(self):
        for probability in self.erdos_renyi_probabilities:
            print(probability)

            graphs = ErdosRenyi(self.number_of_simulations, self.number_of_initial_nodes, probability)
            erdos_renyi_degree_histogram = graphs.degree_distribution()
            erdos_renyi_degrees = list((index for index, value in enumerate(erdos_renyi_degree_histogram)))

            self.axes[1].set_ylim([0, 1])
            self.axes[1].set_xlim([0, 30])

            self.axes[1].plot(
                erdos_renyi_degrees,
                erdos_renyi_degree_histogram,
                '-o',
                linewidth=2,
                markersize=8,
                label=f'p={probability}'
            )
        self.axes[1].legend(loc='best', frameon=False)
        self.axes[1].title.set_text('Erdos Renyi Degree Distribution')
