#pragma once
#include <map>
#include "MCell.h"
using namespace std;

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
