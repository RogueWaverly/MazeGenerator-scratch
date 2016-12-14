# MazeGenerator-scratch
This is my scratch work for my bigger Maze Generator project.

The user types in a number of rows and a number of columns,
then the program outputs a random maze of that size with exactly one solution.

## Algorithm:

I reimagine Kruskal's Minimum Spanning Tree Algorithm to use random edges rather than the edge with the least weight.

The maze is represented by a grid with points in a 2D-array of size (rows+1)x(columns+1)
with potential vertical and horizontal walls between these points.

The outside walls are always built such that the 2 openings are
  at the top-left most horizontal wall and
  at the bottom-right most horizontal wall.

The maze is then built by randomly ordering the available inside edges, and building them one by one if the two points it connects are not already connected by other edges.
