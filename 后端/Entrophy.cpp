#include "Entrophy.h"
double Entrophy(double num, double len) {//calculate for last col
	if (len < num) {
		cerr << "Exit cause of entrophy calculation.";//��
		exit(2);
	}
	double tp = num / len;
	double tn = (len - num) / len;
	if (tp == 0)	swap(tp, tn);//��֤tp>0
	return tn != 0.0 ? -(tp * log2(tp) + tn * log2(tn)) : -(tp * log2(tp));
}
//t1��¼��������Ϣ��,t2��¼�������µ���������
double ExpectEntro(vector<double>& t1, vector<double>& t2, double len) {//������
	double t = 0;
	for (int i = 0; i < t1.size(); i++) {
		t += ExEntroSingle(t1[i], t2[i], len);
	}
	return t;
}
double ExEntroSingle(double d1, double d2, double len) {
	return d1 * d2 / len;//����ֵ����Ϣ�س���Ȩ����͵�������
}
double InfoGain(vector<string>& data, vector<string>& good, map<string, vector<string>>& attValue) {
	//��string��Ĵ���
	vector<double> t1;//��¼����ֵ����Ϣ��
	vector<double> t2;//��¼������ֵ����������
	if (data.size() == 0 || good.size() == 0) {
		cerr << "Size = 0.";
		exit(1);
	}
	else if (data.size() != good.size()) {
		cerr << "Size not equal.";
		exit(1);
	}
	double l = (double)data.size() - 1;//����
	for (int i = 0; i < attValue[data[0]].size(); i++) {//��������ȷ��attValue�ĳ���
		double n = (double)count(data.begin() + 1, data.end(), attValue[data[0]][i]);//nΪ����ֵ��������
		double y = 0;
		for (int j = 1; j < data.size(); j++) {
			if (data[j] == attValue[data[0]][i] && good[j] == "��") {
				y++;
			}
		}
		t1.push_back(Entrophy(y, n));//���̵�����ֵ����
		t2.push_back(n);//���̵�����ֵ�ĸ���
	}
	double n = (double)data.size() - 1;//��������
	double y = count(good.begin() + 1, good.end(), "��");////�����еĺùϸ���
	return Entrophy(y, n) - ExpectEntro(t1, t2, l);
}
double InfoGain(string key, vector<double>& data, vector<string>& good, map<string, vector<string>> &attValue, double& value) {
	//��double��Ĵ�����ҪԤ�Ȱ�vector<string>ת��vector<double>�����ṩkey
	vector<double> t1;//��¼����ֵ����Ϣ����
	vector<double> t2;//��¼������ֵ������������С�ڷָ��ĸ�����
	vector<double> t3;//�洢С�ڵ�ĺù���
	double d = count(good.begin(), good.end(), "��");//��¼�ù���
	vector<double> vd;//�洢���ֵ�
	double l = (double)data.size();//����
	vector<double>t = data;
	sort(t.begin(), t.end());//����
	for (int i = 0; i < l - 1; i++) {
		vd.push_back((t[i] + t[i + 1.0]) / 2);//���ֵ�
	}
	for (int i = 0; i < vd.size(); i++) {//��¼t2,t3������t1
		t2.push_back(i + 1.0);//��¼С�ڸ���

		double temp = 0;
		for (int j = 1; j < good.size(); j++) {
			if (data[j - 1.0] < vd[i] && good[j] == "��") {
				temp++;
			}
		}
		t3.push_back(temp);//��¼С�ڵĺù���
	}
	for (int i = 0; i < vd.size(); i++) {
		double temp1 = Entrophy(t3[i], t2[i]);
		temp1 = ExEntroSingle(temp1, t2[i], l);
		double temp2 = Entrophy(d - t3[i], l - t2[i]);
		temp2 = ExEntroSingle(temp2, (l - t2[i]), l);
		t1.push_back(temp1 + temp2);
	}
	vector<double>::iterator it = min_element(t1.begin(), t1.end());//��¼��Сֵ���±�
	value = vd[it - t1.begin()];//�洢���ֵ�
	//map�����������㣬������Ӧ�ֶθ���Ϊ�Ƿ�
	attValue.erase(key);
	attValue.insert(map<string, vector<string>>::value_type(key, { "��","��" }));
	/*
	attValue.erase(key);
	vector<string> temp;
	temp.push_back(to_string(vd[it - t1.begin()]));//����Ӧ��ֵ��Ϊstring
	attValue.insert(map<string, vector<string>>::value_type(key, temp));//����
	*/
	//������
	double n = (double)data.size() - 1;//��������
	double y = count(good.begin() + 1, good.end(), "��");////�����еĺùϸ���
	return Entrophy(y, n) - t1[it - t1.begin()];//�������
}