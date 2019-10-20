import time

from utils.format_simulation_time import format_simulation_time
from visualizations.erdos_renyi_and_watts_strogatz_degree_distributions import \
    ErdosRenyiAndWattsStrogatzDegreeDistributions
from visualizations.erdos_renyi_average_path_length import ErdosRenyiAveragePathLength
from visualizations.erdos_renyi_degree_binomial_and_poisson_distributions import \
    ErdosRenyiDegreeBinomialAndPoissonDistributions
from visualizations.watts_strogatz_clustering_coefficient_and_average_path_length import \
    WattsStrogatzClusteringCoefficientAndAveragePathLength

start = time.time()

# ErdosRenyiAveragePathLength()
# ErdosRenyiDegreeBinomialAndPoissonDistributions()
# ErdosRenyiAndWattsStrogatzDegreeDistributions()
WattsStrogatzClusteringCoefficientAndAveragePathLength()

end = time.time()
simulation_time = end - start

print(format_simulation_time(simulation_time))
