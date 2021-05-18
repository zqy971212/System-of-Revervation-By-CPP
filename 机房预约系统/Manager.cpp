#include "manager.h"
#include <fstream>
#include "globalFile.h"


//Ĭ�Ϲ���
Manager::Manager()
{
}

//�вι���
Manager::Manager(string name, string pwd)
{
	this->m_Name = name;
	this->m_Pwd = pwd;

	//��ʼ������������ȡ�ļ������Ե���Ϣ
	this->initVector();

	//��ʼ��������Ϣ
	vCom.clear();
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom com;
	//������д�뵽������
	while (ifs>> com.m_ComId && ifs>>com.m_MaxNum	)
	{
		this->vCom.push_back(com);
	}
	ifs.close();

	//cout << "����������Ϊ��" << vCom.size() << endl;
}

//��ʾ����Ա��������
void Manager::openMenu()
{
	cout << "---------------------------��ӭ����Ա��------------------------" << endl;
	cout << "\t\t-------------------------------------" << endl;
	cout << "\t\t|                                   |" << endl;
	cout << "\t\t|            1.����˺�             |" << endl;
	cout << "\t\t|                                   |" << endl;
	cout << "\t\t|            2.�鿴�˺�             |" << endl;
	cout << "\t\t|                                   |" << endl;
	cout << "\t\t|            3.�鿴����             |" << endl;
	cout << "\t\t|                                   |" << endl;
	cout << "\t\t|            4.���ԤԼ             |" << endl;
	cout << "\t\t|                                   |" << endl;
	cout << "\t\t|            0.ע����¼             |" << endl;
	cout << "\t\t|                                   |" << endl;
	cout << "\t\t-------------------------------------" << endl;
}

//����˺�
void Manager::addAccount()
{
	string fileName;  //�������ļ���
	string tIp;  //��ʾ��ID��  ��ʦ/ѧ��
	string errorTip;

	int select;

	while (true)
	{
		cout << "��������ӵ��˺�����" << endl;
		cout << "1��ѧ��" << endl;
		cout << "2����ʦ" << endl;
		cin >> select;
		if (select == 1)
		{
			//���ѧ��
			fileName = STUDENT_FILE;
			tIp = "������ѧ��:";
			errorTip = "ѧ���ظ�������������";
			break;
		}
		else if (select == 2)
		{
			fileName = TEACHER_FILE;
			tIp = "������̹���:";
			errorTip = "�̹����ظ�������������";
			break;
		}
		cout << "��������ȷ��ѡ��" << endl;
	}

	ofstream ofs;
	string name;  //����
	string pwd;   //����
	int id;   //id

	cout << tIp << endl;  //����ѧ��/�̹��ŵ���ʾ
	while (true)
	{
		cin >> id;
		//���ID�Ƿ��ظ�
		bool ret = this->CheckRepeat(id, select);
		if (ret)
		{
			cout << errorTip << endl;
		}
		else
		{
			break;
		}
	}

	//����׷�ӵķ�ʽд��
	ofs.open(fileName, ios::out | ios::app);

	cout << "����������������" << endl;
	cin >> name;

	cout << "�������������룺" << endl;
	cin >> pwd;

	//д���ļ�
	ofs << id << " " << name << " " << pwd <<endl;
	cout << "��ӳɹ�" << endl;

	//������������ֹ�ظ�����
	this->initVector();

	system("pause");
	system("cls");

	//�ر��ļ�
	ofs.close();
}

//�º���  ��ӡѧ��
class PrintStu
{
public:
	void operator()(Student s1)
	{
		cout << "ѧ�ţ�" << s1.m_Id << " ������" << s1.m_Name<<" ���룺"<<s1.m_Pwd;
		cout << endl;
	}
};
//�º��� ��ӡ��ʦ
class PrintTea
{
public:
	void operator()(Teacher t1)
	{
		cout << "�̹���ţ�" << t1.m_MmpId << " ������" << t1.m_Name << " ���룺" << t1.m_Pwd;
		cout << endl;
	}
};

//�鿴�˺�
void Manager::checkAccount()
{
	cout << "��ѡ��鿴���ݣ�" << endl;
	cout << "1���鿴���е�ѧ��" << endl;
	cout << "2���鿴���е���ʦ" << endl;

	int select;
	while (true)
	{
		cin >> select;
		if (select == 1)
		{
			//�鿴ѧ��
			for_each(vStu.begin(), vStu.end(), PrintStu());

			break;
		}
		else if (select == 2)
		{
			//�鿴��ʦ
			for_each(vTea.begin(), vTea.end(), PrintTea());

			break;
		}
		else
		{
			cout << "��������ȷ��ѡ��" << endl;
		}
	}
	system("pause");
	system("cls");

}

//�鿴������Ϣ�ķº���
class PrintComputer
{
public:
	void operator ()(ComputerRoom com)
	{
		cout << "����ID:" << com.m_ComId << " ���������" << com.m_MaxNum;
		cout << endl;
	}
};

//�鿴������Ϣ
void Manager::checkInfo()
{
	cout << "������Ϣ���£�" << endl;
	for_each(vCom.begin(), vCom.end(), PrintComputer());

	system("pause");
	system("cls");
}

//���ԤԼ��¼
void Manager::clearFile()
{
	cout << "ȷ��Ҫ���ԤԼ��Ϣ��" << endl;
	cout << "1����" << endl;
	cout << "2����" << endl;
	int choice;
	cin >> choice;
	if (choice!=1)
	{
		system("pause");
		system("cls");
		return;
	}
	ofstream ofs;
	//����trunc����ļ�
	ofs.open(ORDER_FILE, ios::trunc);
	ofs.close();

	cout << "��ճɹ���" << endl;
	system("pause");
	system("cls");
}

//��ʼ������
void Manager::initVector()
{
	//ȷ���������
	vStu.clear();
	vTea.clear();

	ifstream ifs;
	//��ȡѧ����Ϣ
	ifs.open(STUDENT_FILE, ios::in);

	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ��" << endl;
		return;
	}

	//��ȡѧ����Ϣ������vStu������
	Student s;
	while (ifs>>s.m_Id && ifs>>s.m_Name && ifs>>s.m_Pwd)
	{
		vStu.push_back(s);
	}
	ifs.close();
	//cout << "ѧ��������Ϊ" << vStu.size() << endl;  ����

	//��ȡ��ʦ��Ϣ

	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ��" << endl;
		return;
	}

	//����ʦ��Ϣ�洢��vTea������
	Teacher t;
	while (ifs>>t.m_MmpId && ifs>>t.m_Name && ifs>>t.m_Pwd)
	{
		vTea.push_back(t);
	}
	ifs.close();
	//cout << "��ʦ������Ϊ" << vTea.size() << endl;  ����
}

//ȥ�ز���
bool Manager::CheckRepeat(int id, int type)   //id:�����ID��type��������
{
	if (type==1)
	{
		//���ѧ��
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			if (id==it->m_Id)
			{
				return true;
			}
		}
	}
	else
	{
		//�����ʦ
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			if (id==it->m_MmpId)
			{
				return true;
			}
		}
	}
	return false;
}