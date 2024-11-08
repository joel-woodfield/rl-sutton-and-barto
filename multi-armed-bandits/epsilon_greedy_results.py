import sys

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

if len(sys.argv) != 3:
    raise ValueError("Requires 2 arguments")
input_file = sys.argv[1]
output_file = sys.argv[2]

data = pd.read_csv(input_file).values
avg_rewards = np.mean(data, axis=0)
plt.plot(avg_rewards)
plt.xlabel("Timestep")
plt.ylabel("Average Reward")
plt.savefig(output_file)
