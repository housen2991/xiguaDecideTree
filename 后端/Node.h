#pragma once
#include"mHead.h"
class Node {
protected:
	string attribute;//结点属性
	string leafType;//若为叶节点，判断节点类型：好|坏瓜
	double Value;
	vector<Node*> childNode;
	//map<string, Node*> linkChildNode;

public:
	Node();
	string getArr();
	string getleafType();
	~Node();
	friend class Tree;
};