#Importing the libraries
import pandas as pd
import numpy as np
import argparse

#Reading the matrix in .csv file and converting pandas datafram object to numpy array object
parser = argparse.ArgumentParser()
parser.add_argument('--path')
parser.add_argument('--num',type=int)
args = parser.parse_args()
df=pd.read_csv(args.path, sep=',',header=None)
matrix = df.to_numpy()

#Getting padding value
num = int(args.num) 

#Padding the matrix and displaying padded matrix
padded_matrix = np.pad(matrix, ((num, num), (num, num)), 'constant',constant_values=((0, 0),(0,0)))
print(padded_matrix)

