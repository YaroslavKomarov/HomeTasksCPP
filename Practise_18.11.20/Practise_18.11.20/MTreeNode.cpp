#include <algorithm>
#include <iostream>
#include <queue>
#include "MTreeNode.h"
using namespace std;

MTreeNode* MTreeNode::begintTree(int i, int j) {
	MTreeNode* node = new MTreeNode(nullptr);
	node->m_distance = 0;
	node->m_i = i;
	node->m_j = j;
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
	m_children[m_children.size() - 1]->m_distance = this->m_distance + 1;
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

MTreeNode* MTreeNode::searchNode(const MTreeNode& tree, const int i, const int j) {
	queue<MTreeNode*> nodes;
	MTreeNode* parent = tree.m_parent;
	if (parent) {
		if (parent->i() == i && parent->j() == j)
			return parent;
		while (true) {
			MTreeNode* temp = parent->m_parent;
			if (!temp) break;
			parent = temp;
		}
		while (true)
		{
			for (const auto child : parent->m_children) {
				nodes.push(child);
				if (child->i() == i && child->j() == j)
					return child;
			}
			if (nodes.size() == 0)
				break;
			parent = nodes.front();
			nodes.pop();
		}
	}
	else {
		for (const auto child : tree.m_children) {
			nodes.push(child);
			if (child->i() == i && child->j() == j)
				return child;
		}
	}
	return nullptr;
}