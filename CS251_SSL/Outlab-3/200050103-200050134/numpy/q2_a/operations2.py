#Importing the libraries
import pandas as pd
import numpy as np
import argparse
np.set_printoptions(precision=2)

#Reading the matrix in .csv file and converting pandas datafram object to numpy array object
parser = argparse.ArgumentParser()
parser.add_argument('--path')
args = parser.parse_args()
df=pd.read_csv(args.path, sep=',',header=None)
matrix = df.to_numpy()

#Mean along x-axis
x_mean = np.mean(matrix, axis=0)
print(x_mean)

#Median along x-axis
x_median = np.median(matrix, axis=0)
print(x_median)

#Standard Deviation along x-axis
x_std = np.std(matrix, axis=0)
print(x_std)

#Finding Determinant
deter = np.linalg.det(matrix)
print(deter)

#Finding inverse matrix
if deter!=0:
    x_inv = np.linalg.inv(matrix)
    print(x_inv)
else:
    x_inv = np.linalg.pinv(matrix)
    print(x_inv)