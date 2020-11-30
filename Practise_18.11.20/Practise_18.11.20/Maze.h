#pragma once
#include <map>
#include "MCell.h"
using namespace std;

enum MazeElem {
	Up = 1 << 0,
	Left = 1 << 1,
	Down = 1 << 2,
	Right = 1 << 3,
	UpLeft = Up + Left,
	UpDown = Up + Down,
	UpRight = Up + Right,
	LeftDown = Left + Down,
	LeftRight = Left + Right,
	RightDown = Right + Down,
	UpLeftDown = Up + Left + Down,
	UpLeftRight = Up + Left + Right,
	UpDownRight = Up + Down + Right,
	LeftDownRight = Left + Down + Right,
	AllDirection = Up + Left + Down + Right,
};

class Maze {
private:
	map<int, char> m_dict;
	MCell* m_field;
	int width;
	int size;
public:
	Maze(int n, int m);
	~Maze();
	const MCell& cell(int i, int j) const;
	bool hasConnection(int i1, int j1, int i2, int j2);
	bool makeConnection(int i1, int j1, int i2, int j2);
	bool removeConnection(int i1, int j1, int i2, int j2);
	void printMaze() const;
};
