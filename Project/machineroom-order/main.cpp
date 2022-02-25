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
			cout << "查看所有预约" << endl;
			tea->ShowAllOrder();
		}
		else if (select == 2)
		{
			cout << "审核预约" << endl;
			tea->ValidOrder();
		}
		else
		{
			delete teacher;
			cout << "注销成功" << endl;
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
			cout << "申请预约" << endl;
			stu->ApplyOrder();
		}
		else if (select == 2)
		{
			cout << "查看自身预约" << endl;
			stu->ShowMyOrder();
		}
		else if (select == 3)
		{
			cout << "查看所有人预约" << endl;
			stu->ShowAllOrder();
		}
		else if (select == 4)
		{
			cout << "取消预约" << endl;
			stu->CancelOrder();
		}
		else
		{
			delete stu;
			cout << "注销登录" << endl;
			system("pause");
			system("cls");
			return;
		};
	}
};

// 进入管理员子菜单
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
			cout << "添加账号" << endl;
			man->AddPerson();
		}
		else if (select == 2)
		{
			cout << "查看账号" << endl;
			man->ShowPerson();
		}
		else if (select == 3)
		{
			cout << "查看机房" << endl;
			man->ShowComputer();
		}
		else if (select == 4)
		{
			cout << "清空预约" << endl;
			man->CleanFile();
		}
		else
		{
			delete manager;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

// 全局函数  登录功能 参数1：操作文件名  参数2 操作身份类型
void LoginIn(string fileName, int type)
{
	// 父类指针，用于指向子类对象
	Identity* person = NULL;

	ifstream ifs;
	ifs.open(fileName, ios::in);

	//ofstream ofs;
	//ofs.open(fileName, ios::out | ios::app);

	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	};

	// 准备接受用户信息
	int id = 0;
	string name;
	string pwd;

	if (type == 1)
	{
		cout << "请输入你的学号：" << endl;
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "请输入您的职工号：" << endl;
		cin >> id;
	};
	cout << "请输入用户名：" << endl;
	cin >> name;

	cout << "请输入密码：" << endl;
	cin >> pwd;


	int fId;
	string fName;
	string fPwd;
	if (type == 1)
	{
		// 学生身份验证
		
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			
			cout << fId << fName << fPwd << endl;
			//fName = UTF8ToGB(fName.c_str());
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "学生验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				// 进入学生身份的子菜单
				StudentMenu(person);
				return;
			}
		}
	}
	else if (type == 2)
	{
		// 教师身份验证
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			cout << fId << fName << fPwd << endl;
			//fName = UTF8ToGB(fName.c_str());
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "教师验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				// 进入老师身份的子菜单
				TeacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3)
	{
		// 管理员身份验证
		while (ifs >> fName && ifs >> fPwd)
		{
			cout <<  fName << fPwd << endl;
			if (fName == name && fPwd == pwd)
			{
				cout << "管理员验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Manager(name, pwd);
				// 进入管理员身份的子菜单
				ManagerMenu(person);

				return;
			}
		}
	};

	cout << "验证登录失败！" << endl;
	system("pause");
	system("cls");

	return;
};



int main()
{
	int select = 0;

	while (true)
	{
		cout << "========================  欢迎来到机房预约系统  ========================" << endl;
		cout << endl << "请输入您的身份" << endl;

		cout << "\t\t --------------------------------\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t|         1、学生代表            |\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t|         2、老    师            |\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t|         3、管 理 员            |\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t|         0、退    出            |\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t --------------------------------\n";
		cout << "请输入您的选择：";

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
			cout << "欢迎下一次使用" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "输入有误，请重新选择！" << endl;
			system("pause");
			system("cls");
			break;
		};
	}
	

	system("pause");
	return 0;
}