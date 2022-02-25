#pragma once
#include "stdafx.h"
#include <fstream>
#include "global_file.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"
extern string UTF8ToGB(const char* str);


void TeacherMenu(Identity*& teacher)
{
	while (true)
	{
		teacher->OperMenu();

		Teacher* tea = (Teacher*)teacher;
		int select = 0;

		cin >> select;
		if (select == 1)
		{
			cout << "�鿴����ԤԼ" << endl;
			tea->ShowAllOrder();
		}
		else if (select == 2)
		{
			cout << "���ԤԼ" << endl;
			tea->ValidOrder();
		}
		else
		{
			delete teacher;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		};
	}
}

void StudentMenu(Identity*& student)
{
	while (true)
	{
		student->OperMenu();

		Student* stu = (Student*)student;
		int select = 0;

		cin >> select;
		if (select == 1)
		{
			cout << "����ԤԼ" << endl;
			stu->ApplyOrder();
		}
		else if (select == 2)
		{
			cout << "�鿴����ԤԼ" << endl;
			stu->ShowMyOrder();
		}
		else if (select == 3)
		{
			cout << "�鿴������ԤԼ" << endl;
			stu->ShowAllOrder();
		}
		else if (select == 4)
		{
			cout << "ȡ��ԤԼ" << endl;
			stu->CancelOrder();
		}
		else
		{
			delete stu;
			cout << "ע����¼" << endl;
			system("pause");
			system("cls");
			return;
		};
	}
};

// �������Ա�Ӳ˵�
void ManagerMenu(Identity*& manager)
{
	while (true)
	{
		manager->OperMenu();

		Manager* man = (Manager*)manager;
		int select = 0;

		cin >> select;
		if (select == 1)
		{
			cout << "����˺�" << endl;
			man->AddPerson();
		}
		else if (select == 2)
		{
			cout << "�鿴�˺�" << endl;
			man->ShowPerson();
		}
		else if (select == 3)
		{
			cout << "�鿴����" << endl;
			man->ShowComputer();
		}
		else if (select == 4)
		{
			cout << "���ԤԼ" << endl;
			man->CleanFile();
		}
		else
		{
			delete manager;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

// ȫ�ֺ���  ��¼���� ����1�������ļ���  ����2 �����������
void LoginIn(string fileName, int type)
{
	// ����ָ�룬����ָ���������
	Identity* person = NULL;

	ifstream ifs;
	ifs.open(fileName, ios::in);

	//ofstream ofs;
	//ofs.open(fileName, ios::out | ios::app);

	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	};

	// ׼�������û���Ϣ
	int id = 0;
	string name;
	string pwd;

	if (type == 1)
	{
		cout << "���������ѧ�ţ�" << endl;
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "����������ְ���ţ�" << endl;
		cin >> id;
	};
	cout << "�������û�����" << endl;
	cin >> name;

	cout << "���������룺" << endl;
	cin >> pwd;


	int fId;
	string fName;
	string fPwd;
	if (type == 1)
	{
		// ѧ�������֤
		
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			
			cout << fId << fName << fPwd << endl;
			//fName = UTF8ToGB(fName.c_str());
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "ѧ����֤��¼�ɹ���" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				// ����ѧ����ݵ��Ӳ˵�
				StudentMenu(person);
				return;
			}
		}
	}
	else if (type == 2)
	{
		// ��ʦ�����֤
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			cout << fId << fName << fPwd << endl;
			//fName = UTF8ToGB(fName.c_str());
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "��ʦ��֤��¼�ɹ���" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				// ������ʦ��ݵ��Ӳ˵�
				TeacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3)
	{
		// ����Ա�����֤
		while (ifs >> fName && ifs >> fPwd)
		{
			cout <<  fName << fPwd << endl;
			if (fName == name && fPwd == pwd)
			{
				cout << "����Ա��֤��¼�ɹ���" << endl;
				system("pause");
				system("cls");
				person = new Manager(name, pwd);
				// �������Ա��ݵ��Ӳ˵�
				ManagerMenu(person);

				return;
			}
		}
	};

	cout << "��֤��¼ʧ�ܣ�" << endl;
	system("pause");
	system("cls");

	return;
};



int main()
{
	int select = 0;

	while (true)
	{
		cout << "========================  ��ӭ��������ԤԼϵͳ  ========================" << endl;
		cout << endl << "�������������" << endl;

		cout << "\t\t --------------------------------\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t|         1��ѧ������            |\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t|         2����    ʦ            |\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t|         3���� �� Ա            |\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t|         0����    ��            |\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t --------------------------------\n";
		cout << "����������ѡ��";

		cin >> select;

		switch (select)
		{
		case 1:
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2:
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3:
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0:
			cout << "��ӭ��һ��ʹ��" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "��������������ѡ��" << endl;
			system("pause");
			system("cls");
			break;
		};
	}
	

	system("pause");
	return 0;
}