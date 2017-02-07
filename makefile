CFLAGS = -c -std=c++11 -Ofast -march=native
# CFLAGS = -c -std=c++11 -g
LFLAGS = -std=c++11
OBJ = Matrix.o VCS.o Ray.o Object.o parse.o

all : render

debug: render
	gdb render

render: $(OBJ) main.o
	g++ $(LFLAGS) $(OBJ) main.o -o render

test: $(OBJ) test.o
	g++ $(LFLAGS) $(OBJ) test.o -o render

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

main.o : main.cpp VCS.h Object.h
	g++ $(CFLAGS) main.cpp

test.o : test.cpp VCS.h
	g++ $(CFLAGS) test.cpp

clean : 
	rm *.o
	rm render
	rm matrix.txt
	rm image.jpg