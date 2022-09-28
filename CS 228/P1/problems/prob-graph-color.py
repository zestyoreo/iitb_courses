#!/usr/bin/python3

from z3 import *
import argparse
import itertools
import time

n = 500
d = 3

# reading edges from a file
# the file has 7000 edges for graph with 500 nodes
edges = []
with open("edges.txt") as f:
    for line in f:
        edges.append([int(v) for v in line.strip().split(',')])

# declare variables 3 color problem for 500 nodes
vs = [ [ Bool ("e_{}_{}".format(i,j)) for j in range(d)] for i in range(n)]

Node_Fs = []
# encode each nodes has at least one color

# encode neigbouring nodes do not have same color
edge_Fs = []


# in a loop,
#  -- color nodes after considering only first k edges
#  -- print k,time for solving, sat/unsat
#  -- increase k by delta
# Our aim is to plot k vs. time to solve

# Hint: time.time() returns current time

k     = 0
delta = 10
limit = 2000
while k < limit:
    # write the loop body

    k = k + delta
