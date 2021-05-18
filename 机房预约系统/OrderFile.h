#pragma once
#include <iostream>
using namespace std;
#include "globalFile.h"
#include <fstream>
#include <map>

class OrderFile
{
public:
	//构造函数
	OrderFile();

	//更新预约记录
	void UpdateOrder();

	//显示全部信息
	void ShowOrder();

	//记录预约条数
	int m_Size;

	//记录所以预约信息的容器  key记录条数  value 记录具体键值对信息
	map<int, map<string, string>> m_OrderDate;
};