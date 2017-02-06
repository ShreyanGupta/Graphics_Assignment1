# CFLAGS = -c -std=c++11 -Ofast -march=native
CFLAGS = -c -std=c++11 -g
LFLAGS = -std=c++11
OBJ = Matrix.o VCS.o Ray.o Object.o parse.o main.o

all : out

debug: out
	gdb out

out: $(OBJ)
	g++ $(LFLAGS) $(OBJ) -o out

Matrix.o : Matrix.cpp Matrix.h
	g++ $(CFLAGS) Matrix.cpp

VCS.o : VCS.cpp VCS.h
	g++ $(CFLAGS) VCS.cpp

Ray.o : Ray.cpp Ray.h
	g++ $(CFLAGS) Ray.cpp

Object.o : Object.cpp Object.h
	g++ $(CFLAGS) Object.cpp

parse.o : parse.cpp
	g++ $(CFLAGS) parse.cpp

main.o : main.cpp Matrix.h
	g++ $(CFLAGS) main.cpp



clean : 
	rm *.o
	rm out