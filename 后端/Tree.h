#pragma once
#include "Node.h"
#include "Entrophy.h"
#include"Filerw.h"
#include "mHead.h"
class Tree {
public:
	Node* rootNode;//�����
	Node* temp;    //��ʱָ�룬����show����
	vector<string> usedAttribute;//��ʹ������
	Tree();
	~Tree();
	void deleteNode(Node* p);
	bool isLeaf(vector<string>& good, map<string, vector<string>>& attValue);  //�ж�����Ƿ�ΪҶ�ڵ�
	bool haveUsed(string attribute);//�жϵ�ǰ�����Ƿ���ʹ��
	void setLeafType(string &leaftype, vector<string>& good);//ȡ�����ж����Ϊ�ڵ����ͣ�ȫ�Ǻùϣ���ù�>=���ϣ���type=���ǡ�;
	string bestAtt(vector<vector<string>>& data, vector<string>& good, map<string, vector<string>>& attValue,vector<double>&value);//���Ż�������
	int AttRow(vector<vector<string>>& data, string attribute);//������ԭʼdata����������
	void show(Node* p, map<string, vector<string>>& attValue);//���������
	//���ɾ���������,����dataΪ������D��attValueΪ���Լ�A��������������ֵ����ӳ���ϵ�磺ɫ���࣬�ڣ��ң�good������������Ϣ
    Node* TreeGenerate(vector<vector<string>>& data, vector<string>& good, map<string, vector<string>>& attValue);
};
