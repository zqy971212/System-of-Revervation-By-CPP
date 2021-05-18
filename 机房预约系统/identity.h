#pragma once
#include <iostream>
using namespace std;
#include <string>

//身份抽象基类
class identity
{
public:

	//操作菜单
	virtual void openMenu() = 0;

	//用户名
	string m_Name;
	//密码
	string m_Pwd;
};