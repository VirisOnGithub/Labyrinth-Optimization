all : compile

compile : 
	g++ -g -Wall -o main main.cpp

clean :
	rm -f main