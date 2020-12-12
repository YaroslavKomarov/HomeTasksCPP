#include <iomanip>
#include <iostream>
#include <queue>
#include <algorithm>
#include <string>
#include "MTreeNode.h"
#include "MCell.h"
#include "Maze.h"
#include <time.h>
using namespace std;

void BuildMaze2(Maze& maze, const int& maze_size);
void BuildMaze1(Maze& maze, const int& maze_size);
void GetTreeForMaze2(Maze& maze, const int& maze_size, MTreeNode* node);


void BuildMaze2(Maze& maze, const int& maze_size) {
	int ind_right = 0;
	int ind_down = 0;
	for (int i = 0; i < maze_size - 1; ++i) {
		int count = i + 2;
		for (int j = 0; j < maze_size; ++j) {
			if (ind_right == j) {
				ind_right++;
				maze.makeConnection(i, j, i, j + 1);
			}
			if (ind_down == i && j < count) {
				maze.makeConnection(i, j, i + 1, j);
			}
		}
		ind_down++;
		ind_right = ind_down;
	}
}

void BuildMaze1(Maze& maze, const int& maze_size) {
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
}

void GetTreeForMaze2(Maze& maze, const int& maze_size, MTreeNode* node) {
	vector<string> strings;
	queue<MTreeNode*> nodes;
	while (true) {
		int i = node->i();
		int j = node->j();
		if (maze.hasConnection(i, j, i + 1, j)) {
			node->addChild(i + 1, j);
			nodes.push(node->hasChild(i + 1, j));
		}
		if (maze.hasConnection(i, j, i, j + 1)) {
			node->addChild(i, j + 1);
			nodes.push(node->hasChild(i, j + 1));
		}
		if (i < strings.size())
			strings[i] += to_string(node->distance()) + ' ';
		else
			strings.push_back(to_string(node->distance()) + ' ');
		
		if (nodes.size() == 0)
			break;
		node = nodes.front();
		nodes.pop();
	}
	for (auto& str : strings)
		cout << str << endl;
}

int main()
{
	const int maze_size = 5;
	Maze maze1 = Maze(maze_size, maze_size);
	BuildMaze1(maze1, maze_size);	//Построение простого лабиринта-лесенки
	cout << "Maze #1:" << endl << endl;
	maze1.printMaze();	//Печать лабиринта-лесенки

	Maze maze2 = Maze(maze_size, maze_size);
	BuildMaze2(maze2, maze_size);	//Построение лабиринта паутинки-лесенки
	cout << endl << "Maze #2:" << endl << endl;
	maze2.printMaze();	//Печать лабиринта паутинки-лесенки

	MTreeNode* start_node = MTreeNode::begintTree(0, 0);
	cout << endl << "Node tree for Maze #2:" << endl << endl;
	GetTreeForMaze2(maze2, maze_size, start_node);	//Построение и печать дерева обхода для лабиринта паутинки-лесенки
	delete start_node;

	return 0;
}
