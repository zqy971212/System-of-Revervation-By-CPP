#pragma once
#include <iostream>
using namespace std;
#include <string>

//��ݳ������
class identity
{
public:

	//�����˵�
	virtual void openMenu() = 0;

	//�û���
	string m_Name;
	//����
	string m_Pwd;
};