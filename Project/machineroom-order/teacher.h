#pragma once
#include "identity.h"

// ��ʦ��
class Teacher : public Identity
{
public:
	Teacher();
	Teacher(int empId, string name, string pwd);
	~Teacher();

	// �˵�����
	void OperMenu();

	//
	void ValidOrder();

	void ShowAllOrder();

	void CancelOrder();

	int m_EmpId;
	string m_Name;
	string m_Pwd;
};