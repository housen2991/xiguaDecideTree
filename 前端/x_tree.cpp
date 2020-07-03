#include"x_tree.h"
Tree::Tree()
{
    rootNode = NULL;
    temp = NULL;
}
void Tree::deleteNode(Node* p)//递归delete各决策树结点
{
    if (p != NULL)
    {
        for (int i = 0; i < p->childNode.size(); i++)
        {
            Node* temp = p->childNode[i];
            if (temp->childNode.size() == 0)
            {
                delete temp;
            }
            else deleteNode(temp);
        }
        delete p;
    }
    return;
}
Tree::~Tree()
{
    deleteNode(rootNode);
}
void Tree::show(Node* p, map<string, vector<string>>& attValue)
{
    if (p != NULL)
    {
        cout << p->attribute;
        for (int i = 0; i < p->childNode.size(); i++)
        {
            if (p->attribute == "密度" || p->attribute == "含糖率")
            {
                if (attValue[p->attribute][i] == "是")
                    cout << "<=" << p->Value << "—" << attValue[p->attribute][i] << "→";
                else
                {
                    for (int j = 0; j < 2; j++)cout << "\t";
                    cout << ">" << p->Value << "—" << attValue[p->attribute][i] << "→";
                }
            }
            else
            {
                if (i > 0)cout << "    ";
                cout << "—" << attValue[p->attribute][i] << "→";
            }
            temp = p->childNode[i];
            if (temp->childNode.size() == 0)
            {
                if (i == 0 && p->attribute != " " && p->attribute != rootNode->childNode[0]->attribute)
                {
                    if (temp->leafType == "是")
                    {
                        cout << "好瓜" << endl;
                        cout << "\t    ";
                    }
                    else
                    {
                        cout << "坏瓜" << endl;
                        cout << "\t    ";
                    }
                }
                else {
                    if (temp->leafType == "是")
                        cout << "好瓜" << endl;
                    else
                        cout << "坏瓜" << endl;
                }
            }
            else	for (int j = 0; j < temp->childNode.size(); j++)
            {
                show(temp, attValue);
            }
        }
        return;
    }
    else cout << "生成树为空！" << endl;
}
bool Tree::isLeaf(vector<string>& good, map<string, vector<string>>& attValue)
{
    int j = 2;
    for (j; j < good.size(); j++)//D中样本于同一类别，必为叶结点
    {
        if (good[j] != good[1])
            break;
    }
    if (j >= good.size())        //j >= goodW.size()说明所有瓜的类别和goodW[1]相同
    {
        return 1;                   //结点为叶结点
    }
    else if (usedAttribute.size() == attValue.size() - 1)//全部属性已被使用，即A = 0 ，必为叶结点
    {
        return 1;
    }
    else return 0;
}
void Tree::setLeafType(string& leafType, vector<string>& good)
{
    int j = 0;
    for (int i = 1; i < good.size(); i++)
    {
        if (good[i] == "是")j++;    //统计好瓜个数
        if (i == good.size() - 1 && j >= (good.size() - 1) - j)//good.size() - 1为总数
        {
            leafType = "是";    //好瓜个数多，叶结点类型为：是
        }
        else if (i == good.size() - 1 && j < (good.size() - 1) - j)
        {
            leafType = "否";//坏瓜个数多，叶结点类型为：否
        }
    }
}
bool Tree::haveUsed(string attribute)
{
    int k = 0;
    for (k = 0; k < usedAttribute.size(); k++)
    {
        if (usedAttribute[k] == attribute)
            break;
    }
    if (k >= usedAttribute.size() || k == 0)//attribute未被使用
        return 0;
    else return 1;
}
string Tree::bestAtt(vector<vector<string>>& data, vector<string>& good, map<string, vector<string>>& attValue, vector<double>& value)
{
    ///cout << data[0].size() << " " << good.size() << endl;
    vector<double>Info;      //存放所有未使用属性增益（eg:0.345,....0.224)
    vector<string>att;       //存放Info增益对应的属性（eg:0.345->色泽...0.224->密度）
    vector<int>attRow;       //计录每个未被使用属性在原始data中所在的行坐标（色泽->行坐标为1...密度->行坐标为7）
    for (int i = 0; i < attValue.size() - 3; i++)//计算各非连续属性值信息增益
    {
        if (!haveUsed(data[i + 1.0][0]))     //若data[i + 1][0]未被使用
        {
            Info.push_back(InfoGain(data[i + 1.0], good, attValue));
            att.push_back(data[i + 1.0][0]);//记录Info[i]增益对应的属性att[i],便于后续确定最大增益的同时知道属性
            attRow.push_back(i + 1);      //计算每个未被使用属性在原始data中所在的行坐标
        }
    }
    for (int i = data.size() - 3; i < data.size() - 1; i++)//计算连续属性值信息增益
    {
        if (!haveUsed(data[i][0]))                      //data[i][0]未被使用
        {
            double v;
            vector<double>temp = vStr2vDouble(data[i]);//使用下面的函数需要将string转为double（eg:密度0.234在data中是string类型，将其转为double）
            Info.push_back(InfoGain(data[i][0], temp, good, attValue, v));
            att.push_back(data[i][0]);//记录Info[i]增益对应的属性att[i],便于后续确定最大增益的同时知道属性
            attRow.push_back(i);      //计算每个未被使用属性在原始data中所在的行坐标
            value.push_back(v);
        }
    }
    vector <string>temp;
    temp.clear();
    for (int i = 0; i < data.size(); i++) {
        temp.push_back(data[i][0]);
    }
    WriteGain(temp, Info);
    vector<double>::iterator it = max_element(Info.begin(), Info.end());//记录最大增益的下标
    usedAttribute.push_back(att[it - Info.begin()]);//记录已使用的属性
    if (att[it - Info.begin()] == "密度")
    {
        //cout << "最佳划分属性：" << att[it - Info.begin()] << "<=" << value[0] << " "<<usedAttribute.size() << endl;
        return att[it - Info.begin()];
    }
    else if (att[it - Info.begin()] == "含糖率")
    {
        //cout << "最佳划分属性：" << att[it - Info.begin()] << "<=" << value[1] << " " << usedAttribute.size() << endl;
        return att[it - Info.begin()];
    }
    else {
        //cout << "最佳划分属性：" << att[it - Info.begin()] << " " << usedAttribute.size() << endl;
        return att[it - Info.begin()];
    }
}
int Tree::AttRow(vector<vector<string>>& data, string attribute)
{
    for (int i = 1; i < data.size() - 1; i++)
    {
        if (data[i][0] == attribute)
            return i;
    }
    return 0;
}
Node* Tree::TreeGenerate(vector<vector<string>>& data, vector<string>& good, map<string, vector<string>>& attValue)
{
    Node* p = new Node;
    if (rootNode == NULL)
        rootNode = p;
    if (isLeaf(good, attValue))    //若为叶结点
    {
        setLeafType(p->leafType, good);  //设置叶结点类型（好瓜/坏瓜）
        return p;                   //退出函数
    }
    else//结点为根结点或子结点，
    {
        vector<double>value;//value计录连续属性值最大增益对应的二分点
        p->attribute = bestAtt(data, good, attValue, value);////将最优划分属性赋给p->attribute
        if (p->attribute == "密度" || p->attribute == "含糖率")
            cout << attValue[p->attribute].size() << " " << value[0] << " " << value[1] << endl;
        vector<string>cgood; // good存放子集childData的好瓜数据
        vector <vector<string>> childData;
        for (int i = 0; i < attValue[p->attribute].size(); i++)//按最优划分属性值（eg:青，黑，灰）生成分支结点
        {
            cgood.clear();//清空，便于下次循环使用
            childData.clear();//清空，便于下次循环使用
            int AttCol = AttRow(data, p->attribute);
            data = transpose<string>(data);
            childData.push_back(data[0]);
            cgood.push_back(data[0][data[0].size() - 1]);
            //先判断数据是否是double，然后分别生成
            for (int j = 1; j < data.size(); j++)//遍历所有西瓜数据，只保留该属性值（eg:青绿西瓜）数据生成子集childData
            {
                if (p->attribute == "密度")
                {
                    if (attValue[p->attribute][i] == "是" && atof(data[j][AttCol].c_str()) <= value[0])//若第j个西瓜为青绿
                    {
                        childData.push_back(data[j]);
                        cgood.push_back(data[j][data[j].size() - 1]);
                    }
                    else if (attValue[p->attribute][i] == "否" && atof(data[j][AttCol].c_str()) > value[0])
                    {
                        childData.push_back(data[j]);
                        cgood.push_back(data[j][data[j].size() - 1]);
                    }
                }
                else if (p->attribute == "含糖率")
                {
                    if (attValue[p->attribute][i] == "是" && atof(data[j][AttCol].c_str()) <= value[1])//若第j个西瓜为青绿
                    {
                        childData.push_back(data[j]);
                        cgood.push_back(data[j][data[j].size() - 1]);
                    }
                    else if (attValue[p->attribute][i] == "否" && atof(data[j][AttCol].c_str()) > value[1])
                    {
                        childData.push_back(data[j]);
                        cgood.push_back(data[j][data[j].size() - 1]);
                    }
                }
                else {
                    if (data[j][AttCol] == attValue[p->attribute][i])//若第j个西瓜为青绿
                    {
                        childData.push_back(data[j]);
                        cgood.push_back(data[j][data[j].size() - 1]);
                    }
                }
            }
            /*for (int k = 0; k < childData.size(); k++)   //检查各子集是否生成正确
            {
                for (int j = 0; j < childData[0].size(); j++)
                    cout << childData[k][j] << '\t';
                cout << endl;
            }*/
            data = transpose<string>(data);
            childData = transpose<string>(childData);
            if (childData[0].size() == 1)//子集childData为空则将子结点判为为叶结点
            {
                Node* lp = new Node;           //生成叶结点
                setLeafType(lp->leafType, good);  //子集childData为空，类别判为父集中多的那个（eg:好瓜）故此处应用good而不是cgood
                p->childNode.push_back(lp);//记录子结点地址
            }

            else //子集非空，继续生成子结点
            {
                if (p->attribute == "密度")
                    p->Value = value[0];
                else if (p->attribute == "含糖率")
                    p->Value = value[1];
                //cout << childData[0].size() << " " << cgood.size() << endl;

                p->childNode.push_back(TreeGenerate(childData, cgood, attValue));//生成分支结点，重复上述过程
            }
        }
        return p;//退出函数
    }
}
