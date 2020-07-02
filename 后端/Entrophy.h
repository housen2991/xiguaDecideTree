#pragma once
//using ID3
#include "mHead.h"
double Entrophy(double num, double len);
double ExpectEntro(vector<double>& t1, vector<double>& t2, double len);
//vector<double> InfoGains(vector<vector<string>>& data, map<string, vector<string>> attValue);
double ExEntroSingle(double d1, double d2, double len);

double InfoGain(vector<string>& data, vector<string>& good, map<string, vector<string>>& attValue);
double InfoGain(string key, vector<double>& data, vector<string>& good, map<string, vector<string>>& attValue, double& value);
//����infogain�����أ�ģ�崦������̫�鷳������ֻ��double��string����
//dataΪ�������ݣ�����������ǵ��У���goodΪ�û�һ�У�attValueΪ��Ҫ�ṩ��map
//keyΪ��Ҫ�ṩ�ı�ͷ�����������Ͼ�double��û�ַ���
//�����Զ���ȡdata�ı�ͷ��������attValue�б�����Ӧ��ֵ��ͳ�ƺ������Ϣ����
//���һ����ʹ��Entrophy()���н��

//ת��vector<string>��vector<double>����ȥ��ͷ