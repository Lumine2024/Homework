#pragma once
#include "Common.h"
#include "Game Logic.h"
#include "Player_base.h"
#include <cmath>
#include <vector>
#include <xutility>
// ����AI��
class Search_AI : public Player_Base {
public:
	using score_t = unsigned long long;
	Search_AI	(int md = 14) : maxdepth(md), max_of_judgement(0ULL) {}
	void judge	(const Five_Chess &fc)	noexcept override;
	void put	(Five_Chess &fc)		noexcept override;
	score_t put	(Five_Chess &fc, int depth) noexcept;		// �ݹ��put��������д��put�������ڴ˺���ʵ��
	std::vector<std::vector<score_t>>	judgement;			// ʹ��judgement����洢ÿһ�����ӵĹ�ֵ
	score_t								max_of_judgement;	// �������ֵ���ռ任ʱ��
	int									maxdepth;			// ������
};