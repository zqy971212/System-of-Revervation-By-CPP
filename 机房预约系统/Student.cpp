#include "Student.h"

//Ĭ�Ϲ���
Student::Student()
{
}

//�вι���
Student::Student(int id, string name, string pwd)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;

	//��ʼ��������Ϣ
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom com;
	while (ifs>>com.m_ComId && ifs>>com.m_MaxNum)
	{
		vCom.push_back(com);
	}
	ifs.close();

}

//��ʾѧ�������Ĳ˵�����
void Student::openMenu()
{
	cout << "---------------------------��ӭ"<<this->m_Name<<"ͬѧ------------------------" << endl;
	cout << "\t\t-----------------------------------------" << endl;
	cout << "\t\t|                                       |" << endl;
	cout << "\t\t|            1.�� �� Ԥ  Լ             |" << endl;
	cout << "\t\t|                                       |" << endl;
	cout << "\t\t|            2.�鿴����ԤԼ             |" << endl;
	cout << "\t\t|                                       |" << endl;
	cout << "\t\t|            3.�鿴����ԤԼ             |" << endl;
	cout << "\t\t|                                       |" << endl;
	cout << "\t\t|            4.ȡ �� Ԥ  Լ             |" << endl;
	cout << "\t\t|                                       |" << endl;
	cout << "\t\t|            0.ע����¼                 |" << endl;
	cout << "\t\t|                                       |" << endl;
	cout << "\t\t-----------------------------------------" << endl;
}

//����ԤԼ
void Student::applyOrder()
{
	cout << "����������ԤԼ��ʱ�䣺" << endl;
	cout << "1����һ" << endl;
	cout << "2���ܶ�" << endl;
	cout << "3������" << endl;
	cout << "4������" << endl;
	cout << "5������" << endl;

	int date = 0;  //����
	int interval = 0;  //ʱ���
	int room = 0;  //�������
	
	while (true)
	{
		cin >> date;
		if (date>=1 && date<=5)
		{
			break;
		}
		cout << "������������������" << endl;
	}

	cout << "����������ԤԼʱ��Σ�" << endl;
	cout << "1������" << endl;
	cout << "2������" << endl;

	while (true)
	{
		cin >> interval;
		if (interval==1 || interval==2)
		{
			break;
		}
		cout << "��������ȷ��ʱ���" << endl;
	}

	cout << "��ѡ�����" << endl;
	for (int i = 0; i < vCom.size(); i++)
	{
		cout <<i+1<<"��"<< vCom[i].m_ComId << "�Ż�������Ϊ��" << vCom[i].m_MaxNum << endl;
	}

	while (true)
	{
		cin >> room;
		if (room>=1 && room<=3)
		{
			break;
		}
		cout << "��������ȷ�Ļ���" << endl;
	}

	cout << "ԤԼ�ɹ��������" << endl;

	ofstream ofs;
	ofs.open(ORDER_FILE, ios::out | ios::app);

	ofs << "date:" << date << " ";
	ofs << "Interval:" << interval << " ";
	ofs << "StuId:" << this->m_Id << " ";
	ofs << "StuName:" << this->m_Name << " ";
	ofs << "roomId:" << room << " ";
	ofs << "Status:" << 1 << endl;


	ofs.close();
	system("pause");
	system("cls");
}

//�鿴����ԤԼ
void Student::checkMyOrder()
{
	OrderFile of;
	if (of.m_Size==0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_Size; i++)
	{
		//string ת int
		//string���� .c_str() ת const char *
		//���� atoi תint
		if (this->m_Id==atoi( of.m_OrderDate[i]["StuId"].c_str()))  //�ҵ�����ԤԼ
		{
			cout << "ԤԼ���ڣ���" << of.m_OrderDate[i]["date"];
			cout << " ʱ��Σ�" << (of.m_OrderDate[i]["Interval"] == "1" ? "����" : "����");
			cout << " �����ţ�" << of.m_OrderDate[i]["roomId"];

			string status = "״̬��";
            //1 �����  2 ��ԤԼ  -1ԤԼʧ��  0 ȡ��ԤԼ
			if (of.m_OrderDate[i]["Status"]=="1")
			{
				status += "�����";
			}
			else if (of.m_OrderDate[i]["Status"]=="2")
			{
				status += "��ԤԼ";
			}
			else if (of.m_OrderDate[i]["Status"]=="-1")
			{
				status += "ԤԼʧ�ܣ����δͨ��";
			}
			else if (of.m_OrderDate[i]["Status"]=="0")
			{
				status += "ԤԼ��ȡ��";
			}
			cout << status;
			cout << endl;
		}
		else
		{
			cout << "δ�鵽�������ԤԼ��Ϣ" << endl;
			break;

		}
	}

	system("pause");
	system("cls");
}

//�鿴����ԤԼ
void Student::checkAllOrder()
{
	OrderFile of;

	if (of.m_Size==0)
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

//ȡ��ԤԼ
void Student::cancelOrder()
{
	OrderFile of;

	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "����л�ԤԼ�ɹ��ļ�¼����ȡ����������ȡ���ļ�¼" << endl;

	vector<int>v;  //�������������е��±���

	int index = 1;
	for (int i = 0; i < of.m_Size; i++)
	{
		//���ж�����ѧ��
		if (this->m_Id==atoi(of.m_OrderDate[i]["StuId"].c_str()))
		{
			//��ɸѡ״̬ ����л�ԤԼ�ɹ�
			if (of.m_OrderDate[i]["Status"]=="1" || of.m_OrderDate[i]["Status"]=="2")
			{
				v.push_back(i);
				cout << index++ << " ��";
				cout << "ԤԼ���ڣ���" << of.m_OrderDate[i]["date"];
				cout << " ʱ��Σ�" << (of.m_OrderDate[i]["Interval"] == "1" ? "����" : "����");
				cout << " ������ţ�" << of.m_OrderDate[i]["roomId"];

				string status = " ״̬��";

				if (of.m_OrderDate[i]["Status"]=="1")
				{
					status += "�����";
				}
				else if (of.m_OrderDate[i]["Status"]=="2")
				{
					status += "ԤԼ�ɹ�";
				}
				cout << status << endl;
			}
		}
	}

	cout << "������ȡ���ļ�¼,0������" << endl;
	int select;
	while (true)
	{
		cin >> select;

		if (select>=0 && select<=v.size())
		{
			if (select==0)
			{
				break;
			}
			else
			{
				of.m_OrderDate[v[select - 1]]["Status"] = "0";

				of.UpdateOrder();

				cout << "��ȡ��ԤԼ" << endl;
				break;
			}
		}

		cout << "������������������" << endl;
	}

	system("pause");
	system("cls");
}