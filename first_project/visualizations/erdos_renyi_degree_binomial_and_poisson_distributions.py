import matplotlib.pyplot as plt

from models.erdos_renyi import ErdosRenyi
import numpy as np
import scipy.stats as stats


class ErdosRenyiDegreeBinomialAndPoissonDistributions:
    """
    Creates a graphical comparison between the degree distribution and the binomial and poisson distributions
    for the erdos_renyi and the watts_strogatz models varying the model probabilities.
    """

    def __init__(self):
        self.number_of_simulations = 20
        self.number_of_simulations = 10

        self.rewiring_probability = 0.4

        self.low_number_of_initial_nodes = 100
        self.high_number_of_initial_nodes = 10000

        self.fig, self.axes = self.setup_figure()

        self.with_low_number_of_initial_nodes()
        self.with_high_number_of_initial_nodes()

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
        self.axes[0].legend(loc='best', frameon=False)
        self.axes[1].legend(loc='best', frameon=False)
        plt.savefig('images/erdos_renyi_degree_binomial_and_poisson_distributions.png')
        plt.clf()

    def with_low_number_of_initial_nodes(self):
        degree_distribution = ErdosRenyi(
            self.number_of_simulations, self.low_number_of_initial_nodes,
            self.rewiring_probability
        ).degree_distribution()
        degrees = list(index for index, value in enumerate(degree_distribution))
        self.axes[0].plot(degrees, degree_distribution, '-o', linewidth=2, markersize=4)

        binomial_average = self.low_number_of_initial_nodes * self.rewiring_probability
        print(binomial_average)
        x_binom = np.arange(
            stats.binom.ppf(0.01, self.low_number_of_initial_nodes, self.rewiring_probability),
            stats.binom.ppf(0.99, self.low_number_of_initial_nodes, self.rewiring_probability)
        )
        self.axes[0].plot(x_binom,
                          stats.binom.pmf(x_binom, self.low_number_of_initial_nodes, self.rewiring_probability),
                          label=f'binomial')

        poisson_average = (self.low_number_of_initial_nodes - 1) * self.rewiring_probability
        print(poisson_average)
        x_poisson = np.arange(
            stats.poisson.ppf(0.01, poisson_average),
            stats.poisson.ppf(0.99, poisson_average)
        )
        self.axes[0].plot(x_poisson, stats.poisson.pmf(x_poisson, poisson_average), label=f'poisson')

        self.axes[0].set_xlim([25, 55])

    def with_high_number_of_initial_nodes(self):
        degree_distribution = ErdosRenyi(
            self.number_of_simulations,
            self.high_number_of_initial_nodes,
            self.rewiring_probability
        ).degree_distribution()
        degrees = list(index for index, value in enumerate(degree_distribution))
        self.axes[1].plot(degrees, degree_distribution, '-o', linewidth=2, markersize=4)

        binomial_average = self.high_number_of_initial_nodes * self.rewiring_probability
        print(binomial_average)
        x_binom = np.arange(
            stats.binom.ppf(0.01, self.high_number_of_initial_nodes, self.rewiring_probability),
            stats.binom.ppf(0.99, self.high_number_of_initial_nodes, self.rewiring_probability)
        )
        self.axes[1].plot(x_binom,
                          stats.binom.pmf(x_binom, self.high_number_of_initial_nodes, self.rewiring_probability),
                          label=f'binomial')

        poisson_average = (self.high_number_of_initial_nodes - 1) * self.rewiring_probability
        print(poisson_average)
        x_poisson = np.arange(
            stats.poisson.ppf(0.01, poisson_average),
            stats.poisson.ppf(0.99, poisson_average)
        )
        self.axes[1].plot(
            x_poisson,
            stats.poisson.pmf(x_poisson, poisson_average),
            label=f'poisson'
        )

        self.axes[1].set_xlim([3750, 4250])
