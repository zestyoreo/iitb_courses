#!/usr/bin/python3

from z3 import *
import argparse
import itertools
import time

problem1 = [
 [ 9, 0, 0,   0, 1, 0,   5, 0, 0],
 [ 7, 0, 0,   8, 0, 3,   0, 0, 2],
 [ 0, 0, 0,   0, 0, 0,   3, 0, 8],

 [ 0, 7, 8,   0, 2, 5,   6, 0, 0],
 [ 0, 0, 0,   0, 0, 0,   0, 0, 0],
 [ 0, 0, 2,   3, 4, 0,   1, 8, 0],

 [ 8, 0, 9,   0, 0, 0,   0, 0, 0],
 [ 5, 0, 0,   4, 0, 1,   0, 0, 9],
 [ 0, 0, 1,   0, 5, 0,   0, 0, 4]
]

problem2 = [
[ 0, 8, 0,   0, 0, 3,   0, 0, 0],
[ 5, 0, 3,   0, 4, 0,   2, 0, 0],
[ 7, 0, 4,   0, 8, 0,   0, 0, 3],

[ 0, 7, 0,   0, 0, 0,   5, 0, 0],
[ 0, 3, 0,   8, 0, 5,   0, 6, 0],
[ 0, 0, 1,   0, 0, 0,   0, 9, 0],

[ 9, 0, 0,   0, 3, 0,   7, 0, 6],
[ 0, 0, 7,   0, 2, 0,   3, 0, 1],
[ 0, 0, 0,   6, 0, 0,   0, 2, 0]
]

problem3 = [
[ 7, 0, 0,   8, 0, 5,   0, 0, 6],
[ 0, 0, 4,   0, 6, 0,   2, 0, 0],
[ 0, 5, 0,   2, 0, 4,   0, 9, 0],

[ 8, 0, 5,   0, 0, 0,   3, 0, 9],
[ 0, 1, 0,   0, 0, 0,   0, 6, 0],
[ 3, 0, 6,   0, 0, 0,   1, 0, 7],

[ 0, 6, 0,   5, 0, 7,   0, 1, 0],
[ 0, 0, 7,   0, 9, 0,   6, 0, 0],
[ 5, 0, 0,   3, 0, 6,   0, 0, 2]
]

problem = problem1
# problem = problem2

# define the problem variables
# Hint: three dimentional array

# def sum_to_one( ls ):
    # reuse some to one code

# Accumulate constraints in the following list 
Fs = []


# Encode already filled positions

# Encode for i,j  \sum_k x_i_j_k = 1

# Encode for j,k  \sum_i x_i_j_k = 1

# Encode for i,k  \sum_j x_i_j_k = 1

# Encode for i,j,k  \sum_r_s x_3i+r_3j+s_k = 1



s = Solver()
s.add( And( Fs ) )

if s.check() == sat:
    m = s.model()
    for i in range(9):
        if i % 3 == 0 :
            print("|-------|-------|-------|")
        for j in range(9):
            if j % 3 == 0 :
                print ("|", end =" ")
            for k in range(9):
                # FILL THE GAP
                # val model for the variables
                # val = m[]
                if is_true( val ):
                    print("{}".format(k+1), end =" ")
        print("|")
    print("|-------|-------|-------|")
else:
    print("sudoku is unsat")

# print vars
