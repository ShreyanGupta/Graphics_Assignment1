CFLAGS = -c -std=c++11 -Ofast -march=native
LFLAGS = -std=c++11 -Ofast -march=native
OBJ = Matrix.o

all : out

out: $(OBJ) Part1.o
	g++ $(LFLAGS) $(OBJ) Part1.o -o p1

Matrix.o : Matrix.cpp Matrix.h
	g++ $(CFLAGS) Matrix.cpp

Part1.o : Part1.cpp Matrix.h
	g++ $(CFLAGS) Part1.cpp

clean : 
	rm *.o
	rm p1