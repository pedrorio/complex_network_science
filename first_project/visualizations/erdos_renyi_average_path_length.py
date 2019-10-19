import matplotlib.pyplot as plt

from models.erdos_renyi import ErdosRenyi


class ErdosRenyiAveragePathLength:
    """
    Creates a visualization of the average path length in the erdos_renyi
    as the probabilities.
    """

    def __init__(self):
        self.number_of_initial_nodes = range(25, 1000, 25)
        # self.number_of_initial_nodes = range(25, 1000, 500)

        self.number_of_simulations = 100
        # self.number_of_simulations = 1

        self.rewiring_probability = 0.4
        self.average_path_lengths = []

        self.average_path_length()
        self.clean_plot()

    def average_path_length(self):
        for number_of_nodes in self.number_of_initial_nodes:
            print(number_of_nodes)
            average_path_length = ErdosRenyi(
                self.number_of_simulations,
                number_of_nodes,
                self.rewiring_probability
            ).average_path_length()
            self.average_path_lengths.append(average_path_length)
        plt.plot(self.number_of_initial_nodes, self.average_path_lengths)
        plt.xlabel('Number of nodes')
        plt.ylabel('Average path length')

        ax = plt.gca()

        plt.text(0.99, 0.07, f'Simulations: {self.number_of_simulations}',
                 horizontalalignment='right',
                 verticalalignment='baseline',
                 transform=ax.transAxes)

        plt.text(0.99, 0.02, f'Rewiring probability: {self.rewiring_probability:,.1%}',
                 horizontalalignment='right',
                 verticalalignment='baseline',
                 transform=ax.transAxes)

    @staticmethod
    def clean_plot():
        """
        saves the image and cleans the plot
        """
        plt.tight_layout()
        plt.savefig('images/erdos_renyi_average_path_length.png')
        plt.clf()
