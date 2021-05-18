#include "Teacher.h"

//Ĭ�Ϲ���
Teacher::Teacher()
{
}

//�вι���
Teacher::Teacher(int id, string name, string pwd)
{
	this->m_MmpId = id;
	this->m_Name = name;
	this->m_Pwd = pwd;
}

//��ʾ��ʦ�����Ĳ˵�
void Teacher::openMenu()
{
	cout << "---------------------------��ӭ" << this->m_Name << "��ʦ------------------------" << endl;
	cout << "\t\t-----------------------------------------" << endl;
	cout << "\t\t|                                       |" << endl;
	cout << "\t\t|            1.�鿴����ԤԼ             |" << endl;
	cout << "\t\t|                                       |" << endl;
	cout << "\t\t|            2.�� �� Ԥ  Լ             |" << endl;
	cout << "\t\t|                                       |" << endl;
	cout << "\t\t|            0.ע �� �� ¼              |" << endl;
	cout << "\t\t|                                       |" << endl;
	cout << "\t\t-----------------------------------------" << endl;
}

//�鿴����ԤԼ
void Teacher::checkOrder()
{
	OrderFile of;

	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}

	of.ShowOrder();

	system("pause");
	system("cls");
}

//���ԤԼ
void Teacher::vaildOrder()
{
	OrderFile of;
	if (of.m_Size==0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}

	vector<int>v;
	int index = 1;
	cout << "����˵�ԤԼ��¼���£�" << endl;

	for (int i = 0; i < of.m_Size; i++)
	{
		//����е�����
		if (of.m_OrderDate[i]["Status"]=="1")
		{
			v.push_back(i);
			cout << index++ << " ��";
			cout << "ԤԼ���ڣ���" << of.m_OrderDate[i]["date"];
			cout << " ʱ��Σ�" << (of.m_OrderDate[i]["Interval"] == "1" ? "����" : "����");
			cout << " ѧ�ţ�" << of.m_OrderDate[i]["StuId"];
			cout << " ������" << of.m_OrderDate[i]["StuName"];
			cout << " ������ţ�" << of.m_OrderDate[i]["roomId"];
			cout << " ״̬�������" << endl;
		}
	}

	cout << "��������˵�ԤԼ��¼��0������" << endl;
	int select;  
	int ret;  //����ԤԼ�����¼

	while (true)
	{
		cin >> select;
		if (select==0)
		{
			break;
		}
		else if (select>0 && select<=v.size())
		{
			cout << "��������˽��" << endl;
			cout << "1��ͨ��" << endl;
			cout << "2����ͨ��" << endl;
			cin >> ret;
			if (ret==1)
			{
				//ͨ��
				of.m_OrderDate[v[select - 1]]["Status"] = "2";
			}
			else
			{
				//��ͨ��
				of.m_OrderDate[v[select - 1]]["Status"] = "-1";
			}
			of.UpdateOrder();
			cout << "������" << endl;
			break;
		}
		cout << "������������������" << endl;
	}

	system("pause");
	system("cls");

}