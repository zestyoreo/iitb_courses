import pandas as pd
import numpy as np
import argparse
import matplotlib.pyplot as plt

#Reading the matrix in .csv file and converting pandas datafram object to numpy array object
parser = argparse.ArgumentParser()
parser.add_argument('--path')
parser.add_argument('--output')
args = parser.parse_args()
df=pd.read_csv(args.path, sep=',',header=None)
df = df-df.mean()
x = df.to_numpy()

print(x)
#Standardizing matrix 

x_standard = x

#Finding Covariance matrix
x_cov = np.cov(x_standard.T)

#Finding eigenvalues and corresponding vectors
eig_val, eig_vec = np.linalg.eig(x_cov)

#Sorting eigenvalues
idx = eig_val.argsort()[::-1]   
eig_val = eig_val[idx]
eig_vec = eig_vec[:,idx]
print(eig_val)

#Reducing dimensions
K = 2
eig_vec_k = eig_vec[:,:K]
red_x = x_standard.dot(eig_vec_k)

output_path = args.output
csv_file_path = output_path+"transform.csv"

DF = pd.DataFrame(red_x)
# save the dataframe as a csv file
DF.to_csv(csv_file_path)

figure_path = output_path+"out.png"
f1 = red_x.T[0]
f2 = red_x.T[1]
plt.scatter(f1, f2)
plt.xlim(-15,15)
plt.ylim(-15,15)
plt.savefig(figure_path)
plt.show()
