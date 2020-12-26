#pragma once
#include <vector>
using namespace std;

class MTreeNode
{
public:
	~MTreeNode();
	int i() const { return m_i; }
	int j() const { return m_j; }
	int distance()  const { return m_distance; }
	int childCount() const { return m_children.size(); }
	bool addChild(int i, int j);
	const MTreeNode* parent() const { return m_parent; }
	MTreeNode* hasChild(int i, int j) const;
	const MTreeNode* child(int i) const { return m_children[i]; }
	static MTreeNode* begintTree(int i, int j);
	const MTreeNode* searchNode(const int i, const int j);
	const MTreeNode* searchRoot(const MTreeNode* node);
private:
	int m_i, m_j = 0;
	int m_distance = 0;
	MTreeNode* m_parent = nullptr;
	vector<MTreeNode*> m_children;
	MTreeNode(MTreeNode* parent);
};

