#pragma once
#include "identity.h"
#include "global_file.h"
#include <vector>
#include "computer_room.h"

// —ß…˙¿‡
class Student : public Identity
{
public:
	Student();
	Student(int id, string name, string pwd);
	~Student();

	void OperMenu();

	void ApplyOrder();

	void ShowMyOrder();

	void ShowAllOrder();

	void CancelOrder();

	int m_Id;
	string m_Name;
	string m_Pwd;
	vector<ComputerRoom> vCom;
};
