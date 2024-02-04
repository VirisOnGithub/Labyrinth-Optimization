all: compile

compile: Case.o Case.h main.o Maze.o Maze.h functions.o functions.h imgui.o imgui_widgets.o imgui_draw.o imgui_tables.o imgui-SFML.o
	g++ -g -Wall -o main main.o Case.o Maze.o functions.o imgui.o imgui_widgets.o imgui_draw.o imgui_tables.o imgui-SFML.o -lsfml-graphics -lsfml-window -lsfml-system -lGL

main.o: main.cpp Case.h Case.cpp Maze.h Maze.cpp
	g++ -g -Wall -c main.cpp

Case.o: Case.h Case.cpp
	g++ -g -Wall -c Case.cpp

Maze.o: Maze.h Maze.cpp Case.h Case.cpp
	g++ -g -Wall -c Maze.cpp

functions.o: functions.h functions.cpp
	g++ -g -Wall -c functions.cpp

#graphical
imgui.o: imgui-master/imgui.cpp imgui-master/imgui.h
	g++ -g -Wall -c imgui-master/imgui.cpp

imgui_widgets.o: imgui-master/imgui_widgets.cpp imgui-master/imgui.h
	g++ -g -Wall -c imgui-master/imgui_widgets.cpp

imgui_draw.o: imgui-master/imgui_draw.cpp imgui-master/imgui.h
	g++ -g -Wall -c imgui-master/imgui_draw.cpp

imgui_tables.o: imgui-master/imgui_tables.cpp imgui-master/imgui.h
	g++ -g -Wall -c imgui-master/imgui_tables.cpp

imgui-SFML.o: imgui-sfml/imgui-SFML.cpp imgui-sfml/imgui-SFML.h
	g++ -g -Wall -c imgui-sfml/imgui-SFML.cpp

c:
	rm -f main *.o version