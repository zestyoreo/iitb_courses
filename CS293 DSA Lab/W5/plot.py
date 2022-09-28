"""
  plot.py
  Data Structures and Algorithms Lab - CS293
  Author: P Balasubramanian
  Rollno: 200050103
"""  
import matplotlib.pyplot as plt
import math
import csv
  
# csv file name
filename1 = "QSP1.csv"
filename2 = "QSPR.csv" 
filename3 = "BS.csv"

# initializing the rows list
rows = []

no_of_elements = []
nlogn = []
n_square = []

# QSP1 
qsp1_rand_array_time_taken = []
qsp1_rand_array_comparisons = []
qsp1_rand_array_swaps = []
qsp1_little_bad_time_taken = []
qsp1_little_bad_comparisons = []
qsp1_little_bad_swaps = []
qsp1_little_good_time_taken = []
qsp1_little_good_comparisons = []
qsp1_little_good_swaps = []

# reading csv file
with open(filename1, 'r') as csvfile:
    # creating a csv reader object
    csvreader = csv.reader(csvfile)
      
    rows.append(next(csvreader))
  
    # extracting each data row one by one
    for row in csvreader:
        rows.append(row)

for row in rows:
    x = int(row[0])
    no_of_elements.append(x)
    y = int(float(row[1]))
    qsp1_rand_array_time_taken.append(y)
    y = int(float(row[2]))
    qsp1_rand_array_comparisons.append(y)
    y = int(float(row[3]))
    qsp1_rand_array_swaps.append(y)

    y = int(float(row[4]))
    qsp1_little_bad_time_taken.append(y)
    y = int(float(row[5]))
    qsp1_little_bad_comparisons.append(y)
    y = int(float(row[6]))
    qsp1_little_bad_swaps.append(y)

    y = int(float(row[7]))
    qsp1_little_good_time_taken.append(y)
    y = int(float(row[8]))
    qsp1_little_good_comparisons.append(y)
    y = int(float(row[9]))
    qsp1_little_good_swaps.append(y)

    x2 = x*math.log(x) if x>0 else 0
    x3 = x*x
    nlogn.append(x2)
    n_square.append(x3)

# initializing the rows list
rows = []

# QSPR
qspr_rand_array_time_taken = []
qspr_rand_array_comparisons = []
qspr_rand_array_swaps = []
qspr_little_bad_time_taken = []
qspr_little_bad_comparisons = []
qspr_little_bad_swaps = []
qspr_little_good_time_taken = []
qspr_little_good_comparisons = []
qspr_little_good_swaps = []

# reading csv file
with open(filename2, 'r') as csvfile:
    # creating a csv reader object
    csvreader = csv.reader(csvfile)
      
    rows.append(next(csvreader))
  
    # extracting each data row one by one
    for row in csvreader:
        rows.append(row)

for row in rows:
    y = int(float(row[1]))
    qspr_rand_array_time_taken.append(y)
    y = int(float(row[2]))
    qspr_rand_array_comparisons.append(y)
    y = int(float(row[3]))
    qspr_rand_array_swaps.append(y)

    y = int(float(row[4]))
    qspr_little_bad_time_taken.append(y)
    y = int(float(row[5]))
    qspr_little_bad_comparisons.append(y)
    y = int(float(row[6]))
    qspr_little_bad_swaps.append(y)

    y = int(float(row[7]))
    qspr_little_good_time_taken.append(y)
    y = int(float(row[8]))
    qspr_little_good_comparisons.append(y)
    y = int(float(row[9]))
    qspr_little_good_swaps.append(y)

# initializing the rows list
rows = []

# BS   
bs_rand_array_time_taken = []
bs_rand_array_comparisons = []
bs_rand_array_swaps = []
bs_little_bad_time_taken = []
bs_little_bad_comparisons = []
bs_little_bad_swaps = []
bs_little_good_time_taken = []
bs_little_good_comparisons = []
bs_little_good_swaps = []

# reading csv file
with open(filename3, 'r') as csvfile:
    # creating a csv reader object
    csvreader = csv.reader(csvfile)
      
    rows.append(next(csvreader))
  
    # extracting each data row one by one
    for row in csvreader:
        rows.append(row)

for row in rows:
    y = int(float(row[1]))
    bs_rand_array_time_taken.append(y)
    y = int(float(row[2]))
    bs_rand_array_comparisons.append(y)
    y = int(float(row[3]))
    bs_rand_array_swaps.append(y)

    y = int(float(row[4]))
    bs_little_bad_time_taken.append(y)
    y = int(float(row[5]))
    bs_little_bad_comparisons.append(y)
    y = int(float(row[6]))
    bs_little_bad_swaps.append(y)

    y = int(float(row[7]))
    bs_little_good_time_taken.append(y)
    y = int(float(row[8]))
    bs_little_good_comparisons.append(y)
    y = int(float(row[9]))
    bs_little_good_swaps.append(y)

#Plot 1:QSPR 3 array type time_taken
fig, axs = plt.subplots(1, 1,figsize =(10, 7),tight_layout = True) 
axs.plot(no_of_elements, qspr_rand_array_time_taken,label = "Random array")
axs.plot(no_of_elements, qspr_little_bad_time_taken,label = "Almost sorted")
axs.plot(no_of_elements, qspr_little_good_time_taken,label = "Almost reverse sorted")
plt.xlabel('No_of_elements')                    # naming the x axis
plt.ylabel('Time_Taken')                        # naming the y axis
plt.title('QSPR Time-Taken Comparison')         # giving a title to my graph
plt.legend()                                    # show a legend on the plot
plt.savefig('QSPR Time-Taken Comparison.png')   # saving the plot
plt.show()                                      # function to show the plot

#Plot 2:QSPR 3 array type no_comparisons
fig, axs = plt.subplots(1, 1,figsize =(10, 7),tight_layout = True) 
axs.plot(no_of_elements, qspr_rand_array_comparisons,label = "Random array")
axs.plot(no_of_elements, qspr_little_bad_comparisons,label = "Almost sorted")
axs.plot(no_of_elements, qspr_little_good_comparisons,label = "Almost reverse sorted")
plt.xlabel('No_of_elements')                           # naming the x axis
plt.ylabel('No. of Comparisons')                       # naming the y axis
plt.title('QSPR No_of_Comparisons Comparison')         # giving a title to my graph
plt.legend()                                           # show a legend on the plot
plt.savefig('QSPR No_of_Comparisons Comparison.png')   # saving the plot
plt.show()                                             # function to show the plot

#Plot 3:QSPR 3 array type swaps
fig, axs = plt.subplots(1, 1,figsize =(10, 7),tight_layout = True) 
axs.plot(no_of_elements, qspr_rand_array_swaps,label = "Random array")
axs.plot(no_of_elements, qspr_little_bad_swaps,label = "Almost sorted")
axs.plot(no_of_elements, qspr_little_good_swaps,label = "Almost reverse sorted")
plt.xlabel('No_of_elements')                    # naming the x axis
plt.ylabel('No_of_swaps')                       # naming the y axis
plt.title('QSPR No_of_swaps Comparison')        # giving a title to my graph
plt.legend()                                    # show a legend on the plot
plt.savefig('QSPR No_of_swaps Comparison.png')  # saving the plot
plt.show()                                      # function to show the plot


#Plot 4:QSP1 3 array type time_taken
fig, axs = plt.subplots(1, 1,figsize =(10, 7),tight_layout = True) 
axs.plot(no_of_elements, qsp1_rand_array_time_taken,label = "Random array")
axs.plot(no_of_elements, qsp1_little_bad_time_taken,label = "Almost sorted")
axs.plot(no_of_elements, qsp1_little_good_time_taken,label = "Almost reverse sorted")
plt.xlabel('No_of_elements')                    # naming the x axis
plt.ylabel('Time_Taken')                        # naming the y axis
plt.title('QSP1 Time-Taken Comparison')         # giving a title to my graph
plt.legend()                                    # show a legend on the plot
plt.savefig('QSPR Time-Taken Comparison.png')   # saving the plot
plt.show()                                      # function to show the plot

#Plot 5:QSP1 3 array type no_comparisons
fig, axs = plt.subplots(1, 1,figsize =(10, 7),tight_layout = True) 
axs.plot(no_of_elements, qsp1_rand_array_comparisons,label = "Random array")
axs.plot(no_of_elements, qsp1_little_bad_comparisons,label = "Almost sorted")
axs.plot(no_of_elements, qsp1_little_good_comparisons,label = "Almost reverse sorted")
plt.xlabel('No_of_elements')                           # naming the x axis
plt.ylabel('No. of Comparisons')                       # naming the y axis
plt.title('QSP1 No_of_Comparisons Comparison')         # giving a title to my graph
plt.legend()                                           # show a legend on the plot
plt.savefig('QSP1 No_of_Comparisons Comparison.png')   # saving the plot
plt.show()                                             # function to show the plot

#Plot 6:QSP1 3 array type swaps
fig, axs = plt.subplots(1, 1,figsize =(10, 7),tight_layout = True) 
axs.plot(no_of_elements, qsp1_rand_array_swaps,label = "Random array")
axs.plot(no_of_elements, qsp1_little_bad_swaps,label = "Almost sorted")
axs.plot(no_of_elements, qsp1_little_good_swaps,label = "Almost reverse sorted")
plt.xlabel('No_of_elements')                    # naming the x axis
plt.ylabel('No_of_swaps')                       # naming the y axis
plt.title('QSP1 No_of_swaps Comparison')        # giving a title to my graph
plt.legend()                                    # show a legend on the plot
plt.savefig('QSP1 No_of_swaps Comparison.png')  # saving the plot
plt.show()                                      # function to show the plot


#Plot 7:BS 3 array type time_taken
fig, axs = plt.subplots(1, 1,figsize =(10, 7),tight_layout = True) 
axs.plot(no_of_elements, bs_rand_array_time_taken,label = "Random array")
axs.plot(no_of_elements, bs_little_bad_time_taken,label = "Almost sorted")
axs.plot(no_of_elements, bs_little_good_time_taken,label = "Almost reverse sorted")
plt.xlabel('No_of_elements')                    # naming the x axis
plt.ylabel('Time_Taken')                        # naming the y axis
plt.title('BS Time-Taken Comparison')           # giving a title to my graph
plt.legend()                                    # show a legend on the plot
plt.savefig('BS Time-Taken Comparison.png')     # saving the plot
plt.show()                                      # function to show the plot

#Plot 8:BS 3 array type no_comparisons
fig, axs = plt.subplots(1, 1,figsize =(10, 7),tight_layout = True) 
axs.plot(no_of_elements, bs_rand_array_comparisons,label = "Random array")
axs.plot(no_of_elements, bs_little_bad_comparisons,label = "Almost sorted")
axs.plot(no_of_elements, bs_little_good_comparisons,label = "Almost reverse sorted")
plt.xlabel('No_of_elements')                           # naming the x axis
plt.ylabel('No. of Comparisons')                       # naming the y axis
plt.title('BS No_of_Comparisons Comparison')           # giving a title to my graph
plt.legend()                                           # show a legend on the plot
plt.savefig('BS No_of_Comparisons Comparison.png')     # saving the plot
plt.show()                                             # function to show the plot

#Plot 9:BS 3 array type swaps
fig, axs = plt.subplots(1, 1,figsize =(10, 7),tight_layout = True) 
axs.plot(no_of_elements, bs_rand_array_swaps,label = "Random array")
axs.plot(no_of_elements, bs_little_bad_swaps,label = "Almost sorted")
axs.plot(no_of_elements, bs_little_good_swaps,label = "Almost reverse sorted")
plt.xlabel('No_of_elements')                    # naming the x axis
plt.ylabel('No_of_swaps')                       # naming the y axis
plt.title('BS No_of_swaps Comparison')          # giving a title to my graph
plt.legend()                                    # show a legend on the plot
plt.savefig('BS No_of_swaps Comparison.png')    # saving the plot
plt.show()                                      # function to show the plot

#Plot 10: sort tecniques comparison on rand_array time taken
fig, axs = plt.subplots(1, 1,figsize =(10, 7),tight_layout = True) 
axs.plot(no_of_elements, bs_rand_array_time_taken,label = "Bubble Sort")
axs.plot(no_of_elements, qsp1_rand_array_time_taken,label = "Quick Sort P1")
axs.plot(no_of_elements, qspr_rand_array_time_taken,label = "Quick Sort PR")
plt.xlabel('No_of_elements')                          # naming the x axis
plt.ylabel('Time_Taken')                              # naming the y axis
plt.title('Sort techniques Time Comparison')          # giving a title to my graph
plt.legend()                                          # show a legend on the plot
plt.savefig('Sort techniques Time Comparison.png')    # saving the plot
plt.show()                                            # function to show the plot

#Plot 11: sort tecniques comparison on rand_array no of swaps
fig, axs = plt.subplots(1, 1,figsize =(10, 7),tight_layout = True) 
axs.plot(no_of_elements, bs_rand_array_swaps,label = "Bubble Sort")
axs.plot(no_of_elements, qsp1_rand_array_swaps,label = "Quick Sort P1")
axs.plot(no_of_elements, qspr_rand_array_swaps,label = "Quick Sort PR")
plt.xlabel('No_of_elements')                          # naming the x axis
plt.ylabel('No_of_swaps')                             # naming the y axis
plt.title('Sort techniques Swaps Comparison')         # giving a title to my graph
plt.legend()                                          # show a legend on the plot
plt.savefig('Sort techniques Swaps Comparison.png')   # saving the plot
plt.show()                                            # function to show the plot

#Plot 12: sort tecniques comparison on rand_array no. of comparisons
fig, axs = plt.subplots(1, 1,figsize =(10, 7),tight_layout = True) 
axs.plot(no_of_elements, bs_rand_array_comparisons,label = "Bubble Sort")
axs.plot(no_of_elements, qsp1_rand_array_comparisons,label = "Quick Sort P1")
axs.plot(no_of_elements, qspr_rand_array_comparisons,label = "Quick Sort PR")
plt.xlabel('No_of_elements')                                    # naming the x axis
plt.ylabel('No_of_Comparisons')                                 # naming the y axis
plt.title('Sort techniques No_of_Comparisons Comparison')       # giving a title to my graph
plt.legend()                                                    # show a legend on the plot
plt.savefig('Sort techniques No_of_Comparisons Comparison.png') # saving the plot
plt.show()                                                      # function to show the plot

#Plot 13: QSPR rand array timetaken vs n^2 vs nlogn
fig, axs = plt.subplots(1, 1,figsize =(10, 7),tight_layout = True) 
axs.plot(no_of_elements, n_square,label = "n^2")
axs.plot(no_of_elements, nlogn,label = "nlogn")
axs.plot(no_of_elements, qspr_rand_array_time_taken,label = "Quick Sort PR")
plt.xlabel('No_of_elements')                                    # naming the x axis
plt.ylabel('Time_Taken')                                        # naming the y axis
plt.title('QSPR rand array timetaken vs n^2 vs nlogn')          # giving a title to my graph
plt.legend()                                                    # show a legend on the plot
plt.savefig('QSPR rand array timetaken vs n^2 vs nlogn.png')    # saving the plot
plt.show()                                                      # function to show the plot

#Plot 14: BS rand array timetaken vs n^2 vs nlogn
fig, axs = plt.subplots(1, 1,figsize =(10, 7),tight_layout = True) 
axs.plot(no_of_elements, n_square,label = "n^2")
axs.plot(no_of_elements, nlogn,label = "nlogn")
axs.plot(no_of_elements, bs_rand_array_time_taken,label = "Bubble Sort")
plt.xlabel('No_of_elements')                                    # naming the x axis
plt.ylabel('Time_Taken')                                        # naming the y axis
plt.title('BS rand array timetaken vs n^2 vs nlogn')            # giving a title to my graph
plt.legend()                                                    # show a legend on the plot
plt.savefig('BS rand array timetaken vs n^2 vs nlogn.png')      # saving the plot
plt.show()    
                                                  # function to show the plot
#Plot 15: BS almost sorted rev array timetaken vs n^2 vs nlogn
fig, axs = plt.subplots(1, 1,figsize =(10, 7),tight_layout = True) 
axs.plot(no_of_elements, n_square,label = "n^2")
axs.plot(no_of_elements, nlogn,label = "nlogn")
axs.plot(no_of_elements, bs_little_good_time_taken,label = "Bubble Sort")
plt.xlabel('No_of_elements')                                                # naming the x axis
plt.ylabel('Time_Taken')                                                    # naming the y axis
plt.title('BS almost sorted rev array timetaken vs n^2 vs nlogn')           # giving a title to my graph
plt.legend()                                                                # show a legend on the plot
plt.savefig('BS almost sorted rev array timetaken vs n^2 vs nlogn.png')     # saving the plot
plt.show()   

#Plot 16: QSP1 rand array timetaken vs n^2 vs nlogn
fig, axs = plt.subplots(1, 1,figsize =(10, 7),tight_layout = True) 
axs.plot(no_of_elements, n_square,label = "n^2")
axs.plot(no_of_elements, nlogn,label = "nlogn")
axs.plot(no_of_elements, qsp1_rand_array_time_taken,label = "Quick Sort P1")
plt.xlabel('No_of_elements')                                    # naming the x axis
plt.ylabel('Time_Taken')                                        # naming the y axis
plt.title('QSP1 rand array timetaken vs n^2 vs nlogn')          # giving a title to my graph
plt.legend()                                                    # show a legend on the plot
plt.savefig('QSP1 rand array timetaken vs n^2 vs nlogn.png')    # saving the plot
plt.show()                                                      # function to show the plot