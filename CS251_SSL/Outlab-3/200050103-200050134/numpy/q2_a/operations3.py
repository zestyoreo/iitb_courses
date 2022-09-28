#Importing the libraries
import pandas as pd
import numpy as np
import argparse

#Reading the matrix in .csv file and converting pandas datafram object to numpy array object
parser = argparse.ArgumentParser()
parser.add_argument('--path')
args = parser.parse_args()
df=pd.read_csv(args.path, sep=',',header=None)
matrix = df.to_numpy()

#Finding and displaying the matrix/array sorted in the x and y axis
x_sort = np.sort(matrix,axis=0)
print(x_sort)
y_sort = np.sort(matrix,axis=1)
print(y_sort)

#Flattening the matrix and printing flat array
flat = matrix.flatten()
flat = np.sort(flat)
print(flat)