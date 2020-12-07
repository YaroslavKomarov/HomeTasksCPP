#include <algorithm>
#include <iostream>
#include "Maze.h"
using namespace std;

Maze::Maze(int n, int m) {
	width = m;
	size = n * m;
	m_field = new MCell[size];
	m_dict = { {AllDirection, char(197)}, {UpLeftDown, char(180)}, {UpLeftRight, char(193)},
		{UpDownRight, char(195)}, {LeftDownRight, char(194)}, {UpLeft, char(217)},
		{UpDown, char(179)}, {UpRight, char(192)}, {LeftDown, char(191)},
		{LeftRight, char(196)}, {RightDown, char(218)}, {Up, '0'}, {Down, '0'}, {Left, '0'}, {Right, '0'} };
}

Maze::~Maze() { delete[] m_field; }

const MCell& Maze::cell(int i, int j) const { return m_field[i * width + j]; }

bool Maze::hasConnection(int i1, int j1, int i2, int j2) {
	int ind1 = min(i1, i2);
	int ind2 = min(j1, j2);
	if (j2 < 0 || j2 >= width || i2 < 0 || i2 >= width)
		return false;
	if (i1 == i2) {
		return m_field[ind1 * width + ind2].right();
	}
	else if (j2 == j1) {
		return m_field[ind1 * width + ind2].down();
	}
	else
		return false;
}

bool Maze::makeConnection(int i1, int j1, int i2, int j2) {
	int ind1 = min(i1, i2);
	int ind2 = min(j1, j2);
	if (j2 < 0 || j2 >= width || i2 < 0 || i2 >= width)
		return false;
	if (i1 == i2) {
		m_field[ind1 * width + ind2].m_right = true;
		return true;
	}
	else if (j1 == j2) {
		m_field[ind1 * width + ind2].m_down = true;
		return true;
	}
	else
		return false;
}

bool Maze::removeConnection(int i1, int j1, int i2, int j2) {
	int ind1 = min(i1, i2);
	int ind2 = min(j1, j2);
	if (j2 < 0 || j2 >= width || i2 < 0 || i2 >= width)
		return false;
	if (i1 == i2) {
		m_field[ind1 * width + ind2].m_right = false;
		return true;
	}
	else if (j2 == j1) {
		m_field[ind1 * width + ind2].m_down = false;
		return true;
	}
	else
		return false;
}

void Maze::printMaze() const {
	for (int n = 0; n < size; ++n) {
		int i = n / width;
		int j = n % width;
		int res = m_field[n].right() << 3 | m_field[n].down() << 2;
		if (i - 1 >= 0)
			res += m_field[(i - 1) * width + j].down() << 0;
		if (j - 1 >= 0)
			res += m_field[i * width + j - 1].right() << 1;

		if (res == 0 || res == 1 || res == 2 || res == 4 || res == 8)
			cout << '0';
		else
			cout << m_dict.find(res)->second;

		if (j + 1 == width)
			cout << endl;
	}
}