import os
import matplotlib.pyplot as plt
import pandas as pd

x = ["1","5","10","20","30"]
avg_t = [27.8879,27.8149,26.2487,24.3425,23.0315]
avg_min_max = [1,0.7803,0.5043,0.2644,0.1785]
roll_no="200050103"


plt.plot(x, avg_t,color='black')
 
# naming the x axis
plt.xlabel('num stations')
# naming the y axis
plt.ylabel('throughput')
 
# giving a title to my graph
tit = "Avg Throughput    "+roll_no
plt.title(tit)
plt.savefig('throughput_gre.png')
# function to show the plot
plt.show()

plt.plot(x, avg_min_max,color='black')
 
# naming the x axis
plt.xlabel('num stations')
# naming the y axis
plt.ylabel('avg_min_max')

tit = "Avg Min/Max Ratio   "+roll_no
# giving a title to my graph
plt.title(tit)
plt.savefig('avg_min_max_gre.png')
# function to show the plot
plt.show()

    
