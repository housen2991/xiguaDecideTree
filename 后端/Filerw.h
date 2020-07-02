#pragma once
#include "mHead.h"
template <typename T>
vector<vector<T>> transpose(vector<vector<T>>& data);
vector<vector<string>> myReadFile(string filepath);
void MapGen(vector<vector<string>>& myData,
	map<string, vector<string>>& myMap, string filepath = "data.csv");
void WriteFile(vector<vector<string>>& myData, string filepath = "data.csv");
void WriteGain(vector<string>& headline, vector<double>& infoGains, string filepath = "Gain.txt");
vector<double> vStr2vDouble(vector<string>& vstr);