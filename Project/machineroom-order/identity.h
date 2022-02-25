#pragma once
#include "stdafx.h"

// 身份抽象基类
class Identity
{
public:
	// 操作菜单
	virtual void OperMenu() = 0;

	// 用户名
	string m_Name;
	// 密码
	string m_Pwd;
};