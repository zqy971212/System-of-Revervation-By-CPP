#pragma once
#include <iostream>
using namespace std;
#include "globalFile.h"
#include <fstream>
#include <map>

class OrderFile
{
public:
	//���캯��
	OrderFile();

	//����ԤԼ��¼
	void UpdateOrder();

	//��ʾȫ����Ϣ
	void ShowOrder();

	//��¼ԤԼ����
	int m_Size;

	//��¼����ԤԼ��Ϣ������  key��¼����  value ��¼�����ֵ����Ϣ
	map<int, map<string, string>> m_OrderDate;
};