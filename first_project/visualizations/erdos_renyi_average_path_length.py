import matplotlib.pyplot as plt
import numpy as np

from models.erdos_renyi import ErdosRenyi


class ErdosRenyiAveragePathLength:
    """
    Creates a visualization of the average path length in the erdos_renyi
    as the probabilities.
    """

    def __init__(self):
        self.number_of_simulations = 3

        self.initial_number_of_nodes = 50
        self.step = 100
        self.final_number_of_nodes = 5000

        self.link_probability = 0.4
        self.average_path_lengths = []
        self.theoretical_values = []
        self.number_of_nodes = []
        self.errors = []
        self.error_derivatives = []

        self.average = (self.initial_number_of_nodes - 1) * self.link_probability

        self.average_path_length()
        self.clean_plot()

    def average_path_length(self):
        number_of_nodes = self.initial_number_of_nodes
        while number_of_nodes <= self.final_number_of_nodes:
            # print('nodes', number_of_nodes)

            self.link_probability = self.average / (number_of_nodes - 1)

            graphs = ErdosRenyi(
                self.number_of_simulations,
                number_of_nodes,
                self.link_probability
            )

            average_path_length = graphs.average_path_length()
            self.average_path_lengths.append(average_path_length)

            self.number_of_nodes.append(number_of_nodes)

            # theoretical values
            average_degree = (number_of_nodes - 1) * self.link_probability
            theoretical_value = np.log(number_of_nodes)/np.log(average_degree)
            theoretical_value = np.log(number_of_nodes)/np.log(self.average)
            self.theoretical_values.append(theoretical_value)

            # errors
            error = theoretical_value - average_path_length
            self.errors.append(error)
            print('error', error)

            number_of_nodes += self.step

        plt.plot(self.number_of_nodes, self.average_path_lengths, label=rf'$<k>={self.average}$')

        # theoretical values
        plt.plot(self.number_of_nodes, self.theoretical_values, label=rf'$<k>={self.average} | theory$')
        # errors
        plt.plot(self.number_of_nodes, self.errors, label=rf'$<k>={self.average} | error$')

        self.error_derivatives = np.diff(self.errors)
        print(self.error_derivatives)
        print(sum(self.error_derivatives))
        plt.plot(self.number_of_nodes[0:-1], self.error_derivatives, label='error derivatives')

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
