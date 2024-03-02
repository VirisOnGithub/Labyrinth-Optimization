$(shell mkdir -p obj)
$(shell mkdir -p bin)
OBJ_DIR = obj
SRC_DIR = src
BIN_DIR = bin

all: compile

compile: $(OBJ_DIR)/Case.o $(SRC_DIR)/Case.h $(OBJ_DIR)/main.o $(OBJ_DIR)/Maze.o $(SRC_DIR)/Maze.h 
	g++ -g -Wall -o $(BIN_DIR)/main $(OBJ_DIR)/main.o $(OBJ_DIR)/Case.o $(OBJ_DIR)/Maze.o

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/Case.h $(SRC_DIR)/Case.cpp $(SRC_DIR)/Maze.h $(SRC_DIR)/Maze.cpp
	g++ -g -Wall -c $(SRC_DIR)/main.cpp -o $(OBJ_DIR)/main.o

$(OBJ_DIR)/Case.o: $(SRC_DIR)/Case.h $(SRC_DIR)/Case.cpp
	g++ -g -Wall -c $(SRC_DIR)/Case.cpp -o $(OBJ_DIR)/Case.o

$(OBJ_DIR)/Maze.o: $(SRC_DIR)/Maze.h $(SRC_DIR)/Maze.cpp $(SRC_DIR)/Case.h $(SRC_DIR)/Case.cpp
	g++ -g -Wall -c $(SRC_DIR)/Maze.cpp -o $(OBJ_DIR)/Maze.o

clean:
	rm -f $(BIN_DIR)/main

mrproper: clean
	rm -f $(OBJ_DIR)/*.o

m: mrproper
