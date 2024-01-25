all: compile

compile: Case.h main.cpp
	g++ -g -Wall -o main main.cpp

clean:
	rm -f main
