#include "Search_AI.h"
#include <unordered_map>
#ifdef _DEBUG
#include <iostream>
#include <iomanip>
// �ָ���
constexpr char separator[] = "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n";
#endif
using namespace std;
#pragma warning(disable: 4244) // doubleתscore_t���ܻ��о�����ʧ���������ﲻ��Ҫ����

constexpr Search_AI::score_t score_ref[5] = { 1, 100, 100000, 100000000ULL, 10000000000000ULL }; // �������Ͷ�Ӧ�ĵ÷ֹ�ֵ����
constexpr int directions[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} }; // ��������
void Search_AI::judge(const Five_Chess &fc) noexcept {
	judgement = vector<vector<score_t>>(15, vector<score_t>(15, 0)); // ��ʼ���ж�
	max_of_judgement = 0; // ��ʼ�����ֵ
	auto spaces = fc.generate_possible_moves(); // ��ȡ���еĿո�
	for(auto &[x, y] : spaces) { // ��ÿһ���ո�ĵ÷ֽ��й�ֵ
		for(int i = 0; i < 4; ++i) {
			int dx = directions[i][0], dy = directions[i][1]; // ���㷽��
			int leftcnt = 0, rightcnt = 0, lefthasblock = 0, righthasblock = 0; // �����������ӵĸ����Լ��Ƿ��ڵ�
			char leftrecord = ' ', rightrecord = ' '; // ��¼�������ߵ�����
			if(x + dx < 0 || y + dy < 0 || x + dx > 14 || y + dy > 14) { // ���Խ�磬ֱ����Ϊû������������
				rightcnt = 0;
				righthasblock = 1;
			}
			else if(fc.chessboard[x + dx][y + dy] == ' ') rightcnt = 0; // ������һ���ǿյ�
			else {
				rightrecord = fc.chessboard[x + dx][y + dy]; // ��¼������һ��
				for(int j = 1; j < 5; ++j) { // ɨ4��
					int nx = x + dx * j, ny = y + dy * j; // ����ƫ����
					if(nx >= 0 && nx <= 14 && ny >= 0 && ny <= 14) { // ��֤��Խ��
						if(fc.chessboard[nx][ny] == rightrecord) {
							rightcnt = j; // ��ͬ������
						}
						else if(fc.chessboard[nx][ny] != ' ') {
							righthasblock = 1; // ����ͬ��˵����·
							break;
						}
						else break; // �գ��˳�
					}
					else { // ���Խ�磬�������²��˵ģ���Ϊ�з�·
						righthasblock = 1;
						break;
					}
				}
			}
			// ͬ���߼�
			if(x - dx < 0 || y - dy < 0 || x - dx > 14 || y - dy > 14) {
				leftcnt = 0;
				lefthasblock = 1;
			}
			else if(fc.chessboard[x - dx][y - dy] == ' ') leftcnt = 0;
			else {
				leftrecord = fc.chessboard[x - dx][y - dy];
				for(int j = 1; j < 5; ++j) {
					int nx2 = x - dx * j, ny2 = y - dy * j;
					if(nx2 >= 0 && nx2 <= 14 && ny2 >= 0 && ny2 <= 14) {
						if(fc.chessboard[nx2][ny2] == leftrecord) {
							leftcnt = j;
						}
						else if(fc.chessboard[nx2][ny2] != ' ') {
							lefthasblock = 1;
							break;
						}
						else break;
					}
					else {
						lefthasblock = 1;
						break;
					}
				}
			}
			// ����õ�ĵ÷�
			// ���������ȣ����з�·������С��4�����ﲻ���������������飬ֱ������
			if((leftrecord == rightrecord) && lefthasblock && righthasblock && (leftcnt + rightcnt < 4)) {
				continue;
			}
			// ���������һ��Խ�磬����һ��С��4�����ﲻ���������������飬ֱ������
			else if((leftrecord == ' ') ^ (rightrecord == ' ') && (leftcnt < 4) && (rightcnt < 4) &&
				lefthasblock && righthasblock) {
				continue;
			}
			// ������߾���Ϊ���Ҳ���ȣ���ÿһ�߾�С��4�����ﲻ���������������飬ֱ������
			else if((leftrecord != ' ') && (rightrecord != ' ') &&
				(leftrecord != rightrecord) && (leftcnt < 4) && (rightcnt < 4)) {
				continue;
			}
			else {
				judgement[x][y] +=
					(lefthasblock	? 0.1 : 1.)	* score_ref[leftcnt] *
					(righthasblock	? 0.1 : 1.)	* score_ref[rightcnt];
			}
		}
		// �������ֵ
		max_of_judgement = max(max_of_judgement, judgement[x][y]);
	}
}

Search_AI::score_t Search_AI::put(Five_Chess &fc, int depth) noexcept {
	// ���ж�
	judge(fc);
	// �������ֵ�ĵ�
	vector<pair<int, int>> maxs;
	// �ݹ鵽�����ֱ�ӷ���
	if(depth >= maxdepth) {
		return max_of_judgement;
	}
	// �����ֵΪ0ʱ��˵����Ϸ��Ϊƽ��
	if(max_of_judgement == 0) {
		auto [x, y] = fc.generate_possible_moves()[0];
		fc.putchess(x, y);
		return 0ULL;
	}
	else {
		// ��ȡ�����������е�
		for(int i = 0; i < 15; ++i) {
			for(int j = 0; j < 15; ++j) {
				if(judgement[i][j] == max_of_judgement) {
					maxs.emplace_back(i, j);
				}
			}
		}
		// ������ĵ�ֻ��һ����ֱ�ӷ���
		if(maxs.size() == 1) {
			auto [i, j] = maxs[0];
			fc.putchess(i, j);
			// ���У���Ϸ�Ƿ����
			char ch;
			if(fc.has_ended(ch)) {
				if(depth != 0) fc.rmchess(i, j); // ֻ�е���Ȳ�Ϊ0ʱ����Ҫ�Ƴ�������
				return static_cast<score_t>(-1);
			}
			judge(fc);
			auto ret = max_of_judgement;
			if(depth != 0) fc.rmchess(i, j);
			else return static_cast<score_t>(-1);
			return ret;
		}
		int _x = -1, _y = -1;
		unsigned long long maxn = 0;
		// ����ÿһ�����ĵ㣬�ݹ������ڼ������ӵ�����£���Ӧ�����ĵ�
		for(auto [i, j] : maxs) {
			fc.putchess(i, j);
			char ch;
			if(fc.has_ended(ch)) {
				if(depth != 0) {
					fc.rmchess(i, j);
				}
				return static_cast<score_t>(-1);
			}
			judge(fc);
			auto retthis = put(fc, depth + 1);
			if(maxn < retthis) {
				maxn = retthis;
				_x = i, _y = j;
			}
			fc.rmchess(i, j);
		}
		// ������Ϊ0������������
		if(depth == 0) {
			fc.putchess(_x, _y);
			return static_cast<score_t>(-1);
		}
		else {
			return maxn;
		}
	}
}

void Search_AI::put(Five_Chess &fc) noexcept {
#ifdef _DEBUG
	// ��DEBUGģʽ�´�ӡjudgement
	for(int i = 0; i < 15; ++i) {
		for(int j = 0; j < 15; ++j) {
			cout << setw(16) << judgement[j][i] << "\t";
		}
		cout << "\n\n";
	}
	cout << separator;
#endif
	put(fc, 0);
}