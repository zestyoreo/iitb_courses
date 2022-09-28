ifndef VERBOSE
.SILENT:

./tree: tree.o
	g++ -std=c++17 -g -o tree tree.o 

tree.o: tree.hpp tree.cpp
	g++ -std=c++17 -g -o tree.o -c tree.cpp

gdb: ./tree
	gdb -batch -x t2.gdb --args ./tree 12 40 28 56 21 8 23 3 2 5 

clean:
	rm *.o *.exe *.out ./tree

endif