"""
  plot.py
  Data Structures and Algorithms Lab - CS293
  Author: P Balasubramanian
  Rollno: 200050103
"""  
import matplotlib.pyplot as plt
import math
import numpy as np

lines = []
with open('info.txt') as f:
    lines = f.readlines()

# x axis values
N_values = []
# corresponding y axis values
time_taken = []
swaps = []

# x axis values
N5_values = []
# corresponding y axis values
N5_time_taken = []
N5_swaps = []

# x axis values
N2_values = []
# corresponding y axis values
N2_time_taken = []
N2_swaps = []

for line in lines:
    x = int(line.split(",")[0])
    N_values.append(x)
    tim = int(line.split(",")[1])
    time_taken.append(tim)
    swap = int(line.split(",")[2])
    swaps.append(swap)

    x = int(line.split(",")[3])
    N2_values.append(x)
    tim = int(line.split(",")[4])
    N2_time_taken.append(tim)
    swap = int(line.split(",")[5])
    N2_swaps.append(swap)

    x = int(line.split(",")[6])
    N5_values.append(x)
    tim = int(line.split(",")[7])
    N5_time_taken.append(tim)
    swap = int(line.split(",")[8])
    N5_swaps.append(swap)
  
x = np.arange(len(N_values))

# insertion time_graph
plt.bar(x, time_taken,label = "Actual insertion time", color ='blue',width = 0.4)
plt.xticks(x, N_values)
plt.xlabel('N')
plt.ylabel('time_taken')
plt.title('N vs Time_taken')
plt.legend()
plt.savefig('insert_time.png')
plt.show()

#insertion swaps_graph
plt.bar(x, swaps,label = "swaps", color ='green')
plt.xticks(x, N_values)
plt.xlabel('N')
plt.ylabel('#of swaps')
plt.title('N_values vs Swaps')
plt.legend()
plt.savefig('insert_swaps.png')
plt.show()

# rand op time_graph
plt.plot(N5_values, N5_time_taken,label = "Actual time")
plt.xlabel('N/5')
plt.ylabel('time_taken')
plt.title('N/5 vs Time_taken')
plt.legend()
plt.savefig('rand_op_insert_time.png')
plt.show()

#rand op insertion swaps_graph
plt.plot(N_values, swaps,label = "swaps")
plt.xlabel('N/5')
plt.ylabel('#of swaps')
plt.title('N/5 vs Swaps')
plt.legend()
plt.savefig('rand_op_insert_swaps.png')
plt.show()

width = 0.2

# time_comp_graph
plt.bar(x, time_taken, width,label = "Actual insertion time", color ='blue')
plt.bar(x+0.2, N2_time_taken, width,label = "Actual deletion time", color ='red')
plt.xticks(x, N_values)
plt.xlabel('N')
plt.ylabel('time_taken')
plt.title('Time_taken: Insertion vs Deletion')
plt.legend()
plt.savefig('time_comp_graph.png')
plt.show()

# swaps_comp_graph
plt.bar(x, swaps, width,label = "insertion swaps", color ='blue')
plt.bar(x+0.2, N2_swaps, width,label = "deletion swaps", color ='red')
plt.xticks(x, N_values)
plt.xlabel('N')
plt.ylabel('swaps')
plt.title('Swaps: Insertion vs Deletion')
plt.legend()
plt.savefig('swaps_comp_graph.png')
plt.show()