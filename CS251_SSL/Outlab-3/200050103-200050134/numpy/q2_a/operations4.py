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

#Flattening the matrix
flat = matrix.flatten()

#Sorting flattened matrix
flat = np.sort(flat)

#Finding unique elements in numpy array and displaying unique elements with their respective counts
unique, count = np.unique(flat, return_counts=True)
print(unique)
print(count)

#Displaying the frequency of second largest element
print(count[-2])