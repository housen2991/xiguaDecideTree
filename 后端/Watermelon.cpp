#include"Watermelon.h"

//为静态数据成员赋值
string  Watermelon::c[3] = { "青绿","乌黑","浅白" };
string  Watermelon::s[3] = { "浊响","沉闷","清脆" };
string  Watermelon::r[3] = { "蜷缩","稍蜷","硬挺" };
string  Watermelon::li[3] = { "清晰","稍糊","模糊" };
string  Watermelon::um[3] = { "凹陷","稍凹","平坦" };
string  Watermelon::t[2] = { "硬滑","软黏" };

int Watermelon::getnum(int a, int b)
{
	return rand() % (b - a + 1) + a;
}
Watermelon::Watermelon()
{
	density = sweet = 0;
}
string Watermelon::getcolor() { return color; }
string Watermelon::getroot() { return root; }
string Watermelon::getsound() { return sound; }
string Watermelon::getline() { return line; }
string Watermelon::getumbilicus() { return umbilicus; }
string Watermelon::gettouch() { return touch; }
double Watermelon::getdensity()
{
	return density;
}
double Watermelon::getsweet()
{
	return sweet;
}

void  Watermelon::insert()//随机生成各属性值
{
	color = c[getnum(0, 2)];
	root = r[getnum(0, 2)];
	sound = s[getnum(0, 2)];
	line = li[getnum(0, 2)];
	umbilicus = um[getnum(0, 2)];
	touch = t[getnum(0, 1)];
	density = getnum(243, 774) / 1000.0;
	sweet = getnum(42, 460) / 1000.0;
}
void  Watermelon::show()
{
	cout << color << " " << root << " " << sound << " " << line << " " << umbilicus << " " << touch << " "
		<< density << " " << sweet << endl;
}//输出函数
vector<vector<string>> random_Generate(int n)
{
	Watermelon w;
	srand((unsigned)time(NULL));//设置随机数种子
	vector<vector<string>> vec;
	vector<string> vs;//存入行数据
	for (int i = 0; i < n; i++)
	{
		vs.clear();
		w.insert();//随机给w赋值
		w.id = i + 1;//给西瓜编号
		vs.push_back(w.color);
		vs.push_back(w.root);
		vs.push_back(w.sound);
		vs.push_back(w.line);
		vs.push_back(w.umbilicus);
		vs.push_back(w.touch);
		vs.push_back(to_string(w.getdensity()));
		vs.push_back(to_string(w.getsweet()));
		vec.push_back(vs);
	}
	return vec;
}