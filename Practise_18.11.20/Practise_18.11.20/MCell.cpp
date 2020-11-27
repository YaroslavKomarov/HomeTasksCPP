#include "MCell.h"

MCell::MCell() {
	m_down = false;
	m_right = false;
}

bool MCell::down() const { return m_down; }

bool MCell::right() const { return m_right; }
