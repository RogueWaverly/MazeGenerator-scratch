#include <iostream>
#include <stdlib.h>

#ifndef Maze_H
#define Maze_H

class Maze
{
	struct wall
	{
		bool build;
		wall() : build(0) {};
		void reset()
		{
			build = 0;
		}
	};

	struct point
	{
		point* parent;
		int rank;
		point() : parent(this), rank(0) {};
		void reset()
		{
			parent = this;
			rank = 0;
		}
	};

	int rows, columns, edgeCount;
	wall*** HMaze;
	wall*** VMaze;
	point*** Points;
	bool* edges;

public:
	Maze(int r, int c);
	void makeMaze();
	void printMaze();
private:
	void reset();
	void makeBorder();
	int nextEdge();
	void decideToBuild(int edgeNum);
	point* findParent(point* p);
	void printHRow(int row);
	void printVRow(int row);
};

#endif