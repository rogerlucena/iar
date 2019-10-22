import numpy as np
import matplotlib.pyplot as plt

with open('log/1571393509.897512-TrialDurations-randomPersist.txt') as fh:
    random_data = np.loadtxt(fh)

print("Random Median", np.median(random_data))
print("Random First Quartile", np.percentile(random_data,25))
print("Random Third Quartile", np.percentile(random_data,75))
print("-----------------------------------------------------------")

# with open('log/1571391607.3999226-TrialDurations-qlearning.txt') as fh:
# with open('log/1571394857.449889-TrialDurations-qlearning.txt') as fh:
with open('log/1571395670.4905314-TrialDurations-qlearning.txt') as fh:
    qlearning_data = np.loadtxt(fh)

fig = plt.figure()
plt.bar(range(len(qlearning_data)), qlearning_data)
plt.ylabel("Time (s)")
plt.xlabel("Trial number")
fig.savefig('qlearning.png', dpi=fig.dpi)

print("Q-learning Median", np.median(qlearning_data))
print("Q-learning First Quartile", np.percentile(qlearning_data,25))
print("Q-learning Third Quartile", np.percentile(qlearning_data,75))
print("-----------------------------------------------------------")
print("Q-learning Median First 10", np.median(qlearning_data[0:10]))
print("Q-learning First Quartile First 10", np.percentile(qlearning_data[0:10],25))
print("Q-learning Third Quartile First 10", np.percentile(qlearning_data[0:10],75))
print("-----------------------------------------------------------")
print("Q-learning Median Last 10", np.median(qlearning_data[-10::]))
print("Q-learning First Quartile Last 10", np.percentile(qlearning_data[-10::],25))
print("Q-learning Third Quartile Last 10", np.percentile(qlearning_data[-10::],75))