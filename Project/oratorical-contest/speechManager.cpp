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
	cout << "************  ��ӭ�μ��ݽ�����  *******************" << endl;
	cout << "************   1.��ʼ�ݽ�����   *******************" << endl;
	cout << "************   2.�鿴�����¼   *******************" << endl;
	cout << "************   3.��ձ�����¼   *******************" << endl;
	cout << "************   3.�Ƴ���������   *******************" << endl;
	cout << "***************************************************" << endl;
	cout << endl;
};

void SpeechManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
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
	// ��ʼ����������
	this->m_Index = 1;
};

void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		};

		// 12 ��ѡ�ֱ��
		this->v1.push_back(i + 1001);

		// ѡ�ֱ�ţ��Լ���Ӧ��ѡ��  ��ŵ� map ������
		this->m_Speaker.insert(make_pair(i + 1001, sp));
	}
};

void SpeechManager::startSpeech()
{
	// ��һ�ֱ���
	// 1����ǩ
	speechDraw();

	// 2������
	speechContest();

	// 3����ʾ�������
	showScore();

	// �ڶ��ֱ���
	m_Index++;
	// 1����ǩ
	speechDraw();

	// 2������
	speechContest();

	// 3����ʾ���ս��
	showScore();

	// 4���������
	saveRecord();
};

void SpeechManager::speechDraw()
{
	cout << "�� << " << this->m_Index << " >> �ֱ���ѡ�����ڳ�ǩ..." << endl;
	cout << "----------------------------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;

	if (this->m_Index == 1)
	{
		// ��һ�ֱ���
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
		// �ڶ��ֱ���
	}
};

void SpeechManager::speechContest()
{
	cout << "--------------  ��" << this->m_Index << "�ֱ�����ʽ��ʼ  --------------" << endl;
	multimap<double, int, greater<double>> groupScore;
	int num = 0; // ��¼��Ա 6 ��Ϊһ��

	vector<int> v_Src;  // ����ѡ������
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	};

	// ��������ѡ�ֽ��б���
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		// ��ί���
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;   // 600 ~ 1000 f����С��
			d.push_back(score);

		};

		sort(d.begin(), d.end(), greater<double>()); // ����
		d.pop_front();   // ȥ����߷�
		d.pop_back();	 // ȥ����ͷ�

		double sum = accumulate(d.begin(), d.end(), 0.0f);  // �ܷ�
		double avg = sum / (double)d.size();  // ƽ����

		// ��ƽ���ַ��뵽 map ������
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		// ��������� ���뵽��ʱС��������
		groupScore.insert(make_pair(avg, *it)); // key �ǵ÷�, value �Ǿ���ѡ�ֱ��

		num++;
		// ÿ 6 ��ȡ��ǰ����
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С��������Σ�" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "��ţ�" << it->second << " ������" << this->m_Speaker[it->second].m_Name << " �ɼ���"
					<< this->m_Speaker[it->second].m_Score[m_Index - 1] << endl;
			};

			// ȡǰ����������һ��������
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

			groupScore.clear(); // С���������
			cout << "-------------  ��" << this->m_Index << "�ֱ������  ---------------------" << endl;
			system("pause");
		};

	};

};

void SpeechManager::showScore()
{
	cout << "-----------  ��" << this->m_Index << "�ֽ���ѡ������: ------------" << endl;
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
		cout << "ѡ�ֱ��: " << *it << " ������" << m_Speaker[*it].m_Name << " �÷�: " << m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	};
	cout << endl;

	system("pause");
	system("cls");
	this->show_Menu();
};

void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app); // ������ķ�ʽ���ļ�  -- д�ļ�

	// ��ÿ��������д�뵽�ļ���
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << m_Speaker[*it].m_Score[1] << ",";
	};
	ofs << endl;

	// �ر��ļ�
	ofs.close();

	this->isEmptyFile = false;
	initSpeech();
	createSpeaker();
	cout << "=============��¼�Ѿ�����============" << endl;
	cout << "=============����������============" << endl;
	cout << endl;
};

void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);   // ���������� ��ȡ�ļ�

	// �ǿ��ж�
	if (!ifs.is_open())
	{
		this->isEmptyFile == true;
		cout << "�ļ�������!" << endl;
		ifs.close();
		return;
	};

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ��!" << endl;
		this->isEmptyFile = true;
		ifs.close();
		return;
	};

	// �ļ���Ϊ��
	this->isEmptyFile = false;

	ifs.putback(ch);  // ��ȡ�ĵ����ַ��Ż�ȥ

	string data;
	int index = 0;
	while (ifs >> data)
	{
		vector<string> v;
		int pos = -1;
		int start = 0;

		while (true)
		{
			pos = data.find(",", start); // �� 0 ��ʼ����
			if (pos == -1)
			{
				break; // �Ҳ�������
			};
			string tmp = data.substr(start, pos - start); // �ҵ��ˣ����зָ���� 1 ��ʼλ�ã����� 2 ��ȡ����
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
		cout << "=======  �޼�¼  ========" << endl;
		return;
	};

	for (map<int, vector<string>>::iterator mapIt = this->m_Record.begin(); mapIt != this->m_Record.end(); mapIt++)
	{
		cout << "�� �� " << mapIt->first + 1 << " �� �죺";
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
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ�� 2������" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		// ��ʼ������
		this->initSpeech();

		// ����ѡ��
		this->createSpeaker();
	}
}