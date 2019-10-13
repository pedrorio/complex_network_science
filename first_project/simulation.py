# -*- coding: utf-8 -*-
"""
Created on Fri Oct  4 13:47:52 2019

@author: Regina Duarte
@author: Pedro Rio
"""

import matplotlib.pyplot as plt

import timeit

from erdos_renyi import ErdosRenyi
from model import Model
from watts_strogatz import WattsStrogatz

start = timeit.timeit()
print("started time it")

# Binomial and poisson distributions in the erdos renyi model
number_of_nodes = [100, 1000]
histogram_per_number_of_nodes = []
for number in number_of_nodes:
    print(number)
    graphs = ErdosRenyi(30, number, 0.4).graphs
    degree_distribution = Model(graphs).degree_distribution()
    histogram_per_number_of_nodes.append(degree_distribution)
    print(number)
    print('\n')

for histogram in histogram_per_number_of_nodes:
    degrees = list(index for index, value in enumerate(histogram))
    plt.scatter(degrees, histogram)

plt.savefig('images/binomial_and_poisson_in_erdos_renyi.png')
plt.clf()

# Average path length in the erdos renyi model
number_of_nodes = [50, 100, 200, 500, 1000]
average_path_lengths = []
for number in number_of_nodes:
    print(number)
    graphs = ErdosRenyi(30, number, 0.4).graphs
    average_path_length = Model(graphs).average_path_length()
    average_path_lengths.append(average_path_length)
    print(number)
    print('\n')

plt.scatter(number_of_nodes, average_path_lengths)

plt.savefig('images/average_path_length_in_erdos_renyi.png')
plt.clf()

# Random vs Wattz Distributions
number_of_simulations = 100
probabilities = [0, 0.0001, 0.001, 0.01, 0.1, 0.3, 0.5, 0.75, 0.9, 1.0]

for probability in probabilities:
    print(probability)
    graphs = WattsStrogatz(number_of_simulations, 1000, probability, 4).graphs
    watts_histogram = Model(graphs).degree_distribution()
    watts_degrees = list((index for index, value in enumerate(watts_histogram)))
    plt.scatter(watts_degrees, watts_histogram)

    graphs = ErdosRenyi(number_of_simulations, 1000, probability).graphs
    erdos_histogram = Model(graphs).degree_distribution()
    erdos_degrees = list((index for index, value in enumerate(erdos_histogram)))
    plt.scatter(erdos_degrees, erdos_histogram)
    print(probability)
    print('\n')

plt.savefig('images/random_vs_watts_degree_distributions.png')

# Clustering and average path length in the watts and strogatz model
p = 0.00
probabilities = []
average_clustering_coefficients = []
average_path_length = []

while p < 1:
    print(p)
    graphs = WattsStrogatz(50, 1500, p, 4).graphs
    c = Model(graphs).clustering_coefficient_mean()
    l = Model(graphs).average_path_length()

    average_clustering_coefficients.append(c)
    average_path_length.append(l)
    probabilities.append(p)
    print(p)
    print('\n')

    p += 0.1

plt.scatter(probabilities, average_clustering_coefficients)
plt.scatter(probabilities, average_path_length)
plt.savefig('images/randomness_and_clustering_in_watts_strogatz.png')
plt.clf()


end = timeit.timeit()
print("ended time it")
print(-(end - start))
