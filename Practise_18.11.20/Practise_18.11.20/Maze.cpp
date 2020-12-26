#include <algorithm>
#include <iostream>
#include <map>
#include "Maze.h"
#include <cassert>
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
static map<int, char> m_dict = { {AllDirection, char(197)}, {UpLeftDown, char(180)}, {UpLeftRight, char(193)},
		{UpDownRight, char(195)}, {LeftDownRight, char(194)}, {UpLeft, char(217)},
		{UpDown, char(179)}, {UpRight, char(192)}, {LeftDown, char(191)},
		{LeftRight, char(196)}, {RightDown, char(218)}, {Up, '0'}, {Down, '0'}, {Left, '0'}, {Right, '0'}, {0, '0'}
};

Maze::Maze(int n, int m) {
	m_width = m;
	m_height = n;
	m_field = new MCell[m * n];
}

Maze::~Maze() { delete[] m_field; }

const MCell& Maze::cell(int i, int j) const { 
	assert(i >= 0);
	assert(j >= 0);
	return m_field[i * m_width + j]; 
}

bool Maze::hasConnection(int i1, int j1, int i2, int j2) const {
	if ((abs(i1 - i2) + abs(j1 - j2) != 1)) return false;
	if (j2 < 0 || j2 >= m_width || i2 < 0 || i2 >= m_height)
		return false;
	const int ind1 = min(i1, i2);
	const int ind2 = min(j1, j2);
	if (i1 == i2) {
		return m_field[ind1 * m_width + ind2].right();
	}
	else if (j2 == j1) {
		return m_field[ind1 * m_width + ind2].down();
	}
	else
		return false;
}

bool Maze::makeConnection(int i1, int j1, int i2, int j2) {
	if ((abs(i1 - i2) + abs(j1 - j2) != 1)) return false;
	if (j2 < 0 || j2 >= m_width || i2 < 0 || i2 >= m_height)
		return false;
	int ind1 = min(i1, i2);
	int ind2 = min(j1, j2);
	if (i1 == i2) {
		m_field[ind1 * m_width + ind2].m_right = true;
		return true;
	}
	else if (j1 == j2) {
		m_field[ind1 * m_width + ind2].m_down = true;
		return true;
	}
	else
		return false;
}

bool Maze::removeConnection(int i1, int j1, int i2, int j2) {
	if ((abs(i1 - i2) + abs(j1 - j2) != 1)) return false;
	if (j2 < 0 || j2 >= m_width || i2 < 0 || i2 >= m_height)
		return false;
	int ind1 = min(i1, i2);
	int ind2 = min(j1, j2);
	if (i1 == i2) {
		bool res = m_field[ind1 * m_width + ind2].m_right;
		m_field[ind1 * m_width + ind2].m_right = false;
		return res;
	}
	else if (j2 == j1) {
		bool res = m_field[ind1 * m_width + ind2].m_down;
		m_field[ind1 * m_width + ind2].m_down = false;
		return res;
	}
	else
		return false;
}

void Maze::printMaze() const {
	for (int n = 0; n < m_width * m_height; ++n) {
		int i = n / m_width;
		int j = n % m_width;
		int res = m_field[n].down() << 2 | m_field[n].right() << 3;
		if (i - 1 >= 0)
			res += m_field[(i - 1) * m_width + j].down() << 0;
		if (j - 1 >= 0)
			res += m_field[i * m_width + j - 1].right() << 1;

		assert(typeid(m_dict.find(res)->second) == typeid(char));
		cout << m_dict.find(res)->second;

		if (j + 1 == m_width)
			cout << endl;
	}
}