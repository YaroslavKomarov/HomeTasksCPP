#include <algorithm>
#include <iostream>
#include "MTreeNode.h"
using namespace std;

MTreeNode MTreeNode::begintTree(int i, int j) {
	MTreeNode node = MTreeNode(nullptr);
	node.m_distance = i + j;
	node.m_i = i;
	node.m_j = j;
	return node;
}

MTreeNode::MTreeNode(MTreeNode* parent) {
	m_parent = parent;
	m_distance = 0;
	m_i = 0;
	m_j = 0;
}

MTreeNode::~MTreeNode() {
	for (auto& ptr : m_children)
		delete ptr;
}

int MTreeNode::i() const { return m_i; }

int MTreeNode::j() const { return m_j; }

const MTreeNode* MTreeNode::parent() const { return m_parent; }

const MTreeNode* MTreeNode::child(int i) const { return m_children[i]; }

int MTreeNode::distance() const { return m_distance; }

int MTreeNode::childCount() const { return m_children.size(); }

bool MTreeNode::addChild(int i, int j) {
	if (abs(i - m_i + j - m_j) != 1)
		return false;
	m_children.push_back(new MTreeNode(this));
	m_children[m_children.size() - 1]->m_distance = i + j;
	m_children[m_children.size() - 1]->m_i = i;
	m_children[m_children.size() - 1]->m_j = j;
	return true;
}

MTreeNode* MTreeNode::hasChild(int i, int j) {
	int count = m_children.size();
	for (int ind = 0; ind < count; ++ind) {
		MTreeNode* child = m_children[ind];
		if (child->m_i == i && child->m_j == j)
			return child;
	}
	return nullptr;
}