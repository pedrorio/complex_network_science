# -*- coding: utf-8 -*-
"""
Created on Fri Oct  4 13:47:52 2019

@author: Regina Duarte
"""

import networkx as nx
import matplotlib.pyplot as plt
import numpy as np

def degree_distribution(graphs):
    final_degree_count = np.zeros([0])

    for graph in graphs:

        degree_count = np.asarray(nx.degree_histogram(graph))

        final_degree_count_length = len(final_degree_count)
        degree_count_length = len(degree_count)

        length_differential = final_degree_count_length - degree_count_length

        if length_differential > 0:
            degree_count = np.append(degree_count, np.zeros([abs(length_differential)]))
        elif length_differential < 0:
            final_degree_count = np.append(final_degree_count, np.zeros([abs(length_differential)]))

        final_degree_count = np.add(final_degree_count, degree_count)

    final_degree_count = final_degree_count / len(graphs)
    
    probabilities_final_degree_count= final_degree_count / sum(final_degree_count)


    return probabilities_final_degree_count

def clustering_coef_mean(graphs):
    averages=0
    
    for graph in graphs:
        
        clustering_of_all_nodes=nx.clustering(graph)
        averages+=sum(clustering_of_all_nodes.values())/nx.number_of_nodes(graph)
        
    return averages/len(graphs)

def averege_path_lengh(graphs):
    
    for graph in graphs:
        
        average_path_lenght=nx.average_shortest_path_length(graph)
        
    return average_path_lenght/len(graphs)
    

def simulation_erdos(
        number_of_simulations,
        number_of_initial_nodes,
        probability_of_rewiring_each_node
):
    graphs = []

    # generate a graph n times
    for simulation_number in range(number_of_simulations):
        # for number_of_initial_nodes in initial_nodes_numbers:
        # for probability_of_rewiring_each_node in probabilities_of_rewiring_each_node:
        erdos_renyi = nx.erdos_renyi_graph(
            number_of_initial_nodes,
            probability_of_rewiring_each_node,
            
        )

        graphs.append(erdos_renyi)

    # compute the degree distribution for all the graphs
    return (clustering_coef_mean(graphs), averege_path_lengh(graphs),degree_distribution(graphs))

def simulation_wratts(
        number_of_simulations,
        number_of_initial_nodes,
        probability_of_rewiring_each_node,
        k_nearest_neigbhours
):
    graphs = []

    # generate a graph n times
    for simulation_number in range(number_of_simulations):
        # for number_of_initial_nodes in initial_nodes_numbers:
        # for probability_of_rewiring_each_node in probabilities_of_rewiring_each_node:
        watts_strogatz = nx.watts_strogatz_graph(
                number_of_initial_nodes,
                k_nearest_neigbhours, 
                probability_of_rewiring_each_node
                )
    
        graphs.append(watts_strogatz)

    # compute the degree distribution for all the graphs
    return (clustering_coef_mean(graphs), averege_path_lengh(graphs),degree_distribution(graphs))

    
##some graphics
    
### distribuibao binomial/poisson do random graph

number_nodos=[100,1000,5000]
histograma_por_num_nodos=[]
for numero in number_nodos:
    histograma_por_num_nodos.append(simulation_erdos(50, numero, 0.4)[2])

for histograma in histograma_por_num_nodos:
    degrees = [index for index, value in enumerate(histograma)]
    plt.scatter(degrees,histograma)


#### relação entre C e L no wrats and strogatss
#probabilidades crescentes, 50 simulações, 1500 nodos, 4 vizinhos iniciais
C0, L0 = simulation_wratts(1,1500,0,4)[0:1]
p=0.001
probabilidades=[]
Clustering=[]
Path_lengh=[]
while p<1:
    c,l=simulation_wratts(50,1500,p,4)[0:1]
    Clustering.append(c)
    Path_lengh.append(l)
    probabilidades.append(p)
    p+=0.001

plt.scatter(probabilidades,Clustering)
plt.scatter(probabilidades,Path_lengh)

    
    
    
    



        
    
        

