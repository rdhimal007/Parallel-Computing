import pandas as pd

import matplotlib.pyplot as plt
# Load data
strong_df = pd.read_csv('strong_Scaling.csv')
weak_df = pd.read_csv('weak_Scaling.csv')

# Plotting
plt.figure(figsize=(10, 5))

# Strong Scaling
plt.subplot(1, 2, 1)
plt.plot(strong_df['Threads'], strong_df['Time'], marker='o', label='Strong Scaling')
plt.xlabel('Number of Threads')
plt.ylabel('Execution Time (s)')
plt.title('Strong Scaling Analysis')
plt.grid(True)
plt.legend()

# Weak Scaling
plt.subplot(1, 2, 2)
plt.plot(weak_df['Threads'], weak_df['Time'], marker='o', color='r', label='Weak Scaling')
plt.xlabel('Number of Threads')
plt.ylabel('Execution Time (s)')
plt.title('Weak Scaling Analysis')
plt.grid(True)
plt.legend()

plt.tight_layout()
plt.savefig('openmp02-scaling.png')
plt.show()
