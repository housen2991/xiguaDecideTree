#include "mHead.h"
class Watermelon
{
protected:
	string id;
	string color;
	string root;
	string sound;
	string line;
	string umbilicus;
	string touch;
	string quality;
	double density; //�ܶ�
	double sweet; //������
	static string c[3];
	static string r[3];//����
	static string s[3];
	static string li[3];//����
	static string um[3];//�겿
	static string t[2];

public:
	Watermelon();
	int getnum(int a, int b);//����һ��a~b֮�������,���ں����������Watermelon
	string getcolor();
	string getroot();
	string getsound();
	string getline();
	string getumbilicus();
	string gettouch();
	double getdensity();
	double getsweet();
	void show();  //�������
	void insert(); //��ֵ����
	friend vector<vector<string>> random_Generate(int n);//�����������Watermelon
	friend class sample;
};
