#pragma once
#include <iostream>
#include <vector>
#include <map>

#include "speaker.h"

using namespace std;

// 设计演讲管理类
class SpeechManager
{
public:
	SpeechManager();
	~SpeechManager();

	void show_Menu();    // 菜单功能

	void exitSystem();   // 退出程序

	void initSpeech();   // 初始化属性

	void createSpeaker();  // 创建选手

	void startSpeech();   // 开始比赛

	void speechDraw();    // 第一轮比赛

	void speechContest(); // 比赛进行

	void showScore();   // 展示分数

	void saveRecord();  // 保存记录

	void loadRecord();  // 加载记录

	void showRecord();  // 加载记录

	void clearRecord(); // 清除记录
	// 比赛选手 容器 12人
	vector<int> v1;

	// 第一轮晋级容器  6人
	vector<int> v2;

	// 胜利前三名容器  3人
	vector<int> vVictory;

	// 存放编号 以及对应的具体选手  容器
	map<int, Speaker> m_Speaker;

	// 记录比赛轮数
	int m_Index;

	// 比赛记录
	map<int, vector<string>> m_Record;

	// 是否为空
	bool isEmptyFile;
};
