#pragma once
#include "identity.h"
#include "student.h"
#include "teacher.h"
#include <vector>
#include "computer_room.h"

// 管理员类
class Manager : public Identity
{
public:
	Manager();
	Manager(string name, string pwd);
	~Manager();

	void InitVector();

	bool CheckRepeat(int id, int type);

	void OperMenu();

	void AddPerson();

	void ShowPerson();

	void ShowComputer();

	void CleanFile();

	string m_Name;
	string m_Pwd;

	vector<Student> vStu;
	vector<Teacher> vTea;
	vector<ComputerRoom> vCom;
};
