import cma
import gym
import numpy as np
from fixed_structure_nn_numpy import SimpleNeuralControllerNumpy

env = gym.make('CartPole-v1')

def eval_nn(genotype, render=False):
    total_reward=0
    nn=SimpleNeuralControllerNumpy(4,1,2,5)
    nn.set_parameters(genotype)
    observation = env.reset()
        for t in range(1000):
            if render:
                env.render()
            action=nn.predict(observation)
            if action>0:
                action=1
            else:
                action=0
            observation, reward, done, info = env.step(action) 
            total_reward+=reward
            if done:
                print("Episode finished after %d timesteps"%(t+1))
                break        
    return total_reward

### A completer pour optimiser les parametres du reseau de neurones avec CMA-ES ###

env.close()
