#!/usr/bin/env python

from radarGuidance import *
from wallFollower import *

import random #used for the random choice of a strategy
import sys
import numpy as np
import math

import json
#--------------------------------------
# Position of the goal:
goalx = 300
goaly = 450
# Initial position of the robot:
initx = 300
inity = 35
# strategy choice related stuff:
choice = -1
choice_tm1 = -1
tLastChoice = 0
rew = 0

i2name=['wallFollower','radarGuidance']

# Parameters of State building:
# threshold for wall consideration
th_neglectedWall = 35
# threshold to consider that we are too close to a wall
# and a punishment should be delivered
th_obstacleTooClose = 13
# angular limits used to define states
angleLMin = 0
angleLMax = 55

angleFMin=56
angleFMax=143

angleRMin=144
angleRMax=199

# Q-learning related stuff:
# definition of states at time t and t+1
S_t = ''
S_tm1 = ''

file_name = time.time()
# Q-learning constants
alpha=0.4
beta=4.0
gamma=0.95
try:
  with open('Q_table.json', 'r') as json_file:
    Q = json.load(json_file)
    print("Loaded Q_Table")
    time.sleep(3)
except:
  Q = {}
  for a1 in range(2):
    for a2 in range(2):
      for a3 in range(2):
        for a4 in range(8):
          for a5 in range(3):
            Q[str(a1)+str(a2)+str(a3)+str(a4)+str(a5)] = [0, 0]
  print("New Q_table")
  time.sleep(3)

# Time
last_time = 0

def soft_max(x):
  x = beta * np.array(x)
  e_x = np.exp(x - np.max(x))
  return e_x / e_x.sum()

def choose_from_distribution(x):
  return np.random.choice(np.arange(0,len(x)), p=x)
  

def update_Q():
  global Q
  global rew
  global S_tm1
  global S_t
  global choice_tm1
  try:
    delta = rew + gamma * max(Q[S_t]) - Q[S_tm1][choice_tm1]
    Q[S_tm1][choice_tm1] += alpha * delta
  except:
    pass
  with open('Q_table.json', 'w') as json_file:
    json.dump(Q, json_file)

  

#--------------------------------------
# the function that selects which controller (radarGuidance or wallFollower) to use
# sets the global variable "choice" to 0 (wallFollower) or 1 (radarGuidance)
# * arbitrationMethod: how to select? 'random','randPersist','qlearning'
def strategyGating(arbitrationMethod,verbose=True):
  global choice
  global choice_tm1
  global tLastChoice
  global rew
  global last_time
  global S_t
  global S_tm1

  choice_tm1 = choice
  # The chosen gating strategy is to be coded here:
  #------------------------------------------------
  if arbitrationMethod=='random':
    choice = random.randrange(2)
  #------------------------------------------------
  elif arbitrationMethod=='randomPersist':
    now = time.time()
    try:
      if (now - last_time) > 2:
        last_time = now
        choice = random.randrange(2)
    except:
      last_time = now
      choice = random.randrange(2)
  #------------------------------------------------
  elif arbitrationMethod=='qlearning':
    now = time.time()
    if rew != 0 or S_tm1 != S_t or (now-last_time) > 2:
      # print("New choice")
      last_time = now
      choice = choose_from_distribution(soft_max(Q[S_t]))
    if rew != 0 or S_tm1 != S_t or choice_tm1 != choice:
      # print("Update Q")
      update_Q()

    
    # print('Q-Learning selection : to be implemented')
  #------------------------------------------------
  else:
    print(arbitrationMethod+' unknown.')
    exit()

  if verbose:
    print("strategyGating: Active Module: "+i2name[choice])

#--------------------------------------
def buildStateFromSensors(laserRanges,radar,dist2goal):
  S   = ''
  # determine if obstacle on the left:
  wall='0'
  if min(laserRanges[angleLMin:angleLMax]) < th_neglectedWall:
    wall ='1'
  S += wall
  # determine if obstacle in front:
  wall='0'
  if min(laserRanges[angleFMin:angleFMax]) < th_neglectedWall:
    wall ='1'
    #print("Mur Devant")
  S += wall
  # determine if obstacle on the right:
  wall='0'
  if min(laserRanges[angleRMin:angleRMax]) < th_neglectedWall:
    wall ='1'
  S += wall

  S += str(radar)

  if dist2goal < 125:
    S+='0'
  elif dist2goal < 250:
    S+='1'
  else:
    S+='2'
  #print('buildStateFromSensors: State: '+S)

  return S

#--------------------------------------
def main():
  global S_t
  global S_tm1
  global rew

  settings = Settings('worlds/entonnoir.xml')

  env_map = settings.map()
  robot = settings.robot()

  d = Display(env_map, robot)

  method = 'qlearning'
  # experiment related stuff
  startT = time.time()
  trial = 0
  nbTrials = 100
  trialDuration = np.zeros((nbTrials))

  i = 0
  while trial<nbTrials:
    # update the display
    #-------------------------------------
    d.update()
    # get position data from the simulation
    #-------------------------------------
    pos = robot.get_pos()
    # print("##########\nStep "+str(i)+" robot pos: x = "+str(int(pos.x()))+" y = "+str(int(pos.y()))+" theta = "+str(int(pos.theta()/math.pi*180.)))

    # has the robot found the reward ?
    #------------------------------------
    dist2goal = math.sqrt((pos.x()-goalx)**2+(pos.y()-goaly)**2)
    # if so, teleport it to initial position, store trial duration, set reward to 1:
    if (dist2goal<20): # 30
      print('***** REWARD REACHED *****')
      pos.set_x(initx)
      pos.set_y(inity)
      robot.set_pos(pos) # format ?
      # and store information about the duration of the finishing trial:
      currT = time.time()
      trialDuration[trial] = currT - startT
      startT = currT
      np.savetxt('log/'+str(file_name)+'-TrialDurations-Partial'+method+'.txt',trialDuration)
      print("Trial "+str(trial)+" duration:"+str(trialDuration[trial]))
      trial +=1
      rew = 1
      update_Q()

    # get the sensor inputs:
    #------------------------------------
    lasers = robot.get_laser_scanners()[0].get_lasers()
    laserRanges = []
    for l in lasers:
      laserRanges.append(l.get_dist())

    radar = robot.get_radars()[0].get_activated_slice()

    bumperL = robot.get_left_bumper()
    bumperR = robot.get_right_bumper()


    # 2) has the robot bumped into a wall ?
    #------------------------------------
    rew = 0
    if bumperR or bumperL or min(laserRanges[angleFMin:angleFMax]) < th_obstacleTooClose:
      rew = -1
      print("***** BING! ***** "+i2name[choice])

    # 3) build the state, that will be used by learning, from the sensory data
    #------------------------------------
    S_tm1 = S_t
    S_t = buildStateFromSensors(laserRanges,radar, dist2goal)

    #------------------------------------
    strategyGating(method,verbose=False)
    if choice==0:
      v = wallFollower(laserRanges,verbose=False)
    else:
      v = radarGuidance(laserRanges,bumperL,bumperR,radar,verbose=False)

    i+=1
    robot.move(v[0], v[1], env_map)
    time.sleep(0.01)

  # When the experiment is over:
  np.savetxt('log/'+str(startT)+'-TrialDurations-'+method+'.txt',trialDuration)

#--------------------------------------

if __name__ == '__main__':
  random.seed()
  main()
