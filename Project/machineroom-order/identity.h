#pragma once
#include "stdafx.h"

// ��ݳ������
class Identity
{
public:
	// �����˵�
	virtual void OperMenu() = 0;

	// �û���
	string m_Name;
	// ����
	string m_Pwd;
};