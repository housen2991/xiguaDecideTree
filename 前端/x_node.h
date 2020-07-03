#pragma once
#include"x_mhead.h"
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
    void show() {
        cout << "attribute:" << attribute << "\tleafType:" << leafType << "\tValue:" << Value << "\tchildeNode.size() :" << childNode.size() << endl;
    }
    ~Node();
    friend class Tree;
};
