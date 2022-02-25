#pragma once
#include "identity.h"

// 教师类
class Teacher : public Identity
{
public:
	Teacher();
	Teacher(int empId, string name, string pwd);
	~Teacher();

	// 菜单界面
	void OperMenu();

	//
	void ValidOrder();

	void ShowAllOrder();

	void CancelOrder();

	int m_EmpId;
	string m_Name;
	string m_Pwd;
};