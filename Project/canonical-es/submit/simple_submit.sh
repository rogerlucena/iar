#!/bin/bash
N_CPUS=6
EPISODES_PER_CPU=2
GAME="Pong"
RUN=1
CONFIG="configurations/canonical-es.json"

mpirun -np $N_CPUS --bind-to core --map-by node -report-bindings python main.py -e $EPISODES_PER_CPU -g $GAME -c $CONFIG -r $RUN