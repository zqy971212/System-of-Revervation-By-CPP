#include "OrderFile.h"

//构造函数
OrderFile::OrderFile()
{
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);

	string date;      //日期
	string interval;  //时间段
	string stuId;      //ID
	string stuName;   //姓名
	string roomId;    //机房号
	string status;    //预约状态

	this->m_Size = 0;  //初始化条数

	while (ifs>>date && ifs>>interval && ifs>>stuId && ifs>>stuName && ifs>>roomId && ifs>>status)
	{
		//cout << date << endl;
		//cout << interval << endl;
		//cout << stuId << endl;
		//cout << stuName << endl;
		//cout << roomId << endl;
		//cout << status << endl;

		string key;
		string value;
		map<string, string>m1;
		
		//date:11
		int pos = date.find(":");
		//判断是否截取到字符串
		if (pos!=-1)
		{
			key = date.substr(0, pos);
			value = date.substr(pos + 1, date.size() - pos - 1);
			//cout << key << " " << value << endl;测试
			m1.insert(make_pair(key, value));
		}

		//获取间隔
		pos = interval.find(":");
		//判断是否截取到字符串
		if (pos != -1)
		{
			key = interval.substr(0, pos);
			value = interval.substr(pos + 1, interval.size() - pos - 1);
			//cout << key << " " << value << endl;测试
			m1.insert(make_pair(key, value));
		}

		//获取学号
		pos = stuId.find(":");
		//判断是否截取到字符串
		if (pos != -1)
		{
			key = stuId.substr(0, pos);
			value = stuId.substr(pos + 1, stuId.size() - pos - 1);
			//cout << key << " " << value << endl;测试
			m1.insert(make_pair(key, value));
		}

		//获取姓名
		pos = stuName.find(":");
		//判断是否截取到字符串
		if (pos != -1)
		{
			key = stuName.substr(0, pos);
			value = stuName.substr(pos + 1, stuName.size() - pos - 1);
			//cout << key << " " << value << endl;测试
			m1.insert(make_pair(key, value));
		}

		//获取房间号
		pos = roomId.find(":");
		//判断是否截取到字符串
		if (pos != -1)
		{
			key = roomId.substr(0, pos);
			value = roomId.substr(pos + 1, roomId.size() - pos - 1);
			//cout << key << " " << value << endl;测试
			m1.insert(make_pair(key, value));
		}

		//获取状态
		pos = status.find(":");
		//判断是否截取到字符串
		if (pos != -1)
		{
			key = status.substr(0, pos);
			value = status.substr(pos + 1, status.size() - pos - 1);
			//cout << key << " " << value << endl;测试
			m1.insert(make_pair(key, value));
		}

		//将小容器map放入到大的Map容器中
		this->m_OrderDate.insert(make_pair(this->m_Size, m1));
		this->m_Size++;
	}

	ifs.close();

	//测试最大map容器
	/*for (map<int,map<string,string>>::iterator it = this->m_OrderDate.begin(); it != this->m_OrderDate.end(); it++)
	{
		cout << "条数为：" << it->first << " valuse= " << endl;
		for (map<string,string>::iterator mit = (*it).second.begin(); mit != (*it).second.end(); mit++)
		{
			cout << " key = " << mit->first << " value= " << mit->second << " ";
			cout << endl;
		}
	}*/

}

//更新预约记录
void OrderFile::UpdateOrder()
{
	if (this->m_Size==0)
	{
		return;  //预约记录为0条直接return
	}
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::out | ios::trunc);
	
	for (int i = 0; i < this->m_Size; i++)
	{
		ofs << "date:" << this->m_OrderDate[i]["date"] << " ";
		ofs << "Interval:" << this->m_OrderDate[i]["Interval"] << " ";
		ofs << "StuId:" << this->m_OrderDate[i]["StuId"] << " ";
		ofs << "StuName:" << this->m_OrderDate[i]["StuName"] << " ";
		ofs << "roomId:" << this->m_OrderDate[i]["roomId"] << " ";
		ofs << "Status:" << this->m_OrderDate[i]["Status"] << endl;
	}
	ofs.close();
}

//显示全部信息
void OrderFile::ShowOrder()
{
	for (int i = 0; i < this->m_Size; i++)
	{
		cout << i + 1 << "、";
		cout << "预约日期：周" << this->m_OrderDate[i]["date"];
		cout << " 时间段：" << (this->m_OrderDate[i]["Interval"] == "1" ? "上午" : "下午");
		cout << " 学号：" << this->m_OrderDate[i]["StuId"];
		cout << " 姓名：" << this->m_OrderDate[i]["StuName"];
		cout << " 机房编号：" << this->m_OrderDate[i]["roomId"];

		string status = " 状态：";
		//1 审核中  2 已预约  -1预约失败  0 取消预约
		if (this->m_OrderDate[i]["Status"] == "1")
		{
			status += "审核中";
		}
		else if (this->m_OrderDate[i]["Status"] == "2")
		{
			status += "已预约";
		}
		else if (this->m_OrderDate[i]["Status"] == "-1")
		{
			status += "预约失败，审核未通过";
		}
		else if (this->m_OrderDate[i]["Status"] == "0")
		{
			status += "预约已取消";
		}
		cout << status;
		cout << endl;
	}
}