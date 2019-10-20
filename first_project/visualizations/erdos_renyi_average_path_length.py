import matplotlib.pyplot as plt
import numpy as np

from models.erdos_renyi import ErdosRenyi


class ErdosRenyiAveragePathLength:
    """
    Creates a visualization of the average path length in the erdos_renyi
    as the probabilities.
    """

    def __init__(self):
        # self.number_of_nodes = range(25, 1000, 25)
        # self.number_of_nodes = range(25, 1000, 300)
        self.number_of_nodes = [25, 200, 400, 600, 1000]

        # self.number_of_simulations = 100
        self.number_of_simulations = 3

        self.link_probability = 0.4
        self.average_path_lengths = []
        self.approximations = []

        self.average_path_length()
        self.clean_plot()

    def average_path_length(self):
        for number_of_nodes in self.number_of_nodes:
            print(number_of_nodes)
            graphs = ErdosRenyi(
                self.number_of_simulations,
                number_of_nodes,
                self.link_probability
            )
            average_path_length = graphs.average_path_length()
            self.average_path_lengths.append(average_path_length)

            approximation = float(np.log(number_of_nodes)) / np.log(graphs.average_degree())
            self.approximations.append(approximation)


        # plt.plot(self.number_of_nodes, self.average_path_lengths, label=f'Comprimento do percurso médio')
        plt.plot(self.number_of_nodes, self.average_path_lengths, label=f'Resultado das simulações')
        plt.plot(self.number_of_nodes, self.approximations, label=f'Valor Teórico')

        plt.xlabel('Nodos')
        plt.ylabel('Comprimento do percurso médio')

        ax = plt.gca()

        plt.text(0.99, 0.07, f'Simulações: {self.number_of_simulations}',
                 horizontalalignment='right',
                 verticalalignment='baseline',
                 transform=ax.transAxes)

        plt.text(0.99, 0.02, f'Probabilidade de ligação: {self.link_probability:,.1%}',
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
        plt.tight_layout()
        # plt.savefig('images/erdos_renyi_average_path_length.png')
        plt.savefig('images/wip/erdos_renyi_average_path_length.png')
        plt.clf()
