"""
  plot_csv.py
  Data Structures and Algorithms Lab - CS293
  Author: P Balasubramanian
  Rollno: 200050103
"""  
import matplotlib.pyplot as plt
import math
import csv
  
# csv file name
filename = "BST_insertion_time.csv"
  
# initializing the rows list
rows = []
  
# reading csv file
with open(filename, 'r') as csvfile:
    # creating a csv reader object
    csvreader = csv.reader(csvfile)
      
    # extracting field names through first row
    rows.append(next(csvreader))
  
    # extracting each data row one by one
    for row in csvreader:
        rows.append(row)
  
    # get total number of rows
    print("Total no. of rows: %d"%(csvreader.line_num))
k=0.125
# x axis values
no_insertions = []
# corresponding y axis values
time_taken = []

# x axis values
nlogn_no_insertions = []
# corresponding y axis values
nlogn_time_taken = []

for row in rows:
    x = int(row[0])
    y = row[1]
    if 'e' in y:
        y = int(float(y.split('e+')[0])*pow(10,int(y.split('e+')[1])))
    else:
        y = int(float(row[1]))
    no_insertions.append(x)
    time_taken.append(int(y))
    x2 = k*x*math.log(x) if x>0 else 0
    nlogn_no_insertions.append(x)
    nlogn_time_taken.append(x2)
  
# plotting the points 
plt.plot(no_insertions, time_taken,label = "Actual insertion time")

# plotting the points 
plt.plot(nlogn_no_insertions, nlogn_time_taken,label = "k*nlogn")

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