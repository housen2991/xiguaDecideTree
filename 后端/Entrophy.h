#pragma once
//using ID3
#include "mHead.h"
double Entrophy(double num, double len);
double ExpectEntro(vector<double>& t1, vector<double>& t2, double len);
//vector<double> InfoGains(vector<vector<string>>& data, map<string, vector<string>> attValue);
double ExEntroSingle(double d1, double d2, double len);

double InfoGain(vector<string>& data, vector<string>& good, map<string, vector<string>>& attValue);
double InfoGain(string key, vector<double>& data, vector<string>& good, map<string, vector<string>>& attValue, double& value);
//对于infogain的重载，模板处理起来太麻烦了所以只对double和string适用
//data为单列数据（按常理理解是单行），good为好坏一列，attValue为需要提供的map
//key为需要提供的表头（索引），毕竟double里没字符串
//程序自动获取data的表头，并且在attValue中遍历对应的值，统计后计算信息增益
//最后一列请使用Entrophy()进行解决

//转换vector<string>到vector<double>并抛去表头