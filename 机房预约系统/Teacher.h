#pragma once
#include "identity.h"
#include "OrderFile.h"
#include <vector>

class Teacher :public identity
{
public:
	//Ĭ�Ϲ���
	Teacher();

	//�вι���
	Teacher(int id, string name, string pwd);

	//��ʾ��ʦ�����Ĳ˵�
	virtual void openMenu();

	//�鿴����ԤԼ
	void checkOrder();

	//���ԤԼ
	void vaildOrder();

	//ְ��ID
	int m_MmpId;
};
