#include "student.h"
#include <fstream>
#include "computer_room.h"
#include "order_file.h"


Student::Student()
{

};

Student::Student(int id, string name, string pwd):m_Id(id),m_Name(name),m_Pwd(pwd)
{
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom c;
	while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
	{
		vCom.push_back(c);
	};

	ifs.close();
};

Student::~Student()
{

};

void Student::OperMenu()
{
	cout << "��ӭѧ������" << this->m_Name << "��¼��" << endl;

	cout << "\t\t --------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|         1������ԤԼ            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|         2���鿴�ҵ�ԤԼ        |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|         3���鿴����ԤԼ        |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|         4��ȡ��ԤԼ            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|         0��ע����¼            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t --------------------------------\n";
	cout << "��ѡ�����Ĳ�����" << endl;
};

void Student::ApplyOrder()
{
	cout << "��������ʱ��Ϊ��һ������!" << endl;
	cout << "����������ԤԼ��ʱ�䣺" << endl;
	cout << "1����һ" << endl;
	cout << "2���ܶ�" << endl;
	cout << "3������" << endl;
	cout << "4������" << endl;
	cout << "5������" << endl;

	int date = 0;
	int interval = 0;
	int room = 0;

	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "�����������������룡" << endl;
	};

	cout << "����������ԤԼʱ��Σ�" << endl;
	cout << "1������" << endl;
	cout << "2������" << endl;

	while (true)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		cout << "�����������������룡" << endl;
	};

	cout << "��ѡ�������" << endl;
	for (int i = 0; i < (int)vCom.size(); i++)
	{
		cout << vCom[i].m_ComId << "�Ż�������Ϊ��" << vCom[i].m_MaxNum << endl;
	}

	while (true)
	{
		cin >> room;
		if (room >= 1 && room <= 3)
		{
			break;
		}
		cout << "�����������������룡" << endl;
	};
	
	cout << "ԤԼ�ɹ�������С�����" << endl;

	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);

	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->m_Id << " ";
	ofs << "stuName:" << this->m_Name << " ";
	ofs << "roomId:" << room << " ";
	ofs << "status:" << 1 << " ";
	
	system("pause");
	system("cls");

};

void Student::ShowMyOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	};

	for (int i = 0; i < of.m_Size; i++)
	{
		if (atoi(of.m_OrderData[i]["stuId"].c_str()) == this->m_Id)
		{
			cout << "ԤԼ���ڣ���" << of.m_OrderData[i]["date"];
			cout << " ʱ�Σ�" << (of.m_OrderData[i]["interval"] == "1" ? "����" : "����");
			cout << " ������" << of.m_OrderData[i]["roomId"];
			string status = " ״̬�� ";
			if (of.m_OrderData[i]["status"] == "1")
			{
				status += "�����";
			}
			else if (of.m_OrderData[i]["status"] == "2")
			{
				status += "ԤԼ�ɹ�";
			}
			else if (of.m_OrderData[i]["status"] == "2")
			{
				status += "���δͨ����ԤԼʧ��";
			}
			else
			{
				status += "ԤԼ��ȡ��";
			};
			cout << status << endl;
		}
	};
	system("pause");
	system("cls");
};

void Student::ShowAllOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	};

	for (int i = 0; i < of.m_Size; i++)
	{
		cout << i + 1 << "��  ";
		cout << "ԤԼ���ڣ���" << of.m_OrderData[i]["date"];
		cout << " ʱ�Σ�" << (of.m_OrderData[i]["interval"] == "1" ? "����" : "����");
		cout << " ������" << of.m_OrderData[i]["roomId"];
		string status = " ״̬�� ";
		if (of.m_OrderData[i]["status"] == "1")
		{
			status += "�����";
		}
		else if (of.m_OrderData[i]["status"] == "2")
		{
			status += "ԤԼ�ɹ�";
		}
		else if (of.m_OrderData[i]["status"] == "2")
		{
			status += "���δͨ����ԤԼʧ��";
		}
		else
		{
			status += "ԤԼ��ȡ��";
		};
		cout << status << endl;

	};
	system("pause");
	system("cls");
};

void Student::CancelOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	};
	cout << "����л�ԤԼ�гɹ��ļ�¼����ȡ����������ȡ���ļ�¼" << endl;

	vector<int> v;
	int index = 1;
	for (int i = 0; i < of.m_Size; i++)
	{
		if (atoi(of.m_OrderData[i]["stuId"].c_str()) == this->m_Id)
		{
			if (of.m_OrderData[i]["status"] == "1" && of.m_OrderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << index++ << "��";
				cout << "ԤԼ���ڣ���" << of.m_OrderData[i]["date"];
				cout << " ʱ�Σ�" << (of.m_OrderData[i]["interval"] == "1" ? "����" : "����");
				cout << " ������" << of.m_OrderData[i]["roomId"];
				string status = " ״̬�� ";
				if (of.m_OrderData[i]["status"] == "1")
				{
					status += "�����";
				}
				else if (of.m_OrderData[i]["status"] == "2")
				{
					status += "ԤԼ�ɹ�";
				}

				cout << status << endl;
			}
		}
	};

	cout << "������ȡ���ļ�¼��0������" << endl;
	int select = 0;
	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select = 0)
				break;
			else
			{
				of.m_OrderData[v[select - 1]]["status"] = "0";
				of.UpdateOrder();
				cout << "��ȡ��ԤԼ" << endl;
				break;
			}
		};
		cout << "�����������������룡" << endl;
	};

	system("pause");
	system("cls");
}
