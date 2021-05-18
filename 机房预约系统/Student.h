#pragma once
#include "identity.h"
#include <vector>
#include "ComputerRoom.h"
#include <fstream>
#include "globalFile.h"
#include "OrderFile.h"

class Student :public identity
{
public:
	//Ĭ�Ϲ���
	Student();

	//�вι���
	Student(int id, string name, string pwd);

	//��ʾѧ�������Ĳ˵�����
	virtual void openMenu();

	//����ԤԼ
	void applyOrder();

	//�鿴����ԤԼ
	void checkMyOrder();

	//�鿴����ԤԼ
	void checkAllOrder();

	//ȡ��ԤԼ
	void cancelOrder();

	//ѧ��
	int m_Id;

	//������Ϣ
	vector<ComputerRoom>vCom;
};