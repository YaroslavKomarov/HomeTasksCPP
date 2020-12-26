#pragma once
//#include <map>
#include "MCell.h"

class Maze {
public:
	Maze(int n, int m);
	~Maze();
	const MCell& cell(int i, int j) const;
	bool hasConnection(int i1, int j1, int i2, int j2) const;
	bool makeConnection(int i1, int j1, int i2, int j2);
	bool removeConnection(int i1, int j1, int i2, int j2);
	void printMaze() const;
private:
	MCell* m_field = nullptr;
	int m_width = 0;
	int m_height = 0;
};
