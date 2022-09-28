.PHONY: t%.o
t%.o: t%.cpp
	g++ -g -c t$*.cpp -o t$*.o

.PHONY: t%
t%: t%.o init
	g++ t$*.o init -o t$*.out

.PHONY: clean
clean:
	rm *.o *.out
