#pragma once
#include "identity.h"
#include "OrderFile.h"
#include <vector>

class Teacher :public identity
{
public:
	//默认构造
	Teacher();

	//有参构造
	Teacher(int id, string name, string pwd);

	//显示教师操作的菜单
	virtual void openMenu();

	//查看所有预约
	void checkOrder();

	//审核预约
	void vaildOrder();

	//职工ID
	int m_MmpId;
};
