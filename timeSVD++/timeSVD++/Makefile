all: run.sh

run: run.sh
	./run.sh

clean:
	rm *.o
run.sh: main.o
	g++ -g main.o -o run.sh
main.o: main.cpp SVD.h
	g++ -g -std=c++0x -c main.cpp

.PHONY: run clean all



