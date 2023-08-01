CXX   ?= g++
CXXDEBUG = -g -Wall
CXXSTD = -std=c++11


lexer: scanner.l scanner.hh 
	flex++ -d --outfile=scanner.yy.cc  $<
	$(CXX)  $(CXXDEBUG)  scanner.yy.cc  -o scanner


.PHONY: clean
clean:
	rm *.o