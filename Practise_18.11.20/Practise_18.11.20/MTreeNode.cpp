#include <algorithm>
#include <iostream>
#include <queue>
#include "MTreeNode.h"
using namespace std;

MTreeNode* MTreeNode::begintTree(int i, int j) {
	MTreeNode* node = new MTreeNode(nullptr);
	node->m_i = i;
	node->m_j = j;
	return node;
}

MTreeNode::MTreeNode(MTreeNode* parent) {
	m_parent = parent;
	if (parent) m_distance = parent->m_distance + 1;
}

MTreeNode::~MTreeNode() {
	for (auto ptr : m_children)
		delete ptr;
}

bool MTreeNode::addChild(int i, int j) {
	if (abs(i - m_i + j - m_j) != 1)
		return false;

	for (auto &child : m_children)
		if (child->m_i == i && child->m_j == j)
			return false;
	m_children.push_back(new MTreeNode(this));
	m_children.back()->m_i = i;
	m_children.back()->m_j = j;
	return true;
}

MTreeNode* MTreeNode::hasChild(int i, int j) const{
	for (auto &child : m_children){
		if (child->m_i == i && child->m_j == j)
			return child;
	}
	return nullptr;
}

//Метод, реализующий поиск узла в дереве начиная от корня
const MTreeNode* MTreeNode::searchNode(const int i, const int j) {
	queue<MTreeNode*> nodes;
	auto node = searchRoot(this);
	while (true)
	{
		if (node->m_i == i && node->m_j == j) return node;
		for (const auto child : node->m_children) {
			if (child->i() == i && child->j() == j)
				return child;
			nodes.push(child);
		}
		if (nodes.size() == 0)
			break;
		node = nodes.front();
		nodes.pop();
	}
}

//Метод поиска корня в дерве
const MTreeNode* MTreeNode::searchRoot(const MTreeNode* node) {
	queue<MTreeNode*> nodes;
	MTreeNode* parent = node->m_parent;
	if (!parent) 
		return node; 
	else {
		while (true) {
			MTreeNode* temp = parent->m_parent;
			if (!temp) break;
			parent = temp;
		}
		return parent;
	}
}