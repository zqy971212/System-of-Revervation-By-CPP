#include "Student.h"

//默认构造
Student::Student()
{
}

//有参构造
Student::Student(int id, string name, string pwd)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;

	//初始化机房信息
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom com;
	while (ifs>>com.m_ComId && ifs>>com.m_MaxNum)
	{
		vCom.push_back(com);
	}
	ifs.close();

}

//显示学生操作的菜单界面
void Student::openMenu()
{
	cout << "---------------------------欢迎"<<this->m_Name<<"同学------------------------" << endl;
	cout << "\t\t-----------------------------------------" << endl;
	cout << "\t\t|                                       |" << endl;
	cout << "\t\t|            1.申 请 预  约             |" << endl;
	cout << "\t\t|                                       |" << endl;
	cout << "\t\t|            2.查看自身预约             |" << endl;
	cout << "\t\t|                                       |" << endl;
	cout << "\t\t|            3.查看所有预约             |" << endl;
	cout << "\t\t|                                       |" << endl;
	cout << "\t\t|            4.取 消 预  约             |" << endl;
	cout << "\t\t|                                       |" << endl;
	cout << "\t\t|            0.注销登录                 |" << endl;
	cout << "\t\t|                                       |" << endl;
	cout << "\t\t-----------------------------------------" << endl;
}

//申请预约
void Student::applyOrder()
{
	cout << "请输入申请预约的时间：" << endl;
	cout << "1、周一" << endl;
	cout << "2、周二" << endl;
	cout << "3、周三" << endl;
	cout << "4、周四" << endl;
	cout << "5、周五" << endl;

	int date = 0;  //日期
	int interval = 0;  //时间段
	int room = 0;  //机房编号
	
	while (true)
	{
		cin >> date;
		if (date>=1 && date<=5)
		{
			break;
		}
		cout << "输入有误请重新输入" << endl;
	}

	cout << "请输入申请预约时间段：" << endl;
	cout << "1、上午" << endl;
	cout << "2、下午" << endl;

	while (true)
	{
		cin >> interval;
		if (interval==1 || interval==2)
		{
			break;
		}
		cout << "请输入正确的时间段" << endl;
	}

	cout << "请选择机房" << endl;
	for (int i = 0; i < vCom.size(); i++)
	{
		cout <<i+1<<"、"<< vCom[i].m_ComId << "号机房容量为：" << vCom[i].m_MaxNum << endl;
	}

	while (true)
	{
		cin >> room;
		if (room>=1 && room<=3)
		{
			break;
		}
		cout << "请输入正确的机房" << endl;
	}

	cout << "预约成功，审核中" << endl;

	ofstream ofs;
	ofs.open(ORDER_FILE, ios::out | ios::app);

	ofs << "date:" << date << " ";
	ofs << "Interval:" << interval << " ";
	ofs << "StuId:" << this->m_Id << " ";
	ofs << "StuName:" << this->m_Name << " ";
	ofs << "roomId:" << room << " ";
	ofs << "Status:" << 1 << endl;


	ofs.close();
	system("pause");
	system("cls");
}

//查看自身预约
void Student::checkMyOrder()
{
	OrderFile of;
	if (of.m_Size==0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_Size; i++)
	{
		//string 转 int
		//string利用 .c_str() 转 const char *
		//利用 atoi 转int
		if (this->m_Id==atoi( of.m_OrderDate[i]["StuId"].c_str()))  //找到自身预约
		{
			cout << "预约日期：周" << of.m_OrderDate[i]["date"];
			cout << " 时间段：" << (of.m_OrderDate[i]["Interval"] == "1" ? "上午" : "下午");
			cout << " 机房号：" << of.m_OrderDate[i]["roomId"];

			string status = "状态：";
            //1 审核中  2 已预约  -1预约失败  0 取消预约
			if (of.m_OrderDate[i]["Status"]=="1")
			{
				status += "审核中";
			}
			else if (of.m_OrderDate[i]["Status"]=="2")
			{
				status += "已预约";
			}
			else if (of.m_OrderDate[i]["Status"]=="-1")
			{
				status += "预约失败，审核未通过";
			}
			else if (of.m_OrderDate[i]["Status"]=="0")
			{
				status += "预约已取消";
			}
			cout << status;
			cout << endl;
		}
		else
		{
			cout << "未查到您的相关预约信息" << endl;
			break;

		}
	}

	system("pause");
	system("cls");
}

//查看所有预约
void Student::checkAllOrder()
{
	OrderFile of;

	if (of.m_Size==0)
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

//取消预约
void Student::cancelOrder()
{
	OrderFile of;

	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "审核中或预约成功的记录可以取消，请输入取消的记录" << endl;

	vector<int>v;  //存放在最大容器中的下表编号

	int index = 1;
	for (int i = 0; i < of.m_Size; i++)
	{
		//先判断自身学号
		if (this->m_Id==atoi(of.m_OrderDate[i]["StuId"].c_str()))
		{
			//再筛选状态 审核中或预约成功
			if (of.m_OrderDate[i]["Status"]=="1" || of.m_OrderDate[i]["Status"]=="2")
			{
				v.push_back(i);
				cout << index++ << " 、";
				cout << "预约日期：周" << of.m_OrderDate[i]["date"];
				cout << " 时间段：" << (of.m_OrderDate[i]["Interval"] == "1" ? "上午" : "下午");
				cout << " 机房编号：" << of.m_OrderDate[i]["roomId"];

				string status = " 状态：";

				if (of.m_OrderDate[i]["Status"]=="1")
				{
					status += "审核中";
				}
				else if (of.m_OrderDate[i]["Status"]=="2")
				{
					status += "预约成功";
				}
				cout << status << endl;
			}
		}
	}

	cout << "请输入取消的记录,0代表返回" << endl;
	int select;
	while (true)
	{
		cin >> select;

		if (select>=0 && select<=v.size())
		{
			if (select==0)
			{
				break;
			}
			else
			{
				of.m_OrderDate[v[select - 1]]["Status"] = "0";

				of.UpdateOrder();

				cout << "已取消预约" << endl;
				break;
			}
		}

		cout << "输入有误，请重新输入" << endl;
	}

	system("pause");
	system("cls");
}