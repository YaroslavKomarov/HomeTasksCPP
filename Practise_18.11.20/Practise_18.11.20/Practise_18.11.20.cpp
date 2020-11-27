#include <iostream>
#include "MCell.h"
#include "Maze.h"
using namespace std;

void ChangeMaze(Maze& maze, const int& width, const int& height) {
	int ind_right = 0;
	int ind_down = 1;
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			if (i == width - 1 && j == height - 1) {
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
}

int main()
{
	const int maze_size = 5;
	Maze maze = Maze(maze_size, maze_size);
	ChangeMaze(maze, maze_size, maze_size);
	auto res = true << 3 | true << 2;
	maze.printMaze();
}
