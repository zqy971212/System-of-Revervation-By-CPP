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
	//默认构造
	Manager();

	//有参构造
	Manager(string name, string pwd);

	//显示管理员操作界面
	virtual void openMenu();

	//添加账号
	void addAccount();

	//查看账号
	void checkAccount();

	//查看机房信息
	void checkInfo();

	//清空预约记录
	void clearFile();

	//初始化容器
	void initVector();

	//去重操作
	bool CheckRepeat(int id, int type);

	//学生容器
	vector<Student>vStu;

	//老师容器
	vector<Teacher>vTea;

	//机房信息
	vector<ComputerRoom>vCom;

};
