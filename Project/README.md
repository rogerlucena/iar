# Final Project

Based on the article `Back to Basics: Benchmarking Canonical Evolution Strategies for Playing Atari` (https://arxiv.org/abs/1802.08842) and its source code.

The project report can be found in `./final-report/report.pdf`. The script used to generate the graphs in the report along with the data they represent are inside the folder `./results`. Finally, the original paper and the summary we made are inside the folder `./paper`.

## Instructions

First, install MPI (Message Passing Interface) and the requirements specified in `./canonical-es/requirements.txt`.

Then, to run Canonical ES the command is:

```bash
./canonical-es/submit/simple_submit.sh
```

To run with different parameters, the file `./canonical-es/submit/simple_submit.sh` can be changed. The `CONFIG` field on this file point to where values such as the learning rate and the population size can also be customized.

The model used (original, without batch normalization and another with a simplified version of the neural network architecture) can be chosen changing this field as well (have a look at `./canonical-es/configurations`). These three architectures are defined inside `./canonical-es/src/models.py`.

## GIT LFS

To clone this repository use git LFS (Large File Storage).
