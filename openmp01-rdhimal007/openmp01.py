import pandas as pd
import matplotlib.pyplot as plt

# Read the data into a pandas DataFrame
df = pd.read_csv('openmp01_Time.dat', skipinitialspace=True)
grouped_df = df.groupby('Threads')['Time'].mean().reset_index()

# Plotting
plt.figure(figsize=(10, 6))
plt.plot(grouped_df['Threads'], grouped_df['Time'], marker='o', linestyle='-', color='b')
plt.title('Execution Time vs. Number of Threads')
plt.xlabel('Number of Threads')
plt.ylabel('Execution Time (seconds)')
plt.xticks(grouped_df['Threads'])  
plt.grid(True)
plt.savefig('openmp01.png')

plt.show()