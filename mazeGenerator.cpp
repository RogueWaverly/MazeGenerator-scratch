#include "Maze.h"

int main()
{
	int rows, columns;
	std::cout << "How many rows? ";
	std::cin >> rows;
	std::cout << "How many columns? ";
	std::cin >> columns;

	Maze* maze = new Maze(rows, columns);
	maze->makeMaze();
	maze->printMaze();

	return 0;
}