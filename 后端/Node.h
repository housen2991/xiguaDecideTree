#pragma once
#include"mHead.h"
class Node {
protected:
	string attribute;//�������
	string leafType;//��ΪҶ�ڵ㣬�жϽڵ����ͣ���|����
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