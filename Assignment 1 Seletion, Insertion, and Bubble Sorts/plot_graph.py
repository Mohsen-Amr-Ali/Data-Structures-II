import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df = pd.read_csv('sorting_data.csv')

bubble = df[df['Algorithm'] == 'BubbleSort']
selection = df[df['Algorithm'] == 'SelectionSort']
insertion = df[df['Algorithm'] == 'InsertionSort']

plt.figure(figsize=(10, 6))

plt.plot( bubble['Size'], bubble['Time'],
          label='Bubble Sort',
          color='blue',
          marker='o',
          linestyle='-',
          linewidth='2')

plt.plot( selection['Size'], selection['Time'],
          label='Selection Sort',
          color='red',
          marker='s',
          linestyle='-',
          linewidth='2')

plt.plot( insertion['Size'], insertion['Time'],
          label='Insertion Sort',
          color='green',
          marker='^',
          linestyle='-',
          linewidth='2')

n_values = bubble['Size']
theoretical_values = [0.002 * (n**2) for n in n_values]

plt.plot( n_values, theoretical_values,
          label='Theoretical n^2 values',
          color='black',
          linestyle='--',
          linewidth='1',
          alpha=0.6)

plt.title('Sorting Algorithm Benchmark: Time vs Input Size')
plt.xlabel('Input Size (N)')
plt.ylabel('Execution Time (Microseconds)')

plt.legend()
plt.grid(True)

plt.show()