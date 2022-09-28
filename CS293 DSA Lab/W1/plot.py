import matplotlib.pyplot as plt

lines = []
with open('linear_time.txt') as f:
    lines = f.readlines()

# x axis values
linear_no_insertions = []
# corresponding y axis values
linear_time_taken = []

for line in lines:
    linear_no_insertions.append(int(line.split(",")[0]))
    linear_time_taken.append(int(line.split(",")[1]))
  
# plotting the points 
plt.plot(linear_no_insertions, linear_time_taken,label = "linear")


lines = []
with open('expo_time.txt') as f:
    lines = f.readlines()
# x axis values
expo_no_insertions = []
# corresponding y axis values
expo_time_taken = []
for line in lines:
    expo_no_insertions.append(int(line.split(",")[0]))
    expo_time_taken.append(int(line.split(",")[1]))
  
# plotting the points 
plt.plot(expo_no_insertions, expo_time_taken,label = "exponential")

  
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
