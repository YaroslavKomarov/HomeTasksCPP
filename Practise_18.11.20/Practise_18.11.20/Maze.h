#pragma once
#include "MCell.h"
#include <map>

enum MazeElem {
	PrevDown = 1 << 0,
	PrevRight = 1 << 1,
	Down = 1 << 2,
	Right = 1 << 3,
};

class Maze {
private:
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
