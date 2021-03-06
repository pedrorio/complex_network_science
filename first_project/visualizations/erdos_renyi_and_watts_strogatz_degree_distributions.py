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
        self.number_of_nodes = 10000
        self.k_neighbours = 4

        self.watts_strogatz_probabilities = [0, 0.1, 0.2, 0.4, 0.8, 1]
        self.erdos_renyi_probabilities = [0.0001, 0.001, 0.0015]

        self.watts_strogatz_degree_distribution()
        self.erdos_renyi_degree_distribution()

    def watts_strogatz_degree_distribution(self):
        for probability in self.watts_strogatz_probabilities:
            graphs = yield WattsStrogatz(
                self.number_of_simulations,
                self.number_of_nodes,
                probability,
                self.k_neighbours
            )

            watts_strogatz_degree_histogram = graphs.degree_distribution()
            watts_strogatz_degrees = list((index for index, value in enumerate(watts_strogatz_degree_histogram)))

            watts_strogatz_degrees, watts_strogatz_degree_histogram = zip(
                *((degree, count) for degree, count in zip(watts_strogatz_degrees, watts_strogatz_degree_histogram) if
                  count >= 0.001))

            plt.plot(
                watts_strogatz_degrees,
                watts_strogatz_degree_histogram,
                '-o',
                linewidth=2,
                markersize=8,
                label=fr'$p_{{ligação}}={probability:,.1%}$' + '%'
            )
            print(probability)

        plt.xlabel(r'$k$')
        plt.ylabel(r'$p^k$')

        ax = plt.gca()

        values = ax.get_yticks()
        ax.set_yticklabels(['{:,.1%}'.format(x) for x in values])

        plt.text(0.95, 0.20, fr'$n_{{vizinhos}}={self.k_neighbours}$',
                 horizontalalignment='right',
                 verticalalignment='baseline',
                 transform=ax.transAxes)

        plt.text(0.95, 0.15, fr'$n_{{simulações}}={self.number_of_simulations}$',
                 horizontalalignment='right',
                 verticalalignment='baseline',
                 transform=ax.transAxes)

        plt.text(0.95, 0.10, fr'$n_{{nodos}}={self.number_of_nodes}$',
                 horizontalalignment='right',
                 verticalalignment='baseline',
                 transform=ax.transAxes)

        plt.legend(loc='best', frameon=False)
        plt.tight_layout()
        plt.savefig('reprot/images/watts_strogatz_degree_distribution.png')
        plt.clf()

    def erdos_renyi_degree_distribution(self):
        for probability in self.erdos_renyi_probabilities:
            graphs = ErdosRenyi(self.number_of_simulations, self.number_of_nodes, probability)

            erdos_renyi_degree_histogram = graphs.degree_distribution()
            erdos_renyi_degrees = list((index for index, value in enumerate(erdos_renyi_degree_histogram)))

            erdos_renyi_degrees, erdos_renyi_degree_histogram = zip(
                *((degree, count) for degree, count in zip(erdos_renyi_degrees, erdos_renyi_degree_histogram) if
                  count >= 0.001))

            plt.plot(
                erdos_renyi_degrees,
                erdos_renyi_degree_histogram,
                '-o',
                linewidth=2,
                markersize=8,
                label=fr'$p_{{ligação}}={probability:,.2%}$' + '%'
            )
            print(probability)

        plt.xlabel(r'$k$')
        plt.ylabel(r'$p^k$')

        ax = plt.gca()

        values = ax.get_yticks()
        ax.set_yticklabels(['{:,.1%}'.format(x) for x in values])

        plt.text(0.95, 0.20, fr'$n_{{simulações}}={self.number_of_simulations}$',
                 horizontalalignment='right',
                 verticalalignment='baseline',
                 transform=ax.transAxes)

        plt.text(0.95, 0.15, fr'$n_{{nodos}}={self.number_of_nodes}$',
                 horizontalalignment='right',
                 verticalalignment='baseline',
                 transform=ax.transAxes)

        plt.legend(loc='best', frameon=False)
        plt.tight_layout()
        plt.savefig('report/images/erdos_renyi_degree_distribution.png')
        plt.clf()
