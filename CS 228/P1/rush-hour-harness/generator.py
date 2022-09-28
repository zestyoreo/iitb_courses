'''
		OVERVIEW
_________________________________________________________________________________________


This exercise is inspired by the eponymous sliding block game:
https://en.wikipedia.org/wiki/Rush_Hour_(puzzle)

Here is the description of the exercise:
1) There is an n x n grid
2) A set of 2 x 1 cars are positioned on the grid. They are oriented horizontally or vertically.
   - Each car can move forward or backward in the direction of the car if another car is not blocking the car.
   - A move is shifting any one car by a single block
3) A special red car, which moves horizontally.
   - The goal is to get the red car to the rightmost end of its lane within a given number of moves (referred to as "limit")
4) There are some 1 x 1 mines on the grid. A car cannot drive over a mine.
5) Cars cannot collide with each other

Example:
	
	0     1    2    3    4    5
	_______________________________
0	|    |    |    | X  |    |    |
	|____|____|____|____|____|____|
1	|    |    |    | V1 |    |    |
	|____|____|____|____|____|____|
2	|    | R  | R  | V1 |    | V2 |
	|____|____|____|____|____|____|
3	|    | X  | H  | H  |    | V2 |
	|____|____|____|____|____|____|
4	|    |    |    |    |    |    |
	|____|____|____|____|____|____|
5       |    |    |    |    |    |    |
	|____|____|____|____|____|____|

In the above diagram, the red car is denoted with the letter R is located in
row two. There are two vertical cars (V1 and V2), and one other horizontal car (H).
There are two mines, each denoted by the letter X. The goal is to bring R to column 5.

_________________________________________________________________________________________

		INPUT FORMAT
_________________________________________________________________________________________

We will describe objects on the grid by 3 comma-separated non-negative integers:
- orientation: 0 for vertical car, 1 for horizontal car, 2 for mine
- location: row,column
    * for cars, if the location of a vertical car is given as (i, j), it stands on (i, j) and (i+1, j)
    * likewise, the location of a horizontal car occupying (i, j) and (i, j+1) is given by (i, j)
	
The Red Car moves horizontally, so we omit the orientation for it.

Thus, the input is as follows.

First line: the dimension of the grid "n", and the maximum number of moves "limit"
   -Example: "6,17" means "the red car needs to reach the right edge of the 6x6 grid in at most 17 moves"

Second line: location of the red car.

The remaining lines: descriptions of the rest of the objects, as explained above.

Here is the input for the above example:

6,11
2,1
0,1,3
0,2,5
1,3,2
2,0,3
2,3,1

_________________________________________________________________________________________

		SOLUTION
___________________________________________________________________________________________

In this assignment,  you encode the above game as a SAT problem and use a SAT
solver to find the moves to bring the red car to the exit within the given limit. 

Write your solution in a file called rush_hour.py

_________________________________________________________________________________________

		OUTPUT
___________________________________________________________________________________________

Your code must only output to stdout.

- If the goal is not possible, your code should only print "unsat" and exit
	
- If the goal is possible, your code should print a sequence of moves, one per line
   * A move is two comma-separated non-negative integers
   * The pair denotes a position on the grid (row, column).
   * The car that occupies the position. moves and will move in a way such 
     that it will continue to occupy the position.

Example output:

3,5
4,5
3,3
3,4
2,3
3,3
2,2
2,3
2,4

The above sequence of moves solves the example grid.

_________________________________________________________________________________________

		HARNESS CODE
_________________________________________________________________________________________
	
To generate inputs for testing, use this file as follows:

$ python3 generator.py foo.txt

The above command will produce a random input in foo.txt

We will call your solution using the following command.

$ python3 rush_hour.py /path/to/foo.txt > /path/to/bar.txt

You can write code in auxiliary files for readability (eg. utils.py),
but you can't assume that any of the files that we have provided will be present
in the working directory when we run your code

Finally, we will verify the output with our simulator included in this folder.

$ python3 simulate.py foo.txt bar.txt

_________________________________________________________________________________________

		SUBMISSION INSTRUCTIONS
_________________________________________________________________________________________

Please refer to the course website
(https://www.cse.iitb.ac.in/~akg/courses/2022-logic/)

'''



import numpy as np
import sys

n = np.random.randint(5, 14)
limit = np.random.randint(n, min(80, 5*n))

file = open(sys.argv[1], "w")
file.write(str(n)+","+str(limit)+"\n")

randomly_generate = 0

board = np.zeros((n, n))

red_orient = 1

red_alley = np.random.randint(n)
red_start = np.random.randint(n-1)


file.write(str(red_alley)+","+str(red_start)+"\n")
board[red_alley][red_start] = 1
board[red_alley][red_start+1] = 1
	


	
for i in range(np.random.randint(2*n, 4*n)):
	orient = np.random.randint(2)
	alley = np.random.randint(n)
	start = np.random.randint(n-1)
	draw = np.random.randint(n)
	mine = 1 if draw == 0 else 0
	orient = orient + mine
	
	if orient == red_orient and alley == red_alley:
		continue
	
	if orient == 0:
		if randomly_generate == 0:
			if board[start][alley]+board[start + 1][alley] != 0:
				continue
		file.write(str(orient)+","+str(start)+","+str(alley)+"\n")
		board[start][alley] = 1
		board[start + 1][alley] = 1
	
	elif orient == 1:
		if randomly_generate == 0:
			if board[alley][start]+board[alley][start + 1] != 0:
				continue
		file.write(str(orient)+","+str(alley)+","+str(start)+"\n")
		board[alley][start] = 1
		board[alley][start+ 1] = 1
		
	else:
		row = np.random.randint(n)
		col = np.random.randint(n)
		if randomly_generate == 0:
			if board[row][col] != 0:
				continue
		file.write(str(orient)+","+str(row)+","+str(col)+"\n")
		board[row][col] = 1
		
	


file.close()
