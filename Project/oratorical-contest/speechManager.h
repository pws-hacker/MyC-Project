#pragma once
#include <iostream>
#include <vector>
#include <map>

#include "speaker.h"

using namespace std;

// ����ݽ�������
class SpeechManager
{
public:
	SpeechManager();
	~SpeechManager();

	void show_Menu();    // �˵�����

	void exitSystem();   // �˳�����

	void initSpeech();   // ��ʼ������

	void createSpeaker();  // ����ѡ��

	void startSpeech();   // ��ʼ����

	void speechDraw();    // ��һ�ֱ���

	void speechContest(); // ��������

	void showScore();   // չʾ����

	void saveRecord();  // �����¼

	void loadRecord();  // ���ؼ�¼

	void showRecord();  // ���ؼ�¼

	void clearRecord(); // �����¼
	// ����ѡ�� ���� 12��
	vector<int> v1;

	// ��һ�ֽ�������  6��
	vector<int> v2;

	// ʤ��ǰ��������  3��
	vector<int> vVictory;

	// ��ű�� �Լ���Ӧ�ľ���ѡ��  ����
	map<int, Speaker> m_Speaker;

	// ��¼��������
	int m_Index;

	// ������¼
	map<int, vector<string>> m_Record;

	// �Ƿ�Ϊ��
	bool isEmptyFile;
};
