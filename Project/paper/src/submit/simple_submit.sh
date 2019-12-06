#!/bin/bash
EPISODES_PER_CPU=2
GAME="Pong"
RUN=1
CONFIG="configurations/sample_configuration.json"

mpirun -np 4 -report-bindings python main.py -e $EPISODES_PER_CPU -g $GAME -c $CONFIG -r $RUN