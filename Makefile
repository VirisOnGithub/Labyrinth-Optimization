all: compile

compile: Case.o Case.h main.o Maze.o Maze.h 
	g++ -g -Wall -o main main.o Case.o Maze.o

main.o: main.cpp Case.h Case.cpp Maze.h Maze.cpp
	g++ -g -Wall -c main.cpp

Case.o: Case.h Case.cpp
	g++ -g -Wall -c Case.cpp

Maze.o: Maze.h Maze.cpp Case.h Case.cpp
	g++ -g -Wall -c Maze.cpp

clean:
	rm -f main

mrproper: clean
	rm -f *.o
