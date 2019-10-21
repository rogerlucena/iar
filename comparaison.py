import cma
from deap import benchmarks
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D  # noqa: F401 unused import
import numpy as np
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import random
from scipy.optimize import minimize

from plot import *
from cmaes import *
from es import *

center=[10]*16
sigma=5
nbrun=20

def ackley(x):
    return benchmarks.ackley(x)[0]

ma_func=ackley

def generate_res():
    ################## Baselines ####################

    # Pour que les comparaisons soient équitables, il faut que les points de départ des optimisation "classiques" soient similaires 
    pop=[[random.gauss(c,sigma) for c in center] for i in range(nbrun)]
    nelder = [minimize(ma_func, x0, method='nelder-mead',options={'xtol': 1e-8, 'disp': False}) for x0 in pop]
    powel = [minimize(ma_func, x0, method='powell',options={'xtol': 1e-8, 'disp': False}) for x0 in pop]

    res_nelder=[x.fun for x in nelder]
    res_powel=[x.fun for x in powel]

    ################## ES ####################
    
    res_es=[]
    for i in range(nbrun):
        ## Mettre ici le code pour faire appel à votre code ES et mettre le résultat dans une variable res
        res_es.append(res)

    ################## CMA-ES ####################

    res_cmaes=[]
    for i in range(nbrun):
        ## Mettre ici le code pour faire appel à votre code CMAES et mettre le résultat dans une variable res
        res_cmaes.append(res)

    res_cmaes_pure=[]
    for i in range(nbrun):
        ## Mettre ici le code pour faire appel à votre code CMAES "pure" et mettre le résultat dans une variable res
        res_cmaes_pure.append(res)


    res={"CMA-ES": res_cmaes,
         "CMA-ES pure": res_cmaes_pure,
         "ES": res_es,
         "Nelder": res_nelder,
         "Powel": res_powel}

    return res

