#pragma once
#include <iostream>
#include <map>
#include "global_file.h"

using namespace std;

// ‘§‘º¿‡
class OrderFile
{
public:
	OrderFile();
	~OrderFile();

	void UpdateOrder();

	map<int, map<string, string>> m_OrderData;

	int m_Size;
};

