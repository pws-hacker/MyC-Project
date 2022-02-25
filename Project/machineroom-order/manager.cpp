#include "manager.h"
#include "global_file.h"
#include <fstream>
#include <algorithm>
#include <functional>
#include "utils.h"


Manager::Manager()
{
	InitVector();
};

Manager::Manager(string name, string pwd):m_Name(name),m_Pwd(pwd)
{
	InitVector();
}

Manager::~Manager()
{

}

void Manager::OperMenu()
{
	cout << "��ӭ����Ա��" << this->m_Name << "��¼��" << endl;

	cout << "\t\t --------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|         1������˺�            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|         2���鿴�˺�           |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|         3���鿴����            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|         4�����ԤԼ            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|         0��ע����¼            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t --------------------------------\n";
	cout << "��ѡ�����Ĳ�����" << endl;
}

void Manager::AddPerson()
{
	cout << "����������˺ŵ�����" << endl;
	cout << "1�����ѧ��" << endl;
	cout << "2�������ʦ" << endl;

	string fileName; // �����ļ���
	string tip;  // ��ʾ id ��
	string errorTip; // �ظ���ʾ

	ofstream ofs;

	int select = 0;
	cin >> select;
	if (select == 1)
	{
		fileName = STUDENT_FILE;
		tip = "������ѧ��";
		errorTip = "ѧ���ظ������������룺";
	}
	else
	{
		fileName = TEACHER_FILE;
		tip = "������ְ����";
		errorTip = "ְ�����ظ������������룺";

	};

	ofs.open(fileName, ios::out | ios::app);

	int id;
	string name;
	string pwd;

	while (true)
	{
		cout << tip << endl;
		cin >> id;
		bool ret = CheckRepeat(id, select);
		if (ret)
		{
			cout << errorTip << endl;
		}
		else
		{
			break;
		}
	}

	
	

	cout << "������������" << endl;
	cin >> name;
	cout << "���������룺" << endl;
	cin >> pwd;

	// ���ļ����������
	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "��ӳɹ�" << endl;

	system("pause");
	system("cls");

	ofs.close();
	InitVector();  // ����������ͬһ id ʱ�޷�����ظ��� bug;
}

void PrintStudent(Student &s)
{
	cout << "ѧ�ţ�" << s.m_Id << " ������" << s.m_Name << " ���룺" << s.m_Pwd << endl;
}

void PrintTeacher(Teacher& s)
{
	//cout << s.m_Name << endl;
	cout << "ְ���ţ�" << s.m_EmpId << " ������" << s.m_Name << " ���룺" << s.m_Pwd << endl;
}

void Manager::ShowPerson()
{
	cout << "��ѡ��鿴���ݣ�" << endl;
	cout << "1���鿴����ѧ��" << endl;
	cout << "2���鿴������ʦ" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		cout << "����ѧ����Ϣ���£�" << endl;
		for_each(vStu.begin(), vStu.end(), PrintStudent);
	}
	else
	{
		cout << "������ʦ��Ϣ���£�" << endl;
		for_each(vTea.begin(), vTea.end(), PrintTeacher);
	};

	system("pause");
	system("cls");
}

void Manager::ShowComputer()
{
	cout << "������Ϣ���£�" << endl;
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
	{
		cout << "������ţ�" << it->m_ComId << " �������������" << it->m_MaxNum << endl;
	};
	system("pause");
	system("cls");
}

void Manager::CleanFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();

	cout << "��ճɹ�" << endl;
	system("pause");
	system("cls");
}

void Manager::InitVector()
{
	vStu.clear();
	vTea.clear();

	// ��ȡ��Ϣ  ѧ������ʦ
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);

	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ��" << endl;
		return;
	};

	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	};
	cout << "��ǰѧ������Ϊ��" << vStu.size() << endl;
	ifs.close();


	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ��" << endl;
		return;
	};
	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	};
	cout << "��ǰ��ʦ����Ϊ��" << vTea.size() << endl;
	ifs.close();

	// ��ȡ������Ϣ
	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom c;

	while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
	{
		vCom.push_back(c);
	};

	cout << "��ǰ��������Ϊ��" << vCom.size() << endl;
	ifs.close();

};

bool Manager::CheckRepeat(int id,int type)
{
	if (type == 1)
	{
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			if (id == it->m_Id)
			{
				return true;
			}
		}
	}
	else
	{
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			if (id == it->m_EmpId)
			{
				return true;
			}
		}
	};

	return false;
}