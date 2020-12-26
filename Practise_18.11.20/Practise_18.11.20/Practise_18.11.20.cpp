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

void buildFullMaze(Maze& iMaze, const MTreeNode* tree);
void BuildMaze2(Maze& maze, const int maze_size);
void BuildMaze1(Maze& maze, const int maze_size);
void BuildTree(MTreeNode* node, const int width, const int height);
void BuildTreeForMaze2(Maze& maze, const int  maze_size, MTreeNode* node);
void PrintTreeInfo(const MTreeNode* tree, const int width, const int height);
vector<int> GetRandCoordinates(const int width, const int height);

void PrintTreeInfo(const MTreeNode* tree, const int width, const int height) {
	int sum_weights = 0;
	int max_weight = 0;
	queue<const MTreeNode*> nodes;
	vector<vector<string>> to_print(height);
	for (auto& vctr : to_print)
		vctr = vector<string>(width);
	for (int p = 0; p < width * height; ++p) {
		int i = tree->i();
		int j = tree->j();
		sum_weights += tree->distance();
		max_weight = max(tree->distance(), max_weight);
		to_print[i][j] = to_string(tree->distance());
		for (int ind = 0; ind < tree->childCount(); ++ind)
			nodes.push(tree->child(ind));
		if (p + 1 == width * height) break;
		tree = nodes.front();
		nodes.pop();
	}
	const int max_len = size(to_string(max_weight));
	for (auto& vctr : to_print) {
		for (auto& str : vctr)
			cout << setw(max_len + 1) << str;
		cout << endl;
	}
	const int average_weight = sum_weights / (1. * width * height);
	cout << endl << "The maximum weight of tree vertices: " << max_weight << endl;
	cout << endl << "The average weight of the vertices: " << average_weight << endl;
}

void buildFullMaze(Maze& iMaze, const MTreeNode* tree) {
	queue<const MTreeNode*> nodes;
	while (true) {
		int t_i = tree->i();
		int t_j = tree->j();
		for (int ind = 0; ind < tree->childCount(); ++ind) {
			const MTreeNode* child = tree->child(ind);
			iMaze.makeConnection(t_i, t_j, child->i(), child->j());
			nodes.push(child);
		}
		if (nodes.size() == 0)
			break;
		tree = nodes.front();
		nodes.pop();
	}
}

vector<int> GetRandCoordinates(const int width, const int height) {
	if (width == 0 || height == 0)
		return { 0, 0 };
	srand(time(NULL));
	int flag = rand() % 4 + 1;
	switch (flag) {
	case(1):
		return { 0, rand() % width };
	case(2):
		return { rand() % height, 0 };
	case(3):
		return { height - 1, rand() % width };
	default:
		return { rand() % height, width - 1 };
	}
}

void BuildTree(MTreeNode* tree, const int width, const int height) {
	queue<MTreeNode*> nodes;
	while (true) {
		int n_i = tree->i();
		int n_j = tree->j();
		for (int i = -1; i < 2; ++i)
			for (int j = -1; j < 2; ++j) {
				if ((i != 0 && j != 0) || (i == 0 && j == 0))
					continue;
				if (n_i + i < 0 || n_i + i >= height || n_j + j < 0 || n_j + j >= width)
					continue;
				int child_i = n_i + i;
				int child_j = n_j + j;
				if (!tree->searchNode(child_i, child_j)) {
					tree->addChild(child_i, child_j);
					MTreeNode* child = tree->hasChild(child_i, child_j);
					nodes.push(child);
				}
			}
		if (nodes.size() == 0)
			break;
		tree = nodes.front();
		nodes.pop();
	}
}

void BuildMaze2(Maze& maze, const int maze_size) {
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

void BuildMaze1(Maze& maze, const int maze_size) {
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

void BuildTreeForMaze2(Maze& maze, const int maze_size, MTreeNode* node) {
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
	BuildTreeForMaze2(maze2, maze_size, start_node);	//Построение и печать дерева обхода для лабиринта паутинки-лесенки
	delete start_node;

	int width, height;
	cout << endl << "Enter the height and width of the maze separated by a space: ";
	cin >> height >> width;		//Считывание размеров случайного лабиринта

	auto start_coordinates = GetRandCoordinates(width, height);//Функция для получения произвольных координат на границе лабиринта
	MTreeNode* tree = MTreeNode::begintTree(start_coordinates[0], start_coordinates[1]);
	BuildTree(tree, width, height);	//Построение дерева для случайного лабиринта заданного размера
	Maze maze3 = Maze(height, width);
	buildFullMaze(maze3, tree);	//Создание лабиринта по дереву
	cout << endl << "Maze #3:" << endl << endl;
	maze3.printMaze();	//Печать случайного лабиринта заданного размера
	cout << endl << "Node tree for random maze:" << endl << endl;
	PrintTreeInfo(tree, width, height);	//Печать весов дерева на экран построчно и пеать информации о вершинах

	return 0;
}
