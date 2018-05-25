OBJS = readData.o 
CC = g++
CPPFLAGS = -g -Wall


test : test.o mmio.o
	gcc -o test $^

convert : convertToValidPrediction.o 
	gcc -o convert $^


readData : $(OBJS)
	$(CC) $(LFLAGS) -o readData $(OBJS)

readData.o : 
	g++ $(CPPFLAGS) -c readData.cpp

clean :
	rm -f core readData $(OBJS)

all : readData

run : readData
	./readData

.PHONY : all clean run

