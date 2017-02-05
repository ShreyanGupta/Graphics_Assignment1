CFLAGS = -c -std=c++11 -Ofast -march=native
LFLAGS = -std=c++11 -Ofast -march=native
OBJ = 

all : out

out: $(OBJ) Part1.o
	g++ $(LFLAGS) $(OBJ) Part1.o -o p1

Part1.o : Part1.cpp Head.h
	g++ $(CFLAGS) Part1.cpp

clean : 
	rm *.o
	rm p1