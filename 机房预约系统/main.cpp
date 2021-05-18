#include <iostream>
using namespace std;
#include "identity.h"
#include <fstream>
#include "globalFile.h"
#include "Student.h"
#include "Teacher.h"
#include "manager.h"

//进入管理员子菜单界面
void managerMenu(identity* &manager)
{
	while (true)
	{
		//调用管理员子菜单
		manager->openMenu();

		//将父类指针，调用子类里其他接口
		Manager* man = (Manager*)manager;

		int choice;

		cin >> choice;

		if (choice == 1)
		{
			//添加账号
			//cout << "添加账号" << endl;
			man->addAccount();
		}
		else if (choice == 2)
		{
			//查看账号
			//cout << "查看账号" << endl;
			man->checkAccount();
		}
		else if (choice == 3)
		{
			//查看机房信息
			//cout << "查看机房" << endl;
			man->checkInfo();
		}
		else if (choice == 4)
		{
			//清空预约
			//cout << "清空预约" << endl;
			man->clearFile();
		}
		else if (choice == 0)
		{
			//注销登录
			delete manager;  //销毁堆区数据
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
		else
		{
			//其他输入
			cout << "请输入正确的指令！" << endl;
			system("pause");
			system("cls");
		}
	}
}

//学生子菜单界面
void StudentMenu(identity * &student)
{
		Student* stu = (Student*)student;

		int choice;
		while (true)
		{
			//调用学生子菜单
			student->openMenu();
			cin >> choice;
			switch (choice)
			{
			case 1:  //申请预约
				stu->applyOrder();
				break;
			case 2:  //查看自身预约
				stu->checkMyOrder();
				break;
			case 3:  //查看所有预约
				stu->checkAllOrder();
				break;
			case 4:  //取消预约
				stu->cancelOrder();
				break;
			case 0:  //注销登录
				delete student;
				cout << "注销成功" << endl;
				system("pause");
				system("cls");
				return;
			default:
				cout << "请输入正确的选择" << endl;
				break;
			}
		}
}

//老师子菜单
void TeacherMenu(identity * & teacher)
{
	Teacher* tea = (Teacher*)teacher;
	int choice;
	while (true)
	{
		teacher->openMenu();
		cin >> choice;

		switch (choice)
		{
		case 1:  //查看所有预约
			tea->checkOrder();
			break;
		case 2:  //审核预约
			tea->vaildOrder();
			break;
		case 0:
			delete teacher;
			cout << "注销登录成功" << endl;
			system("pause");
			system("cls");
			return;

		default:
			cout << "请输入正确的选择" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

//登录功能  参数1，文件类型，参数2  操作身份类型
void Login(string fileName, int type)
{
	identity* person = NULL;

	//读文件
	ifstream ifs;

	ifs.open(fileName, ios::in);

	//判断文件是否存在
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}

	//准备接受用户的信息
	int id = 0;
	string name;
	string pwd;

	//判断身份

	if (type == 1)  	//学生
	{
		cout << "请输入你的学号" << endl;
		cin >> id;
	}
	else if (type == 2)   //老师
	{
		cout << "请输入你的教师编号" << endl;
		cin >> id;
	}

	cout << "请输入用户名:" << endl;
	cin >> name;

	cout << "请输入密码:" << endl;
	cin >> pwd;

	if (type == 1)
	{
		//学生身份验证
		int fId;  //从文件中获取的ID
		string fName;  //从文件中获取的姓名
		string fPwd;  //从文件中获取的密码
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			//cout << fId << " " << fName << " " << fPwd << endl;    测试代码
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "学生登录成功" << endl;
				system("pause");
				system("cls");

				person = new Student(id, name, pwd);
				StudentMenu(person);
				//进入学生的子菜单

				return;
			}
		}
	}
	else if (type == 2)
	{
		//老师身份验证
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "教师登录成功" << endl;
				system("pause");
				system("cls");

				person = new Teacher(id, name, pwd);
				TeacherMenu(person);
				//进入老师子菜单
				return;
			}
		}
	}
	else if (type == 3)
	{
		//管理员身份验证
		string fName;
		string fPwd;
		while (ifs >> fName && ifs >> fPwd)
		{
			if (fName == name && fPwd == pwd)
			{
				cout << "管理员登录成功" << endl;
				system("pause");
				system("cls");
				person = new Manager(name, pwd);

				//管理员子菜单
				managerMenu(person);
				return;
			}
		}
	}

	cout << "验证登录失败！" << endl;
	system("pause");
	system("cls");
}

int main()
{
	int choice;  //接受选择
	while (true)
	{
		cout << "========================Welcome To System Of Reservation==============================" << endl;
		cout << "请输入您的身份" << endl;
		cout << "\t\t-------------------------------------" << endl;
		cout << "\t\t|                                   |" << endl;
		cout << "\t\t|            1.学生代表             |" << endl;
		cout << "\t\t|                                   |" << endl;
		cout << "\t\t|            2.老师代表             |" << endl;
		cout << "\t\t|                                   |" << endl;
		cout << "\t\t|            3.管 理 员             |" << endl;
		cout << "\t\t|                                   |" << endl;
		cout << "\t\t|            0.退    出             |" << endl;
		cout << "\t\t|                                   |" << endl;
		cout << "\t\t-------------------------------------" << endl;

		cin >> choice;
		switch (choice)
		{
		case 1:      //学生
			Login(STUDENT_FILE, 1);
			break;
		case 2:    //老师
			Login(TEACHER_FILE, 2);
			break;
		case 3:    //管理员
			Login(ADMIN_FILE, 3);
			break;
		case 0:    //退出
			cout << "欢迎下次使用。" << endl;
			system("pause");
			exit(0);
			break;
		default:
			cout << "输入有误，请重新选择" << endl;
			system("pause");
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}