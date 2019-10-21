import cma
import gym, gym_fastsim
from deap import *
import numpy as np
from fixed_structure_nn_numpy import SimpleNeuralControllerNumpy
from scipy.spatial import KDTree

from deap import algorithms
from deap import base
from deap import benchmarks
from deap import creator
from deap import tools

import array
import random
import operator
import math

from plot import *

from scoop import futures

from novelty_search import *


def eval_nn(genotype, nbstep=2000, dump=False, render=False, name=""):
    nn=SimpleNeuralControllerNumpy(5,2,2,10)
    nn.set_parameters(genotype)
    observation = env.reset()
    old_pos=None
    total_dist=0
    if (dump):
        f=open("traj"+name+".log","w")
    for t in range(nbstep):
        if render:
            env.render()
        action=nn.predict(observation)
        observation, reward, done, info = env.step(action) 
        pos=info["robot_pos"][:2]
        if(dump):
            f.write(" ".join(map(str,pos))+"\n")
        if (old_pos is not None):
            d=math.sqrt((pos[0]-old_pos[0])**2+(pos[1]-old_pos[1])**2)
            total_dist+=d
        old_pos=list(pos)
        if(done):
            break
    if (dump):
        f.close()
    dist_obj=info["dist_obj"]
    #print("End of eval, total_dist=%f"%(total_dist))
    return ## A completer: une evaluation devra renvoyer la fitness utilisée, mais aussi le descripteur comportemental résultant de cette évaluation

nn=SimpleNeuralControllerNumpy(5,2,2,10)
center=nn.get_parameters()

## Il vous est recommandé de gérer les différentes variantes avec cette variable. Les 3 valeurs possibles seront:
## "FIT+NS": expérience multiobjectif avec la fitness et la nouveauté (NSGA-2)
## "NS": nouveauté seule
## "FIT": fitness seule
## pour les variantes avec un seul objectif, vous pourrez, au choix, utiliser CMA-ES ou NSGA-2 avec un seul objectif,
## il vous est cependant recommandé d'utiliser NSGA-2 car cela limitera la différence entre les variantes et cela 
##vvous fera gagner du temps pour la suite.
variant="FIT+NS"

# votre code contiendra donc des tests comme suit pour gérer la différence entre ces variantes:
if (variant=="FIT+NS"):
    pass ## A remplacer par les instructions appropriées
elif (variant=="FIT"):
    pass ## A remplacer par les instructions appropriées
elif (variant=="NS"):
    pass ## A remplacer par les instructions appropriées
else:
    print("Variante inconnue: "+variant)


def launch_nsga2(mu=100, lambda_=200, cxpb=0.6, mutpb=0.3, ngen=1000, verbose=False):

    random.seed()

    population = toolbox.population(n=mu)
    paretofront = tools.ParetoFront()
    
    fbd=open("bd.log","w")

    # Evaluate the individuals with an invalid fitness
    invalid_ind = [ind for ind in population if not ind.fitness.valid]
    fitnesses_bds = toolbox.map(toolbox.evaluate, invalid_ind)
    for ind, (fit, bd) in zip(invalid_ind, fitnesses_bds):
        #print("Fit: "+str(fit)) 
        #print("BD: "+str(bd))
        ind.fit = fit
        ind.bd = bd
        
        ## A compléter: initialiser ind.fitness.values de façon appropriée, selon la variante  
        
        fbd.write(" ".join(map(str,bd))+"\n")
        fbd.flush()

    if paretofront is not None:
        paretofront.update(population)

    #print("Pareto Front: "+str(paretofront))

    k=15
    add_strategy="random"
    lambdaNov=6

    ## A completer: mettre a jour l'archive et le calcul de nouveauté (qui sera dans ind.novelty)

    for ind in population:
        pass ## A completer pour mettre le critère de nouveauté, si besoin, dans la valeur appropriée de la fitness 

        #print("Fit=%f Nov=%f"%(ind.fit, ind.novelty))

    # On garde trace de l'individu le plus proche de la sortie
    indexmin, valuemin = min(enumerate([i.fit for i in population]), key=operator.itemgetter(1))


    # Begin the generational process
    for gen in range(1, ngen + 1):
        if (gen%10==0):
            print("+",end="", flush=True)
        else:
            print(".",end="", flush=True)


        ## A completer: générer les 'offspring' et les évaluer

        pq=population+offspring

        ## A completer: mettre à jour l'archive et calculer les nouveautés

        for ind in pq:
            pass ## A completer pour mettre le critère de nouveauté, si besoin, dans la valeur appropriée de la fitness 

        

        # Select the next generation population
        population[:] = toolbox.select(pq, mu)

        # Update the hall of fame with the generated individuals
        if paretofront is not None:
            paretofront.update(population)

        indexmin, newvaluemin = min(enumerate([i.fit for i in pq]), key=operator.itemgetter(1))

        if (newvaluemin<valuemin):
            valuemin=newvaluemin
            print("Gen "+str(gen)+", new min ! min fit="+str(valuemin)+" index="+str(indexmin))
            eval_nn(pq[indexmin],True,"_gen%04d"%(gen))
    fbd.close()
    return population, None, paretofront

env = gym.make('FastsimSimpleNavigation-v0')

if (__name__ == "__main__"):

    pop, logbook, paretofront= launch_nsga2(ngen=200)

    
    #plot_pareto_front(paretofront, "Final pareto front")

    # evaluation finale des individus sur le front de pareto final (pour sauver les trajectoires associées)
    for i,p in enumerate(paretofront):
        print("Visualizing indiv "+str(i)+", fit="+str(p.fitness.values))
        eval_nn(p,True,"_last_pareto_front_ind_%d"%(i)))

    env.close()
