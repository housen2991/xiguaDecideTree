#include"Tree.h"
Tree::Tree()
{
	rootNode = NULL;
	temp = NULL;
}
void Tree::deleteNode(Node* p)//�ݹ�delete�����������
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
			if (p->attribute == "�ܶ�" || p->attribute == "������")
			{
				if (attValue[p->attribute][i] == "��")
					cout << "<=" << p->Value << "��" << attValue[p->attribute][i] << "��";
				else
				{
					for (int j = 0; j < 2; j++)cout << "\t";
					cout << ">" << p->Value << "��" << attValue[p->attribute][i] << "��";
				}
			}
			else
			{
				if (i > 0)cout << "    ";
				cout << "��" << attValue[p->attribute][i] << "��";
			}
			temp = p->childNode[i];
			if (temp->childNode.size() == 0)
			{
				if (i == 0 && p->attribute != " " && p->attribute != rootNode->childNode[0]->attribute)
				{
					if (temp->leafType == "��")
					{
						cout << "�ù�" << endl;
						cout << "\t    ";
					}
					else
					{
						cout << "����" << endl;
						cout << "\t    ";
					}
				}
				else {
					if (temp->leafType == "��")
						cout << "�ù�" << endl;
					else
						cout << "����" << endl;
				}
			}
			else	for (int j = 0; j < temp->childNode.size(); j++)
			{
				show(temp, attValue);
			}
		}
		return;
	}
	else cout << "������Ϊ�գ�" << endl;
}
bool Tree::isLeaf(vector<string>& good, map<string, vector<string>>& attValue)
{
	int j = 2;
	for (j; j < good.size(); j++)//D��������ͬһ��𣬱�ΪҶ���
	{
		if (good[j] != good[1])
			break;
	}
	if (j >= good.size())        //j >= goodW.size()˵�����йϵ�����goodW[1]��ͬ
	{
		return 1;                   //���ΪҶ���
	}
	else if (usedAttribute.size() == attValue.size() - 1)//ȫ�������ѱ�ʹ�ã���A = 0 ����ΪҶ���
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
		if (good[i] == "��")j++;    //ͳ�ƺùϸ���
		if (i == good.size() - 1 && j >= (good.size() - 1) - j)//good.size() - 1Ϊ����
		{
			leafType = "��";    //�ùϸ����࣬Ҷ�������Ϊ����
		}
		else if (i == good.size() - 1 && j < (good.size() - 1) - j)
		{
			leafType = "��";//���ϸ����࣬Ҷ�������Ϊ����
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
	if (k >= usedAttribute.size() || k == 0)//attributeδ��ʹ��
		return 0;
	else return 1;
}
string Tree::bestAtt(vector<vector<string>>& data, vector<string>& good, map<string, vector<string>>& attValue, vector<double>& value)
{
	///cout << data[0].size() << " " << good.size() << endl;
	vector<double>Info;      //�������δʹ���������棨eg:0.345,....0.224)
	vector<string>att;       //���Info�����Ӧ�����ԣ�eg:0.345->ɫ��...0.224->�ܶȣ�
	vector<int>attRow;       //��¼ÿ��δ��ʹ��������ԭʼdata�����ڵ������꣨ɫ��->������Ϊ1...�ܶ�->������Ϊ7��
	for (int i = 0; i < attValue.size() - 3; i++)//���������������ֵ��Ϣ����
	{
		if (!haveUsed(data[i + 1.0][0]))     //��data[i + 1][0]δ��ʹ��
		{
			Info.push_back(InfoGain(data[i + 1.0], good, attValue));
			att.push_back(data[i + 1.0][0]);//��¼Info[i]�����Ӧ������att[i],���ں���ȷ����������ͬʱ֪������
			attRow.push_back(i + 1);      //����ÿ��δ��ʹ��������ԭʼdata�����ڵ�������
		}
	}
	for (int i = data.size() - 3; i < data.size() - 1; i++)//������������ֵ��Ϣ����
	{
		if (!haveUsed(data[i][0]))                      //data[i][0]δ��ʹ��
		{
			double v;
			vector<double>temp = vStr2vDouble(data[i]);//ʹ������ĺ�����Ҫ��stringתΪdouble��eg:�ܶ�0.234��data����string���ͣ�����תΪdouble��
			Info.push_back(InfoGain(data[i][0], temp, good, attValue, v));
			att.push_back(data[i][0]);//��¼Info[i]�����Ӧ������att[i],���ں���ȷ����������ͬʱ֪������
			attRow.push_back(i);      //����ÿ��δ��ʹ��������ԭʼdata�����ڵ�������
			value.push_back(v);
		}
	}
	vector <string>temp;
	temp.clear();
	for (int i = 0; i < data.size(); i++) {
		temp.push_back(data[i][0]);
	}
	WriteGain(temp, Info);
	vector<double>::iterator it = max_element(Info.begin(), Info.end());//��¼���������±�
	usedAttribute.push_back(att[it - Info.begin()]);//��¼��ʹ�õ�����
	if (att[it - Info.begin()] == "�ܶ�")
	{
		//cout << "��ѻ������ԣ�" << att[it - Info.begin()] << "<=" << value[0] << " "<<usedAttribute.size() << endl;
		return att[it - Info.begin()];
	}
	else if (att[it - Info.begin()] == "������")
	{
		//cout << "��ѻ������ԣ�" << att[it - Info.begin()] << "<=" << value[1] << " " << usedAttribute.size() << endl;
		return att[it - Info.begin()];
	}
	else {
		//cout << "��ѻ������ԣ�" << att[it - Info.begin()] << " " << usedAttribute.size() << endl;
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
	if (isLeaf(good, attValue))    //��ΪҶ���
	{
		setLeafType(p->leafType, good);  //����Ҷ������ͣ��ù�/���ϣ�
		return p;                   //�˳�����
	}
	else//���Ϊ�������ӽ�㣬
	{
		vector<double>value;//value��¼��������ֵ��������Ӧ�Ķ��ֵ�
		p->attribute = bestAtt(data, good, attValue, value);////�����Ż������Ը���p->attribute
		if (p->attribute == "�ܶ�" || p->attribute == "������")
			cout << attValue[p->attribute].size() << " " << value[0] << " " << value[1] << endl;
		vector<string>cgood; // good����Ӽ�childData�ĺù�����
		vector <vector<string>> childData;
		for (int i = 0; i < attValue[p->attribute].size(); i++)//�����Ż�������ֵ��eg:�࣬�ڣ��ң����ɷ�֧���
		{
			cgood.clear();//��գ������´�ѭ��ʹ��
			childData.clear();//��գ������´�ѭ��ʹ��
			int AttCol = AttRow(data, p->attribute);
			data = transpose<string>(data);
			childData.push_back(data[0]);
			cgood.push_back(data[0][data[0].size() - 1]);
			//���ж������Ƿ���double��Ȼ��ֱ�����
			for (int j = 1; j < data.size(); j++)//���������������ݣ�ֻ����������ֵ��eg:�������ϣ����������Ӽ�childData
			{
				if (p->attribute == "�ܶ�")
				{
					if (attValue[p->attribute][i] == "��" && atof(data[j][AttCol].c_str()) <= value[0])//����j������Ϊ����
					{
						childData.push_back(data[j]);
						cgood.push_back(data[j][data[j].size() - 1]);
					}
					else if (attValue[p->attribute][i] == "��" && atof(data[j][AttCol].c_str()) > value[0])
					{
						childData.push_back(data[j]);
						cgood.push_back(data[j][data[j].size() - 1]);
					}
				}
				else if (p->attribute == "������")
				{
					if (attValue[p->attribute][i] == "��" && atof(data[j][AttCol].c_str()) <= value[1])//����j������Ϊ����
					{
						childData.push_back(data[j]);
						cgood.push_back(data[j][data[j].size() - 1]);
					}
					else if (attValue[p->attribute][i] == "��" && atof(data[j][AttCol].c_str()) > value[1])
					{
						childData.push_back(data[j]);
						cgood.push_back(data[j][data[j].size() - 1]);
					}
				}
				else {
					if (data[j][AttCol] == attValue[p->attribute][i])//����j������Ϊ����
					{
						childData.push_back(data[j]);
						cgood.push_back(data[j][data[j].size() - 1]);
					}
				}
			}
			/*for (int k = 0; k < childData.size(); k++)   //�����Ӽ��Ƿ�������ȷ
			{
				for (int j = 0; j < childData[0].size(); j++)
					cout << childData[k][j] << '\t';
				cout << endl;
			}*/
			data = transpose<string>(data);
			childData = transpose<string>(childData);
			if (childData[0].size() == 1)//�Ӽ�childDataΪ�����ӽ����ΪΪҶ���
			{
				Node* lp = new Node;           //����Ҷ���
				setLeafType(lp->leafType, good);  //�Ӽ�childDataΪ�գ������Ϊ�����ж���Ǹ���eg:�ùϣ��ʴ˴�Ӧ��good������cgood
				p->childNode.push_back(lp);//��¼�ӽ���ַ
			}

			else //�Ӽ��ǿգ����������ӽ��
			{
				if (p->attribute == "�ܶ�")
					p->Value = value[0];
				else if (p->attribute == "������")
					p->Value = value[1];
				//cout << childData[0].size() << " " << cgood.size() << endl;

				p->childNode.push_back(TreeGenerate(childData, cgood, attValue));//���ɷ�֧��㣬�ظ���������
			}
		}
		return p;//�˳�����
	}
}