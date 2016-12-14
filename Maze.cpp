#include "Maze.h"

Maze::Maze(int r, int c)
{
	rows = r;
	columns = c;
	
	edgeCount = (columns-1)*rows + columns*(rows-1);
	edges = new bool[edgeCount];

	HMaze = new wall**[rows+1];
	for(int i=0; i<rows+1; i++)
	{
		HMaze[i] = new wall*[columns];
		for(int j=0; j<columns; j++)
			HMaze[i][j] = new wall();			
	}	
	VMaze = new wall**[rows];
	for(int i=0; i<rows; i++)
	{
		VMaze[i] = new wall*[columns+1];
		for(int j=0; j<columns+1; j++)
			VMaze[i][j] = new wall();
	}

	Points = new point**[rows+1];
	for(int i=0; i<rows+1; i++)
	{
		Points[i] = new point*[columns+1];
		for(int j=0; j<columns+1; j++)
			Points[i][j] = new point();
	}
}

void Maze::makeMaze()
{
	reset();
	makeBorder();

	srand(time(NULL));
	for(int i=0; i<edgeCount; i++)
		decideToBuild(nextEdge());
}

void Maze::printMaze()
{
	printHRow(0);
	for(int i=0; i<rows; i++)
	{
		printVRow(i);
		printHRow(i+1);
	}
}

void Maze::reset()
{
	for(int i=0; i<edgeCount; i++)
		edges[i] = 0;

	for(int i=0; i<rows+1; i++)
		for(int j=0; j<columns; j++)
			HMaze[i][j]->reset();
	for(int i=0; i<rows; i++)
		for(int j=0; j<columns+1; j++)
			VMaze[i][j]->reset();

	for(int i=0; i<rows+1; i++)
		for(int j=0; j<columns+1; j++)
			Points[i][j]->reset();
}

void Maze::makeBorder()
{
	for(int i=0; i<columns-1; i++)
	{
		HMaze[0][i+1]->build = 1;
		HMaze[rows][i]->build = 1;
	}
	for(int i=0; i<rows; i++)
	{
		VMaze[i][0]->build = 1;
		VMaze[i][columns]->build = 1;

		Points[i][0]->parent = Points[0][0];
		Points[i][columns]->parent = Points[0][0];
	}

	for(int i=0; i<columns+1; i++)
	{
		Points[0][i]->parent = Points[0][0];
		Points[rows][i]->parent = Points[0][0];
	}
	for(int i=1; i<rows; i++)
	{
		Points[i][0]->parent = Points[0][0];
		Points[i][columns]->parent = Points[0][0];
	}
}

int Maze::nextEdge()
{
	bool isEmpty = false;
	int origEdge = ((float)rand())/RAND_MAX * edgeCount;
	int edge = origEdge;
	if(edges[edge])
	{
		bool increment = ((float)rand())/RAND_MAX * 2;
		if(increment)
			while(!isEmpty && edges[edge])
			{
				if(++edge == origEdge)
					isEmpty = 1;
				edge %= edgeCount;
			}
		else
			while(!isEmpty && edges[edge])
			{
				if(--edge == origEdge)
					isEmpty = 1;
				edge %= edgeCount;
			}
	}
	if(isEmpty)
		edge = -1;
	else
		edges[edge] = 1;
	return edge;
}

void Maze::decideToBuild(int edgeNum)
{
	int numOfVWalls = rows*(columns-1);

	wall* theWall;
	point* topLeft;
	point* botRight;
	if(edgeNum < numOfVWalls)		// V Wall
	{
		int i = edgeNum%rows;
		int j = edgeNum/rows + 1;
		theWall = VMaze[i][j];
		topLeft = findParent(Points[i][j]);
		botRight = findParent(Points[i+1][j]);
	}
	else							// H Wall
	{
		edgeNum -= numOfVWalls;
		int i = edgeNum/columns + 1;
		int j = edgeNum%columns;
		theWall = HMaze[i][j];
		topLeft = findParent(Points[i][j]);
		botRight = findParent(Points[i][j+1]);
	}

	if(topLeft != botRight)
	{
		if(topLeft->rank < botRight->rank)
			topLeft->parent = botRight;
		else if(botRight->rank < topLeft->rank)
			botRight->parent = topLeft;
		else
		{
			topLeft->parent = botRight;
			botRight->rank++;
		}

		theWall->build = 1;
	}
}

Maze::point* Maze::findParent(point* p)
{
	point* parent = p->parent;
	while(parent != parent->parent)
		parent = parent->parent;
	return parent;
}

void Maze::printHRow(int row)
{
	for(int i=0; i<columns; i++)
	{
		std::cout << "+";
		if(HMaze[row][i]->build)
			std::cout << "~~";
		else
			std::cout << "  ";
	}
	std::cout << "+\n";
}

void Maze::printVRow(int row)
{
	if(VMaze[row][0]->build)
			std::cout << "|";
		else
			std::cout << " ";
	for(int i=1; i<columns+1; i++)
	{
		std::cout << "  ";
		if(VMaze[row][i]->build)
			std::cout << "|";
		else
			std::cout << " ";
	}
	std::cout << "\n";
}