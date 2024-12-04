import pandas as pd
import matplotlib.pyplot as plt

# Read the data into a pandas DataFrame
df = pd.read_csv("threads.dat")

# Group by 'Threads' and 'systemIndetifier' and calculate the mean time
grouped = df.groupby(['Threads', 'systemIndetifier'])['Time'].mean().reset_index()

# Separate data for each system
system1_data = grouped[grouped['systemIndetifier'] == 1]
system2_data = grouped[grouped['systemIndetifier'] == 2]
system3_data = grouped[grouped['systemIndetifier'] == 3]

# Plot the graph
plt.figure(figsize=(10, 6))

# Plot average time for each system
plt.plot(system1_data['Threads'], system1_data['Time'], marker='o', linestyle='-', label='Avg: Local Machine')
plt.plot(system2_data['Threads'], system2_data['Time'], marker='o', linestyle='-', label='Avg: HPC')
plt.plot(system3_data['Threads'], system3_data['Time'], marker='o', linestyle='-', label='Avg: UIC Acer')

# Plot average time as solid line
plt.plot(system1_data['Threads'], system1_data['Time'], linestyle='-', color='gray', alpha=0.5)
plt.plot(system2_data['Threads'], system2_data['Time'], linestyle='-', color='gray', alpha=0.5)
plt.plot(system3_data['Threads'], system3_data['Time'], linestyle='-', color='gray', alpha=0.5)

# Plot execution time for each system as dots
plt.scatter(df[df['systemIndetifier'] == 1]['Threads'], df[df['systemIndetifier'] == 1]['Time'], color='blue', marker='o', label='Execution Time(Local Machine)')
plt.scatter(df[df['systemIndetifier'] == 2]['Threads'], df[df['systemIndetifier'] == 2]['Time'], color='orange', marker='o', label='Execution Time (HPC)')
plt.scatter(df[df['systemIndetifier'] == 3]['Threads'], df[df['systemIndetifier'] == 3]['Time'], color='green', marker='o', label='Execution Time (UIC Acer)')

# Add labels and title
plt.xlabel('Thread count')
plt.ylabel('Time (Seconds)')
plt.title('Execution Time vs Thread Count')
plt.legend()

# Show the plot
plt.grid(True)
plt.savefig('threads-graph.png')

plt.show()

