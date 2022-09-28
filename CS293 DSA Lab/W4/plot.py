"""
  plot.py
  Data Structures and Algorithms Lab - CS293
  Author: P Balasubramanian
  Rollno: 200050103
"""  
import matplotlib.pyplot as plt
import math

lines = []
with open('BST_insertion_time.txt') as f:
    lines = f.readlines()

# x axis values
no_insertions = []
# corresponding y axis values
time_taken = []

# x axis values
nlogn_no_insertions = []
# corresponding y axis values
nlogn_time_taken = []

for line in lines:
    x = int(line.split(",")[0])
    no_insertions.append(x)
    y = line.split(",")[1]
    if 'e' in y:
        y = int(y.split('e')[0])*pow(10,int((y.split('e')[1]).split('\n')[0]))
    time_taken.append(int(y))

    x2 = x*math.log(x) if x>0 else 0
    nlogn_no_insertions.append(x)
    nlogn_time_taken.append(x2)
  
# plotting the points 
plt.plot(no_insertions, time_taken,label = "Actual insertion time")

# plotting the points 
plt.plot(nlogn_no_insertions, nlogn_time_taken,label = "nlogn")

# naming the x axis
plt.xlabel('no_insertions')
# naming the y axis
plt.ylabel('time_taken')  
# giving a title to my graph
plt.title('No_Insertions vs Time_taken')
# show a legend on the plot
plt.legend()
# saving the plot
plt.savefig('runtime.png')
# function to show the plot
plt.show()
