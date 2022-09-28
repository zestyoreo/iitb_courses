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

#Printing upper triangular matrix
matrix = matrix.transpose()
rows = matrix.shape[0]
for i in range(rows):
  for j in range(i+1):
    print(matrix[i][j],end = ' ')
  print('')
   
