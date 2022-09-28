ifndef VERBOSE
.SILENT:

./matrix: matrix.o
	g++ -std=c++17 -g -o matrix matrix.o 

matrix.o: matrix.cpp
	g++ -std=c++17 -g -o matrix.o -c matrix.cpp

gdb: ./matrix
	gdb -batch -x t1.gdb --args ./matrix 4 3 3 4 7 8 1 8 6 5 0 9 8 3

clean:
	rm *.o *.exe *.out ./matrix

endif
