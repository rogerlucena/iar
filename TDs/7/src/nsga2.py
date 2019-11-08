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

# IND_SIZE = 5
# MIN_VALUE = -30
# MAX_VALUE = 30
# MIN_STRATEGY = 0.5
# MAX_STRATEGY = 3

# ## A completer: creator et toolbox de DEAP ##
# creator.create("FitnessMin", base.Fitness, weights=(-1.0, ))

# creator.create("Individual",
#                array.array,
#                typecode="d",
#                fitness=creator.FitnessMin,
#                strategy=None)
# creator.create("Strategy", array.array, typecode="d")

# def generateES(icls, scls, size, imin, imax, smin, smax):
#     ind = icls(random.uniform(imin, imax) for _ in range(size))
#     ind.strategy = scls(random.uniform(smin, smax) for _ in range(size))
#     return ind

# toolbox = base.Toolbox()
# toolbox.register("individual", generateES, creator.Individual,
#                  creator.Strategy, IND_SIZE, MIN_VALUE, MAX_VALUE,
#                  MIN_STRATEGY, MAX_STRATEGY)
# toolbox.register("population", tools.initRepeat, list, toolbox.individual)
# toolbox.register("mate", tools.cxESBlend, alpha=0.1)
# toolbox.register("mutate", tools.mutESLogNormal, c=1.0, indpb=0.03)
# toolbox.register("select", tools.selNSGA2, tournsize=3)
# toolbox.register("evaluate", benchmarks.zdt1)

## Copied
creator.create("FitnessMin", base.Fitness, weights=(-1.0, -1.0))
creator.create("Individual",
               array.array,
               typecode='d',
               fitness=creator.FitnessMin)

toolbox = base.Toolbox()

BOUND_LOW, BOUND_UP = 0.0, 1.0

# Functions zdt4 has bounds x1 = [0, 1], xn = [-5, 5], with n = 2, ..., 10
# BOUND_LOW, BOUND_UP = [0.0] + [-5.0]*9, [1.0] + [5.0]*9

# Functions zdt1, zdt2, zdt3 have 30 dimensions, zdt4 and zdt6 have 10
NDIM = 30


def uniform(low, up, size=None):
    try:
        return [random.uniform(a, b) for a, b in zip(low, up)]
    except TypeError:
        return [
            random.uniform(a, b) for a, b in zip([low] * size, [up] * size)
        ]


toolbox.register("attr_float", uniform, BOUND_LOW, BOUND_UP, NDIM)
toolbox.register("individual", tools.initIterate, creator.Individual,
                 toolbox.attr_float)
toolbox.register("population", tools.initRepeat, list, toolbox.individual)

toolbox.register("evaluate", benchmarks.zdt1)
toolbox.register("mate",
                 tools.cxSimulatedBinaryBounded,
                 low=BOUND_LOW,
                 up=BOUND_UP,
                 eta=20.0)
toolbox.register("mutate",
                 tools.mutPolynomialBounded,
                 low=BOUND_LOW,
                 up=BOUND_UP,
                 eta=20.0,
                 indpb=1.0 / NDIM)
toolbox.register("select", tools.selNSGA2)


def launch_nsga2(mu=100,
                 lambda_=200,
                 cxpb=0.6,
                 mutpb=0.3,
                 ngen=300,
                 display=False,
                 verbose=False):

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

    invalid_ind = [ind for ind in population if not ind.fitness.valid]
    fitnesses = toolbox.map(toolbox.evaluate, invalid_ind)
    for ind, fit in zip(invalid_ind, fitnesses):
        ind.fitness.values = fit

    population = toolbox.select(population, len(population))

    if paretofront is not None:
        paretofront.update(population)

    print("Pareto Front: " + str(paretofront))

    record = stats.compile(population) if stats is not None else {}
    logbook.record(gen=0, nevals=len(invalid_ind), **record)
    if verbose:
        print(logbook.stream)

    # Begin the generational process
    for gen in range(1, ngen + 1):

        ## A completer, génération des 'offspring' et sélection de la nouvelle population
        offspring = tools.selTournamentDCD(population, len(population))
        offspring = [toolbox.clone(ind) for ind in offspring]

        for ind1, ind2 in zip(offspring[::2], offspring[1::2]):
            if random.random() <= cxpb:
                toolbox.mate(ind1, ind2)

        for mutant in offspring:
            if random.random() < mutpb:
                toolbox.mutate(mutant)
                del mutant.fitness.values

        # Evaluate the individuals with an invalid fitness
        invalid_ind = [ind for ind in offspring if not ind.fitness.valid]
        fitnesses = toolbox.map(toolbox.evaluate, invalid_ind)
        for ind, fit in zip(invalid_ind, fitnesses):
            ind.fitness.values = fit

        # Select the next generation population
        population = toolbox.select(population + offspring, mu)

        # Update the hall of fame with the generated individuals
        if paretofront is not None:
            paretofront.update(offspring)

        if display:
            if gen % 50 == 0 or gen == 1:
                plot_pop_pareto_front(population, paretofront,
                                      "Gen: %d" % (gen))

        # Update the statistics with the new population
        record = stats.compile(population) if stats is not None else {}
        logbook.record(gen=gen, nevals=len(invalid_ind), **record)
        if verbose:
            print(logbook.stream)

    return population, logbook, paretofront


if __name__ == '__main__':
    population, logbook, paretofront = launch_nsga2(display=True)
