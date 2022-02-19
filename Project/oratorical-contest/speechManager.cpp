#include "speechManager.h"
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <fstream>


SpeechManager::SpeechManager()
{
	initSpeech();

	createSpeaker();
};
SpeechManager::~SpeechManager()
{

};
void SpeechManager::show_Menu()
{
	cout << "***************************************************" << endl;
	cout << "************  欢迎参加演讲比赛  *******************" << endl;
	cout << "************   1.开始演讲比赛   *******************" << endl;
	cout << "************   2.查看往届记录   *******************" << endl;
	cout << "************   3.清空比赛记录   *******************" << endl;
	cout << "************   3.推出比赛程序   *******************" << endl;
	cout << "***************************************************" << endl;
	cout << endl;
};

void SpeechManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
};

void SpeechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Record.clear();
	// 初始化比赛轮数
	this->m_Index = 1;
};

void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		};

		// 12 名选手编号
		this->v1.push_back(i + 1001);

		// 选手编号，以及对应的选手  存放到 map 容器中
		this->m_Speaker.insert(make_pair(i + 1001, sp));
	}
};

void SpeechManager::startSpeech()
{
	// 第一轮比赛
	// 1、抽签
	speechDraw();

	// 2、比赛
	speechContest();

	// 3、显示晋级结果
	showScore();

	// 第二轮比赛
	m_Index++;
	// 1、抽签
	speechDraw();

	// 2、比赛
	speechContest();

	// 3、显示最终结果
	showScore();

	// 4、保存分数
	saveRecord();
};

void SpeechManager::speechDraw()
{
	cout << "第 << " << this->m_Index << " >> 轮比赛选手正在抽签..." << endl;
	cout << "----------------------------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;

	if (this->m_Index == 1)
	{
		// 第一轮比赛
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		};
		cout << endl;
		cout << "----------------------------------------" << endl;
	}
	else
	{
		// 第二轮比赛
	}
};

void SpeechManager::speechContest()
{
	cout << "--------------  第" << this->m_Index << "轮比赛正式开始  --------------" << endl;
	multimap<double, int, greater<double>> groupScore;
	int num = 0; // 记录人员 6 人为一组

	vector<int> v_Src;  // 比赛选手容器
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	};

	// 遍历所有选手进行比赛
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		// 评委打分
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;   // 600 ~ 1000 f代表小数
			d.push_back(score);

		};

		sort(d.begin(), d.end(), greater<double>()); // 排序
		d.pop_front();   // 去除最高分
		d.pop_back();	 // 去除最低分

		double sum = accumulate(d.begin(), d.end(), 0.0f);  // 总分
		double avg = sum / (double)d.size();  // 平均分

		// 将平均分放入到 map 容器中
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		// 将打分数据 放入到临时小组容器中
		groupScore.insert(make_pair(avg, *it)); // key 是得分, value 是具体选手编号

		num++;
		// 每 6 人取出前三名
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次：" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号：" << it->second << " 姓名：" << this->m_Speaker[it->second].m_Name << " 成绩："
					<< this->m_Speaker[it->second].m_Score[m_Index - 1] << endl;
			};

			// 取前三名放入另一个容器中
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
			{
				if (this->m_Index == 1)
				{
					v2.push_back(it->second);
				}
				else
				{
					vVictory.push_back(it->second);
				}

			};

			groupScore.clear(); // 小组容器清空
			cout << "-------------  第" << this->m_Index << "轮比赛完毕  ---------------------" << endl;
			system("pause");
		};

	};

};

void SpeechManager::showScore()
{
	cout << "-----------  第" << this->m_Index << "轮晋级选手如下: ------------" << endl;
	vector<int> v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;
	};

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "选手编号: " << *it << " 姓名：" << m_Speaker[*it].m_Name << " 得分: " << m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	};
	cout << endl;

	system("pause");
	system("cls");
	this->show_Menu();
};

void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app); // 用输出的方式打开文件  -- 写文件

	// 将每个人数据写入到文件中
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << m_Speaker[*it].m_Score[1] << ",";
	};
	ofs << endl;

	// 关闭文件
	ofs.close();

	this->isEmptyFile = false;
	initSpeech();
	createSpeaker();
	cout << "=============记录已经保存============" << endl;
	cout << "=============本届比赛完毕============" << endl;
	cout << endl;
};

void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);   // 输入流对象 读取文件

	// 非空判断
	if (!ifs.is_open())
	{
		this->isEmptyFile == true;
		cout << "文件不存在!" << endl;
		ifs.close();
		return;
	};

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空!" << endl;
		this->isEmptyFile = true;
		ifs.close();
		return;
	};

	// 文件不为空
	this->isEmptyFile = false;

	ifs.putback(ch);  // 读取的单个字符放回去

	string data;
	int index = 0;
	while (ifs >> data)
	{
		vector<string> v;
		int pos = -1;
		int start = 0;

		while (true)
		{
			pos = data.find(",", start); // 从 0 开始查找
			if (pos == -1)
			{
				break; // 找不到返回
			};
			string tmp = data.substr(start, pos - start); // 找到了，进行分割，参数 1 起始位置，参数 2 截取长度
			v.push_back(tmp);
			start = pos + 1;
		};

		this->m_Record.insert(make_pair(index, v));
		index++;
	};

	ifs.close();

};

void SpeechManager::showRecord()
{
	if (this->m_Record.empty())
	{
		cout << "=======  无记录  ========" << endl;
		return;
	};

	for (map<int, vector<string>>::iterator mapIt = this->m_Record.begin(); mapIt != this->m_Record.end(); mapIt++)
	{
		cout << "第 【 " << mapIt->first + 1 << " 】 届：";
		for (vector<string>::iterator vecIt = mapIt->second.begin(); vecIt != mapIt->second.end(); vecIt++)
		{
			cout << *vecIt << " ";
		};
		cout << endl;
	};
	this->m_Record.clear();
};

void SpeechManager::clearRecord()
{
	cout << "确认清空？" << endl;
	cout << "1、确认 2、返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		// 初始化属性
		this->initSpeech();

		// 创建选手
		this->createSpeaker();
	}
}