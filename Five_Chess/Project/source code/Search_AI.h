#pragma once
#include "Common.h"
#include "Game Logic.h"
#include "Player_base.h"
#include <cmath>
#include <vector>
#include <xutility>
// 搜索AI类
class Search_AI : public Player_Base {
public:
	using score_t = unsigned long long;
	Search_AI	(int md = 14) : maxdepth(md), max_of_judgement(0ULL) {}
	void judge	(const Five_Chess &fc)	noexcept override;
	void put	(Five_Chess &fc)		noexcept override;
	score_t put	(Five_Chess &fc, int depth) noexcept;		// 递归的put函数，重写的put函数基于此函数实现
	std::vector<std::vector<score_t>>	judgement;			// 使用judgement数组存储每一个格子的估值
	score_t								max_of_judgement;	// 保存最大值，空间换时间
	int									maxdepth;			// 最大深度
};