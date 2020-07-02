#include "Tree.h"
using namespace std;

int main() {
	vector <vector<string> >myVec;
	map<string, vector<string>> myMap;
	MapGen(myVec, myMap);
	Tree myTree;
	for (map<string, vector<string> >::iterator ii = myMap.begin(); ii != myMap.end(); ++ii) {
		cout << (*ii).first << ": ";
		for (vector<string>::iterator iii = (*ii).second.begin(); iii != (*ii).second.end(); ++iii) {
			cout << *iii << ',';
		}
		cout << endl;
	}
	//myTree.rootNode = myTree.TreeGenerate(myVec, myVec[myVec.size() - 1.0], myMap);
	cout << "生成前";
	myTree.show(myTree.rootNode, myMap);
	myTree.TreeGenerate(myVec, myVec[myVec.size() - 1], myMap);

	cout << endl << "生成后" << endl;
	myTree.show(myTree.rootNode, myMap);
	/*vector <double> myDoubleVec;
	for (int i = 0; i < myMap.size() - 3; i++) {
		myDoubleVec.push_back(InfoGain(myVec[(1.0 + i)], myVec[myVec.size() - 1], myMap));
	}
	for (int i = myMap.size() - 3; i < myMap.size() - 1; i++) {
		vector<double> temp = vStr2vDouble(myVec[i + 1.0]);
		myDoubleVec.push_back(InfoGain(myVec[(i + 1.0)][0], temp, myVec[myVec.size() - 1], myMap));
	}*/
	//WriteGain(transpose(myVec)[0], myDoubleVec);
	/*
	for (map<string, vector<string> >::iterator ii = myMap.begin(); ii != myMap.end(); ++ii) {
		cout << (*ii).first << ": ";
		for (vector<string>::iterator iii = (*ii).second.begin(); iii != (*ii).second.end(); ++iii) {
			cout << *iii << ',';
		}
		cout << endl;
	}
	for (int i = 0; i < myDoubleVec.size(); i++) {
		cout << myDoubleVec[i] << ',';
	}
	cout << endl;
	for (int i = 0; i < myVec.size(); i++) {
		for (int j = 0; j < myVec[i].size(); j++) {
			cout << myVec[i][j] << '\t';
		}
		cout << endl;
	}
	*/
}