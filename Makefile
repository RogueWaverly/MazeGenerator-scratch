all: release

COMPILER = g++

release: mazeGenerator.o Maze.o
	$(COMPILER) obj/*.o
	rm obj/*.o

mazeGenerator.o:
	$(COMPILER) -c -o obj/mazeGenerator.o mazeGenerator.cpp
Maze.o:
	$(COMPILER) -c -o obj/Maze.o Maze.cpp