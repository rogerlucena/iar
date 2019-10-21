from deap import *

import matplotlib.pyplot as plt
#from mpl_toolkits.mplot3d import Axes3D  # noqa: F401 unused import
import numpy as np
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import random
from scipy.optimize import minimize

from plot import *

import array
import random

import numpy

from deap import algorithms
from deap import base
from deap import benchmarks
from deap import creator
from deap import tools

IND_SIZE = 5
MIN_VALUE = -30
MAX_VALUE = 30
MIN_STRATEGY = 0.5
MAX_STRATEGY = 3


## A completer: creator et toolbox de DEAP ##


def launch_nsga2(mu=100, lambda_=200, cxpb=0.6, mutpb=0.3, ngen=1000, display=False, verbose=False):

    random.seed()

    population = toolbox.population(n=mu)
    paretofront = tools.ParetoFront()
    stats = tools.Statistics(lambda ind: ind.fitness.values)
    stats.register("avg", numpy.mean)
    stats.register("std", numpy.std)
    stats.register("min", numpy.min)
    stats.register("max", numpy.max)
    
    logbook = tools.Logbook()
    logbook.header = ['gen', 'nevals'] + (stats.fields if stats else [])

    ## A completer: évaluation des individus et mise à jour de leur fitness


    if paretofront is not None:
        paretofront.update(population)

    print("Pareto Front: "+str(paretofront))

    record = stats.compile(population) if stats is not None else {}
    logbook.record(gen=0, nevals=len(invalid_ind), **record)
    if verbose:
        print(logbook.stream)

    # Begin the generational process
    for gen in range(1, ngen + 1):


        ## A completer, génération des 'offspring' et sélection de la nouvelle population


        # Update the hall of fame with the generated individuals
        if paretofront is not None:
            paretofront.update(offspring)


        if display:
            plot_pareto_front(population, toolbox, "Gen: %d"%(gen))

        # Update the statistics with the new population
        record = stats.compile(population) if stats is not None else {}
        logbook.record(gen=gen, nevals=len(invalid_ind), **record)
        if verbose:
            print(logbook.stream)

    return population, logbook, paretofront


    
if __name__ == '__main__':
    population,logbook,paretofront = launch_nsga2(display=True)


