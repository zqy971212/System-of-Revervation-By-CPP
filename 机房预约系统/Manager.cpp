#include "manager.h"
#include <fstream>
#include "globalFile.h"


//默认构造
Manager::Manager()
{
}

//有参构造
Manager::Manager(string name, string pwd)
{
	this->m_Name = name;
	this->m_Pwd = pwd;

	//初始化容器，并获取文件中所以的信息
	this->initVector();

	//初始化机房信息
	vCom.clear();
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom com;
	//将数据写入到容器中
	while (ifs>> com.m_ComId && ifs>>com.m_MaxNum	)
	{
		this->vCom.push_back(com);
	}
	ifs.close();

	//cout << "机房的数量为：" << vCom.size() << endl;
}

//显示管理员操作界面
void Manager::openMenu()
{
	cout << "---------------------------欢迎管理员！------------------------" << endl;
	cout << "\t\t-------------------------------------" << endl;
	cout << "\t\t|                                   |" << endl;
	cout << "\t\t|            1.添加账号             |" << endl;
	cout << "\t\t|                                   |" << endl;
	cout << "\t\t|            2.查看账号             |" << endl;
	cout << "\t\t|                                   |" << endl;
	cout << "\t\t|            3.查看机房             |" << endl;
	cout << "\t\t|                                   |" << endl;
	cout << "\t\t|            4.清空预约             |" << endl;
	cout << "\t\t|                                   |" << endl;
	cout << "\t\t|            0.注销登录             |" << endl;
	cout << "\t\t|                                   |" << endl;
	cout << "\t\t-------------------------------------" << endl;
}

//添加账号
void Manager::addAccount()
{
	string fileName;  //操作的文件名
	string tIp;  //提示的ID号  老师/学生
	string errorTip;

	int select;

	while (true)
	{
		cout << "请输入添加的账号类型" << endl;
		cout << "1、学生" << endl;
		cout << "2、老师" << endl;
		cin >> select;
		if (select == 1)
		{
			//添加学生
			fileName = STUDENT_FILE;
			tIp = "请输入学号:";
			errorTip = "学号重复，请重新输入";
			break;
		}
		else if (select == 2)
		{
			fileName = TEACHER_FILE;
			tIp = "请输入教工号:";
			errorTip = "教工号重复，请重新输入";
			break;
		}
		cout << "请输入正确的选择" << endl;
	}

	ofstream ofs;
	string name;  //姓名
	string pwd;   //密码
	int id;   //id

	cout << tIp << endl;  //输入学号/教工号的提示
	while (true)
	{
		cin >> id;
		//检测ID是否重复
		bool ret = this->CheckRepeat(id, select);
		if (ret)
		{
			cout << errorTip << endl;
		}
		else
		{
			break;
		}
	}

	//利用追加的方式写入
	ofs.open(fileName, ios::out | ios::app);

	cout << "请输入您的姓名：" << endl;
	cin >> name;

	cout << "请输入您的密码：" << endl;
	cin >> pwd;

	//写入文件
	ofs << id << " " << name << " " << pwd <<endl;
	cout << "添加成功" << endl;

	//更新容器，防止重复更新
	this->initVector();

	system("pause");
	system("cls");

	//关闭文件
	ofs.close();
}

//仿函数  打印学生
class PrintStu
{
public:
	void operator()(Student s1)
	{
		cout << "学号：" << s1.m_Id << " 姓名：" << s1.m_Name<<" 密码："<<s1.m_Pwd;
		cout << endl;
	}
};
//仿函数 打印老师
class PrintTea
{
public:
	void operator()(Teacher t1)
	{
		cout << "教工编号：" << t1.m_MmpId << " 姓名：" << t1.m_Name << " 密码：" << t1.m_Pwd;
		cout << endl;
	}
};

//查看账号
void Manager::checkAccount()
{
	cout << "请选择查看内容：" << endl;
	cout << "1、查看所有的学生" << endl;
	cout << "2、查看所有的老师" << endl;

	int select;
	while (true)
	{
		cin >> select;
		if (select == 1)
		{
			//查看学生
			for_each(vStu.begin(), vStu.end(), PrintStu());

			break;
		}
		else if (select == 2)
		{
			//查看老师
			for_each(vTea.begin(), vTea.end(), PrintTea());

			break;
		}
		else
		{
			cout << "请输入正确的选择" << endl;
		}
	}
	system("pause");
	system("cls");

}

//查看机房信息的仿函数
class PrintComputer
{
public:
	void operator ()(ComputerRoom com)
	{
		cout << "机房ID:" << com.m_ComId << " 最大容量：" << com.m_MaxNum;
		cout << endl;
	}
};

//查看机房信息
void Manager::checkInfo()
{
	cout << "机房信息如下：" << endl;
	for_each(vCom.begin(), vCom.end(), PrintComputer());

	system("pause");
	system("cls");
}

//清空预约记录
void Manager::clearFile()
{
	cout << "确认要清空预约信息吗？" << endl;
	cout << "1、是" << endl;
	cout << "2、否" << endl;
	int choice;
	cin >> choice;
	if (choice!=1)
	{
		system("pause");
		system("cls");
		return;
	}
	ofstream ofs;
	//利用trunc清空文件
	ofs.open(ORDER_FILE, ios::trunc);
	ofs.close();

	cout << "清空成功！" << endl;
	system("pause");
	system("cls");
}

//初始化容器
void Manager::initVector()
{
	//确保容器清空
	vStu.clear();
	vTea.clear();

	ifstream ifs;
	//读取学生信息
	ifs.open(STUDENT_FILE, ios::in);

	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
		return;
	}

	//读取学生信息并存在vStu容器中
	Student s;
	while (ifs>>s.m_Id && ifs>>s.m_Name && ifs>>s.m_Pwd)
	{
		vStu.push_back(s);
	}
	ifs.close();
	//cout << "学生的数量为" << vStu.size() << endl;  测试

	//读取老师信息

	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
		return;
	}

	//将老师信息存储在vTea容器中
	Teacher t;
	while (ifs>>t.m_MmpId && ifs>>t.m_Name && ifs>>t.m_Pwd)
	{
		vTea.push_back(t);
	}
	ifs.close();
	//cout << "老师的数量为" << vTea.size() << endl;  测试
}

//去重操作
bool Manager::CheckRepeat(int id, int type)   //id:输入的ID，type检测的类型
{
	if (type==1)
	{
		//检测学生
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			if (id==it->m_Id)
			{
				return true;
			}
		}
	}
	else
	{
		//检测老师
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			if (id==it->m_MmpId)
			{
				return true;
			}
		}
	}
	return false;
}