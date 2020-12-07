#pragma once
#include <vector>
using namespace std;

class MTreeNode
{
private:
	int m_i, m_j;
	int m_distance;
	MTreeNode* m_parent;
	vector<MTreeNode*> m_children;
	MTreeNode(MTreeNode* parent);
public:
	~MTreeNode();
	int i() const;
	int j() const;
	int distance() const;
	int childCount() const;
	bool addChild(int i, int j);
	const MTreeNode* parent() const;
	MTreeNode* hasChild(int i, int j);
	const MTreeNode* child(int i) const;
	static MTreeNode begintTree(int i, int j);
};

