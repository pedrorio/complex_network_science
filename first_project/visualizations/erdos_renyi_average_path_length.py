import matplotlib.pyplot as plt

from models.erdos_renyi import ErdosRenyi


class ErdosRenyiAveragePathLength:
    """
    Creates a visualization of the average path length in the erdos_renyi
    as the probabilities.
    """

    def __init__(self):
        self.number_of_nodes = [100, 250, 500, 1000]
        self.number_of_simulations = 100

        self.link_probability = 0.4
        self.average_path_lengths = []
        self.approximations = []
        self.errors = []

        self.average = (self.number_of_nodes[0] - 1) * self.link_probability

        self.average_path_length()
        self.clean_plot()

    def average_path_length(self):
        for number_of_nodes in self.number_of_nodes:
            print('nodes', number_of_nodes)

            self.link_probability = self.average / (number_of_nodes - 1)

            graphs = ErdosRenyi(
                self.number_of_simulations,
                number_of_nodes,
                self.link_probability
            )
            average_path_length = graphs.average_path_length()
            self.average_path_lengths.append(average_path_length)

        plt.plot(self.number_of_nodes, self.average_path_lengths, label=rf'$<k>={self.average}$')

        plt.xlabel(r'$n_{{nodos}}$')
        plt.ylabel(r'$<d>$')

        ax = plt.gca()

        plt.text(0.99, 0.02, fr'$n_{{simulações}}={self.number_of_simulations}$',
                 horizontalalignment='right',
                 verticalalignment='baseline',
                 transform=ax.transAxes)

        plt.legend(loc='best', frameon=False)
        plt.tight_layout()

    @staticmethod
    def clean_plot():
        """
        saves the image and cleans the plot
        """
        plt.savefig('report/images/erdos_renyi_average_path_length.png')
        plt.clf()
