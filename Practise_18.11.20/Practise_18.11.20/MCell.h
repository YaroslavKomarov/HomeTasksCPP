#pragma once

class MCell {
private:
	MCell();
	bool m_down;
	bool m_right;
public:
	bool down() const;
	bool right() const;
	friend class Maze;
};
