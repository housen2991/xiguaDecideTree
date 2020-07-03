#include "x_filerw.h"

/*
transpose(): use to transpose a 2D vector.
*/
template< typename T>
vector<vector<T>> transpose(vector<vector<T>>& data) {
    if (data.size() == (size_t)0) {
        return data;
    }
    vector<vector<T> > t(data[0].size(), vector<T>());
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[i].size(); j++) {
            t[j].push_back(data[i][j]);
        }
    }
    return t;
}
/*
myReadFile():open a csv file and return a transpoesd 2D vector.
*/
vector<vector<string>> myReadFile(string filepath) {
    fstream fst(filepath, ios::in);
    if (!fst.is_open()) {
        cerr << "File open failed.";
        exit(1);
    }
    vector<vector<string>> myData;
    string sline, stemp;
    vector<string> myRow;//use to push row
    while (!fst.eof()) {
        myRow.clear();
        getline(fst, sline);
        if (sline.empty()) {
            break;
        }
        stringstream ss(sline);
        while (getline(ss, stemp, ','))
        {
            myRow.push_back(stemp);
        }
        myData.push_back(myRow);
    }
    return transpose<string>(myData);//transpose myData,now row to col
}
/*
mapGen(): generate map from 2D vector.
*/
void MapGen(vector<vector<string>>& myData, map<string, vector<string>>& myMap) {

    vector<string> myCol;//use to push row
    for (int col = 1; col < myData.size(); col++) {
        myCol.clear();
        for (int i = 1; i < myData[0].size(); i++) {//check every row except 1st
            if (!count(myCol.begin(), myCol.end(), myData[col][i])) {
                myCol.push_back(myData[col][i]);
            }
        }
        myMap.insert(map<string, vector<string>>::value_type(myData[col][0], myCol));
    }
}
/*
WriteFile():write a 2D vector(not transposed) to csv file.
*/
void WriteFile(vector<vector<string>>& myData, string filepath) {
    //maybe write strings as numbers
    fstream fst(filepath, ios::out);
    if (!fst.is_open()) {
        cerr << "File writing failed.";
        exit(1);
    }
    for (int i = 0; i < myData.size(); i++) {
        for (int j = 0; j < myData[i].size(); j++) {
            fst << myData[i][j];
            if (j < myData[i].size() - 1) {
                fst << ',';
            }
        }
        fst << '\n';
    }
    fst.close();
}

void WriteGain(vector<string>& headline, vector<double>& infoGains, string filepath) {//输入表头和信息增益并输出到文件
    vector<vector<string>> myData;
    vector<string> temp;
    for (int i = 0; i < infoGains.size(); i++) {//headline是表头一整行，需要取除第一行
        temp.clear();
        temp.push_back(headline[i + 1.0]);
        temp.push_back(to_string(infoGains[i]));
        myData.push_back(temp);
    }
    ofstream fst(filepath, ios::app);
    if (!fst.is_open()) {
        cerr << "File writing failed.";
        exit(1);
    }
    for (int i = 0; i < myData.size(); i++) {
        for (int j = 0; j < myData[0].size(); j++) {
            fst << myData[i][j] << '\t';
        }
        fst << '\n';
    }
    fst << '\n';
    fst.close();
}//需要提供表头第一行transpose(data)[0]，根据表生成的infoGains，filepath默认为Gain.txt
//infoGains生成如下：（变量名myDoubleVec）
/*
vector <double> myDoubleVec;
for (int i = 0; i < myMap.size() - 3; i++) {//生成前几列的增益
    myDoubleVec.push_back(InfoGain(myVec[(1.0 + i)], myVec[myVec.size() - 1], myMap));
}
for (int i = myMap.size() - 3; i < myMap.size() - 1; i++) {//生成数字两列的增益
    vector<double> temp = vStr2vDouble(myVec[i + 1.0]);
    myDoubleVec.push_back(InfoGain(myVec[(i + 1.0)][0], temp, myVec[myVec.size() - 1], myMap));
}
WriteGain(transpose(myVec)[0], myDoubleVec);//调用函数
*/
vector<double> vStr2vDouble(vector<string>& vstr) {//vector<string>转vector<double>函数
    vector <double> vdouble;
    for (int i = 1; i < vstr.size(); i++) {
        vdouble.push_back(atof(vstr[i].c_str()));
    }
    return vdouble;
}
