#include "Teacher.h"

//默认构造
Teacher::Teacher()
{
}

//有参构造
Teacher::Teacher(int id, string name, string pwd)
{
	this->m_MmpId = id;
	this->m_Name = name;
	this->m_Pwd = pwd;
}

//显示教师操作的菜单
void Teacher::openMenu()
{
	cout << "---------------------------欢迎" << this->m_Name << "老师------------------------" << endl;
	cout << "\t\t-----------------------------------------" << endl;
	cout << "\t\t|                                       |" << endl;
	cout << "\t\t|            1.查看所有预约             |" << endl;
	cout << "\t\t|                                       |" << endl;
	cout << "\t\t|            2.审 核 预  约             |" << endl;
	cout << "\t\t|                                       |" << endl;
	cout << "\t\t|            0.注 销 登 录              |" << endl;
	cout << "\t\t|                                       |" << endl;
	cout << "\t\t-----------------------------------------" << endl;
}

//查看所有预约
void Teacher::checkOrder()
{
	OrderFile of;

	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	of.ShowOrder();

	system("pause");
	system("cls");
}

//审核预约
void Teacher::vaildOrder()
{
	OrderFile of;
	if (of.m_Size==0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	vector<int>v;
	int index = 1;
	cout << "待审核的预约记录如下：" << endl;

	for (int i = 0; i < of.m_Size; i++)
	{
		//审核中的数据
		if (of.m_OrderDate[i]["Status"]=="1")
		{
			v.push_back(i);
			cout << index++ << " 、";
			cout << "预约日期：周" << of.m_OrderDate[i]["date"];
			cout << " 时间段：" << (of.m_OrderDate[i]["Interval"] == "1" ? "上午" : "下午");
			cout << " 学号：" << of.m_OrderDate[i]["StuId"];
			cout << " 姓名：" << of.m_OrderDate[i]["StuName"];
			cout << " 机房编号：" << of.m_OrderDate[i]["roomId"];
			cout << " 状态：审核中" << endl;
		}
	}

	cout << "请输入审核的预约记录，0代表返回" << endl;
	int select;  
	int ret;  //介绍预约结果记录

	while (true)
	{
		cin >> select;
		if (select==0)
		{
			break;
		}
		else if (select>0 && select<=v.size())
		{
			cout << "请输入审核结果" << endl;
			cout << "1、通过" << endl;
			cout << "2、不通过" << endl;
			cin >> ret;
			if (ret==1)
			{
				//通过
				of.m_OrderDate[v[select - 1]]["Status"] = "2";
			}
			else
			{
				//不通过
				of.m_OrderDate[v[select - 1]]["Status"] = "-1";
			}
			of.UpdateOrder();
			cout << "审核完毕" << endl;
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}

	system("pause");
	system("cls");

}