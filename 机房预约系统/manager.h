#pragma once
#include "identity.h"
#include <vector>
#include "Student.h"
#include "Teacher.h"
#include <algorithm>
#include "ComputerRoom.h"

class Manager :public identity
{
public:
	//Ĭ�Ϲ���
	Manager();

	//�вι���
	Manager(string name, string pwd);

	//��ʾ����Ա��������
	virtual void openMenu();

	//����˺�
	void addAccount();

	//�鿴�˺�
	void checkAccount();

	//�鿴������Ϣ
	void checkInfo();

	//���ԤԼ��¼
	void clearFile();

	//��ʼ������
	void initVector();

	//ȥ�ز���
	bool CheckRepeat(int id, int type);

	//ѧ������
	vector<Student>vStu;

	//��ʦ����
	vector<Teacher>vTea;

	//������Ϣ
	vector<ComputerRoom>vCom;

};
