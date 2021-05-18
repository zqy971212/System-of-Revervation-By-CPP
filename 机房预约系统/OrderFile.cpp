#include "OrderFile.h"

//���캯��
OrderFile::OrderFile()
{
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);

	string date;      //����
	string interval;  //ʱ���
	string stuId;      //ID
	string stuName;   //����
	string roomId;    //������
	string status;    //ԤԼ״̬

	this->m_Size = 0;  //��ʼ������

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
		//�ж��Ƿ��ȡ���ַ���
		if (pos!=-1)
		{
			key = date.substr(0, pos);
			value = date.substr(pos + 1, date.size() - pos - 1);
			//cout << key << " " << value << endl;����
			m1.insert(make_pair(key, value));
		}

		//��ȡ���
		pos = interval.find(":");
		//�ж��Ƿ��ȡ���ַ���
		if (pos != -1)
		{
			key = interval.substr(0, pos);
			value = interval.substr(pos + 1, interval.size() - pos - 1);
			//cout << key << " " << value << endl;����
			m1.insert(make_pair(key, value));
		}

		//��ȡѧ��
		pos = stuId.find(":");
		//�ж��Ƿ��ȡ���ַ���
		if (pos != -1)
		{
			key = stuId.substr(0, pos);
			value = stuId.substr(pos + 1, stuId.size() - pos - 1);
			//cout << key << " " << value << endl;����
			m1.insert(make_pair(key, value));
		}

		//��ȡ����
		pos = stuName.find(":");
		//�ж��Ƿ��ȡ���ַ���
		if (pos != -1)
		{
			key = stuName.substr(0, pos);
			value = stuName.substr(pos + 1, stuName.size() - pos - 1);
			//cout << key << " " << value << endl;����
			m1.insert(make_pair(key, value));
		}

		//��ȡ�����
		pos = roomId.find(":");
		//�ж��Ƿ��ȡ���ַ���
		if (pos != -1)
		{
			key = roomId.substr(0, pos);
			value = roomId.substr(pos + 1, roomId.size() - pos - 1);
			//cout << key << " " << value << endl;����
			m1.insert(make_pair(key, value));
		}

		//��ȡ״̬
		pos = status.find(":");
		//�ж��Ƿ��ȡ���ַ���
		if (pos != -1)
		{
			key = status.substr(0, pos);
			value = status.substr(pos + 1, status.size() - pos - 1);
			//cout << key << " " << value << endl;����
			m1.insert(make_pair(key, value));
		}

		//��С����map���뵽���Map������
		this->m_OrderDate.insert(make_pair(this->m_Size, m1));
		this->m_Size++;
	}

	ifs.close();

	//�������map����
	/*for (map<int,map<string,string>>::iterator it = this->m_OrderDate.begin(); it != this->m_OrderDate.end(); it++)
	{
		cout << "����Ϊ��" << it->first << " valuse= " << endl;
		for (map<string,string>::iterator mit = (*it).second.begin(); mit != (*it).second.end(); mit++)
		{
			cout << " key = " << mit->first << " value= " << mit->second << " ";
			cout << endl;
		}
	}*/

}

//����ԤԼ��¼
void OrderFile::UpdateOrder()
{
	if (this->m_Size==0)
	{
		return;  //ԤԼ��¼Ϊ0��ֱ��return
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

//��ʾȫ����Ϣ
void OrderFile::ShowOrder()
{
	for (int i = 0; i < this->m_Size; i++)
	{
		cout << i + 1 << "��";
		cout << "ԤԼ���ڣ���" << this->m_OrderDate[i]["date"];
		cout << " ʱ��Σ�" << (this->m_OrderDate[i]["Interval"] == "1" ? "����" : "����");
		cout << " ѧ�ţ�" << this->m_OrderDate[i]["StuId"];
		cout << " ������" << this->m_OrderDate[i]["StuName"];
		cout << " ������ţ�" << this->m_OrderDate[i]["roomId"];

		string status = " ״̬��";
		//1 �����  2 ��ԤԼ  -1ԤԼʧ��  0 ȡ��ԤԼ
		if (this->m_OrderDate[i]["Status"] == "1")
		{
			status += "�����";
		}
		else if (this->m_OrderDate[i]["Status"] == "2")
		{
			status += "��ԤԼ";
		}
		else if (this->m_OrderDate[i]["Status"] == "-1")
		{
			status += "ԤԼʧ�ܣ����δͨ��";
		}
		else if (this->m_OrderDate[i]["Status"] == "0")
		{
			status += "ԤԼ��ȡ��";
		}
		cout << status;
		cout << endl;
	}
}