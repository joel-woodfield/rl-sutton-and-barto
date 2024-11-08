import sys

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

num_experiments = int(sys.argv[1])
output_file = sys.argv[2]

for i in range(num_experiments):
    input_file = sys.argv[i * 2 + 3]
    label = sys.argv[i * 2 + 4]

    data = pd.read_csv(input_file).values
    avg_rewards = np.mean(data, axis=0)
    plt.plot(avg_rewards, label=label)

plt.xlabel("Timestep")
plt.ylabel("Average Reward")
plt.legend()
plt.savefig(output_file)
