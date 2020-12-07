#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include "MTreeNode.h"
#include "MCell.h"
#include "Maze.h"
using namespace std;

void BuildWebStepMaze(Maze& maze, const int& maze_size) {
	int ind_right = 0;
	int ind_down = 0;
	for (int i = 0; i < maze_size; ++i) {
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

void GetTree(Maze& maze, const int& maze_size, MTreeNode& start_node) {
	vector<string> strings;
	queue<MTreeNode*> nodes;
	MTreeNode* node = &start_node;
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

	int ind_right = 0;
	int ind_down = 1;
	for (int i = 0; i < maze_size; ++i) {
		for (int j = 0; j < maze_size; ++j) {
			if (i == maze_size - 1 && j == maze_size - 1) {
				break;
			}
			if (i == ind_right && j == ind_right) {
				maze1.makeConnection(i, j, i, j + 1);
			}
			if (i == ind_right && j == ind_down) {
				maze1.makeConnection(i, j, i + 1, j);
			}
		}
		++ind_down;
		++ind_right;
	}

	cout << "Maze #1:" << endl << endl;
	maze1.printMaze();

	Maze maze2 = Maze(maze_size, maze_size);
	BuildWebStepMaze(maze2, maze_size);

	cout << endl << "Maze #2:" << endl << endl;
	maze2.printMaze();

	MTreeNode start_node = MTreeNode::begintTree(0, 0);

	cout << endl << "TreeNode for Maze #2:" << endl << endl;
	GetTree(maze2, maze_size, start_node);

	return 0;
}
