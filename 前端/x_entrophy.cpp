#include "x_entrophy.h"
double Entrophy(double num, double len) {//calculate for last col
    if (len < num) {
        cerr << "Exit cause of entrophy calculation.";//？
        exit(2);
    }
    double tp = num / len;
    double tn = (len - num) / len;
    if (tp == 0)	swap(tp, tn);//保证tp>0
    return tn != 0.0 ? -(tp * log2(tp) + tn * log2(tn)) : -(tp * log2(tp));
}
//t1记录各属性信息熵,t2记录各属性下的样本个数
double ExpectEntro(vector<double>& t1, vector<double>& t2, double len) {//条件熵
    double t = 0;
    for (int i = 0; i < t1.size(); i++) {
        t += ExEntroSingle(t1[i], t2[i], len);
    }
    return t;
}
double ExEntroSingle(double d1, double d2, double len) {
    return d1 * d2 / len;//属性值的信息熵乘以权重求和得条件熵
}
double InfoGain(vector<string>& data, vector<string>& good, map<string, vector<string>>& attValue) {
    //对string类的处理
    vector<double> t1;//记录属性值的信息熵
    vector<double> t2;//记录各属性值的样本个数
    if (data.size() == 0 || good.size() == 0) {
        cerr << "Size = 0.";
        exit(1);
    }
    else if (data.size() != good.size()) {
        cerr << "Size not equal.";
        exit(1);
    }
    double l = (double)data.size() - 1;//长度
    for (int i = 0; i < attValue[data[0]].size(); i++) {//根据索引确定attValue的长度
        double n = (double)count(data.begin() + 1, data.end(), attValue[data[0]][i]);//n为属性值的样本数
        double y = 0;
        for (int j = 1; j < data.size(); j++) {
            if (data[j] == attValue[data[0]][i] && good[j] == "是") {
                y++;
            }
        }
        t1.push_back(Entrophy(y, n));//青绿等属性值的熵
        t2.push_back(n);//青绿等属性值的个数
    }
    double n = (double)data.size() - 1;//样本总数
    double y = count(good.begin() + 1, good.end(), "是");////样本中的好瓜个数
    return Entrophy(y, n) - ExpectEntro(t1, t2, l);
}
double InfoGain(string key, vector<double>& data, vector<string>& good, map<string, vector<string>> &attValue, double& value) {
    //对double类的处理，需要预先把vector<string>转成vector<double>，并提供key
    vector<double> t1;//记录属性值的信息增益
    vector<double> t2;//记录各属性值的样本个数（小于分割点的个数）
    vector<double> t3;//存储小于点的好瓜数
    double d = count(good.begin(), good.end(), "是");//记录好瓜数
    vector<double> vd;//存储二分点
    double l = (double)data.size();//长度
    vector<double>t = data;
    sort(t.begin(), t.end());//排序
    for (int i = 0; i < l - 1; i++) {
        vd.push_back((t[i] + t[i + 1.0]) / 2);//二分点
    }
    for (int i = 0; i < vd.size(); i++) {//记录t2,t3并计算t1
        t2.push_back(i + 1.0);//记录小于个数

        double temp = 0;
        for (int j = 1; j < good.size(); j++) {
            if (data[j - 1.0] < vd[i] && good[j] == "是") {
                temp++;
            }
        }
        t3.push_back(temp);//记录小于的好瓜数
    }
    for (int i = 0; i < vd.size(); i++) {
        double temp1 = Entrophy(t3[i], t2[i]);
        temp1 = ExEntroSingle(temp1, t2[i], l);
        double temp2 = Entrophy(d - t3[i], l - t2[i]);
        temp2 = ExEntroSingle(temp2, (l - t2[i]), l);
        t1.push_back(temp1 + temp2);
    }
    vector<double>::iterator it = min_element(t1.begin(), t1.end());//记录最小值的下标
    value = vd[it - t1.begin()];//存储二分点
    //map本身不参与运算，对其相应字段覆盖为是否
    attValue.erase(key);
    attValue.insert(map<string, vector<string>>::value_type(key, { "是","否" }));
    /*
    attValue.erase(key);
    vector<string> temp;
    temp.push_back(to_string(vd[it - t1.begin()]));//把相应的值改为string
    attValue.insert(map<string, vector<string>>::value_type(key, temp));//覆盖
    */
    //最后计算
    double n = (double)data.size() - 1;//样本总数
    double y = count(good.begin() + 1, good.end(), "是");////样本中的好瓜个数
    return Entrophy(y, n) - t1[it - t1.begin()];//返回最大
}
