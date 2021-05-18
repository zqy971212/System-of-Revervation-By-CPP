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
	//默认构造
	Student();

	//有参构造
	Student(int id, string name, string pwd);

	//显示学生操作的菜单界面
	virtual void openMenu();

	//申请预约
	void applyOrder();

	//查看自身预约
	void checkMyOrder();

	//查看所有预约
	void checkAllOrder();

	//取消预约
	void cancelOrder();

	//学号
	int m_Id;

	//机房信息
	vector<ComputerRoom>vCom;
};