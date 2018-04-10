OBJS = readData.o 
CC = g++
CPPFLAGS = -g -Wall



readData : $(OBJS)
	$(CC) -o readData $(OBJS)

readData.o : 
	g++ $(CPPFLAGS) -c readData.cpp

clean :
	rm -f core readData $(OBJS)