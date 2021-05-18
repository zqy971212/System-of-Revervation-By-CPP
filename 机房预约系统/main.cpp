#include <iostream>
using namespace std;
#include "identity.h"
#include <fstream>
#include "globalFile.h"
#include "Student.h"
#include "Teacher.h"
#include "manager.h"

//�������Ա�Ӳ˵�����
void managerMenu(identity* &manager)
{
	while (true)
	{
		//���ù���Ա�Ӳ˵�
		manager->openMenu();

		//������ָ�룬���������������ӿ�
		Manager* man = (Manager*)manager;

		int choice;

		cin >> choice;

		if (choice == 1)
		{
			//����˺�
			//cout << "����˺�" << endl;
			man->addAccount();
		}
		else if (choice == 2)
		{
			//�鿴�˺�
			//cout << "�鿴�˺�" << endl;
			man->checkAccount();
		}
		else if (choice == 3)
		{
			//�鿴������Ϣ
			//cout << "�鿴����" << endl;
			man->checkInfo();
		}
		else if (choice == 4)
		{
			//���ԤԼ
			//cout << "���ԤԼ" << endl;
			man->clearFile();
		}
		else if (choice == 0)
		{
			//ע����¼
			delete manager;  //���ٶ�������
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}
		else
		{
			//��������
			cout << "��������ȷ��ָ�" << endl;
			system("pause");
			system("cls");
		}
	}
}

//ѧ���Ӳ˵�����
void StudentMenu(identity * &student)
{
		Student* stu = (Student*)student;

		int choice;
		while (true)
		{
			//����ѧ���Ӳ˵�
			student->openMenu();
			cin >> choice;
			switch (choice)
			{
			case 1:  //����ԤԼ
				stu->applyOrder();
				break;
			case 2:  //�鿴����ԤԼ
				stu->checkMyOrder();
				break;
			case 3:  //�鿴����ԤԼ
				stu->checkAllOrder();
				break;
			case 4:  //ȡ��ԤԼ
				stu->cancelOrder();
				break;
			case 0:  //ע����¼
				delete student;
				cout << "ע���ɹ�" << endl;
				system("pause");
				system("cls");
				return;
			default:
				cout << "��������ȷ��ѡ��" << endl;
				break;
			}
		}
}

//��ʦ�Ӳ˵�
void TeacherMenu(identity * & teacher)
{
	Teacher* tea = (Teacher*)teacher;
	int choice;
	while (true)
	{
		teacher->openMenu();
		cin >> choice;

		switch (choice)
		{
		case 1:  //�鿴����ԤԼ
			tea->checkOrder();
			break;
		case 2:  //���ԤԼ
			tea->vaildOrder();
			break;
		case 0:
			delete teacher;
			cout << "ע����¼�ɹ�" << endl;
			system("pause");
			system("cls");
			return;

		default:
			cout << "��������ȷ��ѡ��" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

//��¼����  ����1���ļ����ͣ�����2  �����������
void Login(string fileName, int type)
{
	identity* person = NULL;

	//���ļ�
	ifstream ifs;

	ifs.open(fileName, ios::in);

	//�ж��ļ��Ƿ����
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}

	//׼�������û�����Ϣ
	int id = 0;
	string name;
	string pwd;

	//�ж����

	if (type == 1)  	//ѧ��
	{
		cout << "���������ѧ��" << endl;
		cin >> id;
	}
	else if (type == 2)   //��ʦ
	{
		cout << "��������Ľ�ʦ���" << endl;
		cin >> id;
	}

	cout << "�������û���:" << endl;
	cin >> name;

	cout << "����������:" << endl;
	cin >> pwd;

	if (type == 1)
	{
		//ѧ�������֤
		int fId;  //���ļ��л�ȡ��ID
		string fName;  //���ļ��л�ȡ������
		string fPwd;  //���ļ��л�ȡ������
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			//cout << fId << " " << fName << " " << fPwd << endl;    ���Դ���
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "ѧ����¼�ɹ�" << endl;
				system("pause");
				system("cls");

				person = new Student(id, name, pwd);
				StudentMenu(person);
				//����ѧ�����Ӳ˵�

				return;
			}
		}
	}
	else if (type == 2)
	{
		//��ʦ�����֤
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "��ʦ��¼�ɹ�" << endl;
				system("pause");
				system("cls");

				person = new Teacher(id, name, pwd);
				TeacherMenu(person);
				//������ʦ�Ӳ˵�
				return;
			}
		}
	}
	else if (type == 3)
	{
		//����Ա�����֤
		string fName;
		string fPwd;
		while (ifs >> fName && ifs >> fPwd)
		{
			if (fName == name && fPwd == pwd)
			{
				cout << "����Ա��¼�ɹ�" << endl;
				system("pause");
				system("cls");
				person = new Manager(name, pwd);

				//����Ա�Ӳ˵�
				managerMenu(person);
				return;
			}
		}
	}

	cout << "��֤��¼ʧ�ܣ�" << endl;
	system("pause");
	system("cls");
}

int main()
{
	int choice;  //����ѡ��
	while (true)
	{
		cout << "========================Welcome To System Of Reservation==============================" << endl;
		cout << "�������������" << endl;
		cout << "\t\t-------------------------------------" << endl;
		cout << "\t\t|                                   |" << endl;
		cout << "\t\t|            1.ѧ������             |" << endl;
		cout << "\t\t|                                   |" << endl;
		cout << "\t\t|            2.��ʦ����             |" << endl;
		cout << "\t\t|                                   |" << endl;
		cout << "\t\t|            3.�� �� Ա             |" << endl;
		cout << "\t\t|                                   |" << endl;
		cout << "\t\t|            0.��    ��             |" << endl;
		cout << "\t\t|                                   |" << endl;
		cout << "\t\t-------------------------------------" << endl;

		cin >> choice;
		switch (choice)
		{
		case 1:      //ѧ��
			Login(STUDENT_FILE, 1);
			break;
		case 2:    //��ʦ
			Login(TEACHER_FILE, 2);
			break;
		case 3:    //����Ա
			Login(ADMIN_FILE, 3);
			break;
		case 0:    //�˳�
			cout << "��ӭ�´�ʹ�á�" << endl;
			system("pause");
			exit(0);
			break;
		default:
			cout << "��������������ѡ��" << endl;
			system("pause");
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}