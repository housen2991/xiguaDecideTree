#pragma once
#include "x_node.h"
#include "x_entrophy.h"
#include"x_filerw.h"
#include "x_mhead.h"
class Tree {
public:
    Node* rootNode;//根结点
    Node* temp;    //临时指针，用于show函数
    vector<string> usedAttribute;//已使用属性
    Tree();
    ~Tree();
    void deleteNode(Node* p);
    bool isLeaf(vector<string>& good, map<string, vector<string>>& attValue);  //判定结点是否为叶节点
    bool haveUsed(string attribute);//判断当前属性是否已使用
    void setLeafType(string &leaftype, vector<string>& good);//取样本中多的类为节点类型：全是好瓜，或好瓜>=坏瓜，则type=“是”;
    string bestAtt(vector<vector<string>>& data, vector<string>& good, map<string, vector<string>>& attValue,vector<double>&value);//最优划分属性
    int AttRow(vector<vector<string>>& data, string attribute);//属性在原始data中所在行数
    void show(Node* p, map<string, vector<string>>& attValue);//输出决策树
    //生成决策树函数,其中data为样本集D，attValue为属性集A，将属性与属性值建立映射关系如：色泽：青，黑，灰，good样本的质量信息
    Node* TreeGenerate(vector<vector<string>>& data, vector<string>& good, map<string, vector<string>>& attValue);
};
