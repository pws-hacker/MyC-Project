#include "teacher.h"
#include "order_file.h"
#include <vector>

Teacher::Teacher()
{

};

Teacher::Teacher(int empId, string name, string pwd):m_EmpId(empId),m_Name(name),m_Pwd(pwd)
{

};

Teacher::~Teacher()
{

};

void Teacher::OperMenu()
{
	cout << "��ӭ��ʦ��" << this->m_Name << "��¼��" << endl;

	cout << "\t\t --------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|         1���鿴����ԤԼ        |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|         2�����ԤԼ            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|         0��ע����¼            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t --------------------------------\n";
	cout << "��ѡ�����Ĳ�����" << endl;
};

void Teacher::ShowAllOrder()
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

void Teacher::ValidOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	};

	cout << "����˵ļ�¼���£�" << endl;

	vector<int> v;
	int index = 1;
	for (int i = 0; i < of.m_Size; i++)
	{
		if (atoi(of.m_OrderData[i]["stuId"].c_str()) == this->m_EmpId)
		{
			if (of.m_OrderData[i]["status"] == "1" && of.m_OrderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << ++index << "��";
				cout << "ԤԼ���ڣ���" << of.m_OrderData[i]["date"];
				cout << " ʱ�Σ�" << (of.m_OrderData[i]["interval"] == "1" ? "����" : "����");
				cout << " ������" << of.m_OrderData[i]["roomId"];
				string status = " ״̬�� ";
				if (of.m_OrderData[i]["status"] == "1")
				{
					status += "�����";
				};

				cout << status << endl;
			}
		}
	};

	cout << "��������˵�ԤԼ��¼��0������" << endl;
	int select = 0;
	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
				break;
			else
			{
				cout << "��������˽��" << endl;
				cout << "1��ͨ��" << endl;
				cout << "2����ͨ��" << endl;
				int ret;
				cin >> ret;

				if (ret == 1)
				{
					of.m_OrderData[v[select - 1]]["status"] = "2";
				}
				else
				{
					of.m_OrderData[v[select - 1]]["status"] = "-1";
				}
				of.UpdateOrder();
				cout << "������" << endl;
				break;
			}
		};
		cout << "�����������������룡" << endl;
	};
}

void Teacher::CancelOrder()
{

}
