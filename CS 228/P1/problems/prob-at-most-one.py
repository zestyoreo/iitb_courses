#!/usr/bin/python3

from z3 import *
import argparse
import itertools
import time

# number of variables
n=10

# constructed list of variables
vs = []

print vs

# write function that encodes that exactly one variable is one
def sum_to_one( ls ):
    

# call the function
F = sum_to_one( vs )
print F

# construct Z3 solver

# add the formula in the solver

# check sat value

if result == sat:
    # get satisfying model

    # print only if value is true

else:
    print("unsat")
