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
	double density; //密度
	double sweet; //含糖率
	static string c[3];
	static string r[3];//根蒂
	static string s[3];
	static string li[3];//纹理
	static string um[3];//脐部
	static string t[2];

public:
	Watermelon();
	int getnum(int a, int b);//返回一个a~b之间的整数,用于后续生成随机Watermelon
	string getcolor();
	string getroot();
	string getsound();
	string getline();
	string getumbilicus();
	string gettouch();
	double getdensity();
	double getsweet();
	void show();  //输出函数
	void insert(); //赋值函数
	friend vector<vector<string>> random_Generate(int n);//随机生成若干Watermelon
	friend class sample;
};
