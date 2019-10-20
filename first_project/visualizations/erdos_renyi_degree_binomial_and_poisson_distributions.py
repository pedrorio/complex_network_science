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
        self.number_of_simulations = 100

        self.low_number_of_nodes = 100
        self.high_number_of_nodes = 10000

        self.link_probability = 0.4
        self.link_probability_with_low_number_of_nodes = 0.4

        self.average_with_low_number_of_nodes = \
            (self.low_number_of_nodes - 1) * self.link_probability_with_low_number_of_nodes
        self.average_with_high_number_of_initial_nodes = self.average_with_low_number_of_nodes

        self.link_probability_with_high_number_of_nodes = \
            self.average_with_low_number_of_nodes / (self.high_number_of_nodes - 1)

        self.with_low_number_of_nodes()
        self.with_high_number_of_nodes()

    def with_low_number_of_nodes(self):
        degree_distribution = ErdosRenyi(
            self.number_of_simulations, self.low_number_of_nodes,
            self.link_probability
        ).degree_distribution()
        degrees = list(index for index, value in enumerate(degree_distribution))

        degrees, degree_distribution = zip(
            *((degree, count) for degree, count in zip(degrees, degree_distribution) if
              count != 0))

        plt.plot(degrees, degree_distribution, '-o', linewidth=2, markersize=4)

        binomial_average = (self.low_number_of_nodes - 1) * self.link_probability
        print(binomial_average)

        x_binom = np.arange(
            stats.binom.ppf(0.01, self.low_number_of_nodes - 1, self.link_probability),
            stats.binom.ppf(0.99, self.low_number_of_nodes - 1, self.link_probability)
        )
        plt.plot(x_binom,
                 stats.binom.pmf(x_binom, self.low_number_of_nodes - 1, self.link_probability),
                 label=f'Binomial')

        poisson_average = (self.low_number_of_nodes - 1) * self.link_probability
        print(poisson_average)
        x_poisson = np.arange(
            stats.poisson.ppf(0.01, poisson_average),
            stats.poisson.ppf(0.99, poisson_average)
        )
        plt.plot(x_poisson, stats.poisson.pmf(x_poisson, poisson_average), label=f'Poisson')

        plt.xlabel(r'$k$')
        plt.ylabel(r'$p^k$')
        ax = plt.gca()

        values = ax.get_yticks()
        ax.set_yticklabels(['{:,.1%}'.format(x) for x in values])

        plt.text(0.01, 0.95, fr'$n_{{nodos}}={self.low_number_of_nodes}$',
                 horizontalalignment='left',
                 verticalalignment='baseline',
                 transform=ax.transAxes)
        plt.text(0.01, 0.90, fr'$n_{{simulações}}={self.number_of_simulations}$',
                 horizontalalignment='left',
                 verticalalignment='baseline',
                 transform=ax.transAxes)

        plt.text(0.01, 0.85, fr'$p_{{ligação|binomial}}={self.link_probability_with_low_number_of_nodes:,.1%}$' + '%',
                 horizontalalignment='left',
                 verticalalignment='baseline',
                 transform=ax.transAxes)
        plt.text(0.01, 0.80, fr'$p_{{ligação|poisson}}={self.link_probability_with_high_number_of_nodes:,.1%}$' + '%',
                 horizontalalignment='left',
                 verticalalignment='baseline',
                 transform=ax.transAxes)

        plt.legend(loc='best', frameon=False)
        plt.tight_layout()
        plt.savefig('report/images/erdos_renyi_degree_binomial_and_poisson_distributions_low_number_of_initial_nodes.png')
        plt.clf()

    def with_high_number_of_nodes(self):
        degree_distribution = ErdosRenyi(
            self.number_of_simulations,
            self.high_number_of_nodes,
            self.link_probability_with_high_number_of_nodes
        ).degree_distribution()
        degrees = list(index for index, value in enumerate(degree_distribution))

        degrees, degree_distribution = zip(
            *((degree, count) for degree, count in zip(degrees, degree_distribution) if
              count != 0))

        plt.plot(degrees, degree_distribution, '-o', linewidth=2, markersize=4)

        binomial_average = (
                                   self.high_number_of_nodes - 1) * self.link_probability_with_high_number_of_nodes
        print(binomial_average)
        x_binom = np.arange(
            stats.binom.ppf(0.01, self.high_number_of_nodes - 1,
                            self.link_probability_with_high_number_of_nodes),
            stats.binom.ppf(0.99, self.high_number_of_nodes - 1,
                            self.link_probability_with_high_number_of_nodes)
        )
        plt.plot(x_binom,
                 stats.binom.pmf(x_binom, self.high_number_of_nodes - 1,
                                 self.link_probability_with_high_number_of_nodes),
                 label=f'Binomial')

        poisson_average = (
                                  self.high_number_of_nodes - 1) * self.link_probability_with_high_number_of_nodes
        print(poisson_average)
        x_poisson = np.arange(
            stats.poisson.ppf(0.01, poisson_average),
            stats.poisson.ppf(0.99, poisson_average)
        )
        plt.plot(
            x_poisson,
            stats.poisson.pmf(x_poisson, poisson_average),
            label=f'Poisson'
        )

        plt.xlabel(r'$k$')
        plt.ylabel(r'$p^k$')
        ax = plt.gca()

        values = ax.get_yticks()
        ax.set_yticklabels(['{:,.1%}'.format(x) for x in values])

        plt.text(0.01, 0.95, fr'$n_{{nodos}}={self.high_number_of_nodes}$',
                 horizontalalignment='left',
                 verticalalignment='baseline',
                 transform=ax.transAxes)
        plt.text(0.01, 0.9, fr'$n_{{simulações}}={self.number_of_simulations}$',
                 horizontalalignment='left',
                 verticalalignment='baseline',
                 transform=ax.transAxes)
        plt.text(0.01, 0.85, fr'$p_{{ligação|poisson}}={self.link_probability_with_high_number_of_nodes:,.1%}$' + '%',
                 horizontalalignment='left',
                 verticalalignment='baseline',
                 transform=ax.transAxes)
        plt.text(0.01, 0.80, fr'$p_{{ligação|binomial}}={self.link_probability_with_low_number_of_nodes:,.1%}$' + '%',
                 horizontalalignment='left',
                 verticalalignment='baseline',
                 transform=ax.transAxes)

        plt.legend(loc='best', frameon=False)
        plt.tight_layout()
        plt.savefig('report/images/erdos_renyi_degree_binomial_and_poisson_distributions_high_number_of_initial_nodes.png')
        plt.clf()
