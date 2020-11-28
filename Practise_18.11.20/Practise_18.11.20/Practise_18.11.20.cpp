#include <iostream>
#include "MCell.h"
#include "Maze.h"
using namespace std;

int main()
{
	const int maze_size = 5;
	Maze maze = Maze(maze_size, maze_size);

	int ind_right = 0;
	int ind_down = 1;
	for (int i = 0; i < maze_size; ++i) {
		for (int j = 0; j < maze_size; ++j) {
			if (i == maze_size - 1 && j == maze_size - 1) {
				break;
			}
			if (i == ind_right && j == ind_right) {
				maze.makeConnection(i, j, i, j + 1);
			}
			if (i == ind_right && j == ind_down) {
				maze.makeConnection(i, j, i + 1, j);
			}
		}
		++ind_down;
		++ind_right;
	}

	maze.printMaze();
}
