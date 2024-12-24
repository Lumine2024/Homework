#pragma once
#include "Common.h"
#include "Player_Base.h"
#include <algorithm>
#include <utility>
#include <vector>
#pragma warning(disable: 5030) // �޷�ʶ�����ԣ�msvc::always_inline
// ������������
class Five_Chess {
public:
	Five_Chess() :
		chessboard(15, std::vector<char>(15, ' ')),
		white_player_playing(false),
		lastx(-1), lasty(-1),
		prev_lastx(-1), prev_lasty(-1) {}
	Five_Chess(const Five_Chess &other) :
		chessboard(other.chessboard),
		white_player_playing(other.white_player_playing),
		lastx(other.lastx), lasty(other.lasty),
		prev_lastx(other.prev_lastx), prev_lasty(other.prev_lasty) {}
	Five_Chess &operator=(const Five_Chess &other) {
		if(this != &other) {
			chessboard = other.chessboard;
			white_player_playing = other.white_player_playing;
			lastx = other.lastx;
			lasty = other.lasty;
			prev_lastx = other.prev_lastx;
			prev_lasty = other.prev_lasty;
		}
		return *this;
	}
	// ����
	RELEASE_INLINE void								putchess	(int x, int y);
	// �Ƴ�����
	RELEASE_INLINE void								rmchess		(int x, int y) noexcept;
	// �ж���Ϸ�Ƿ������ch�����Ի�ȡʤ�����
	RELEASE_INLINE bool								has_ended	(char &ch) const noexcept;
	// �������п��ܵ����Ӵ�
	RELEASE_INLINE std::vector<std::pair<int, int>> generate_possible_moves() const noexcept;
	// �������������ң�trueΪ����
	RELEASE_INLINE bool								player_playing() const noexcept {
		return white_player_playing;
	}
	// ����
	std::vector<std::vector<char>>	chessboard;
	// �Ƿ�Ϊ�������ڲ���
	bool							white_player_playing;
	// ���һ�����ӵ�λ��
	int								lastx, lasty;
	// ��һ�����ӵ�λ��
	int								prev_lastx, prev_lasty;
};

// ������Ϸ�ĺ���
// ���ĸ�����Ϊ���Ӻ��Ƿ�ȴ�500ms������Ϊ�˷�ֹAI���Ҷ���ʱ���ӹ����޷�����
RELEASE_INLINE void playgame(Five_Chess &fc,
	Player_Base *player1, Player_Base *player2,
	bool dosleep = false) noexcept;

// �������
class Human : public Player_Base {
public:
	Human() noexcept = default;
	// ������жϿ�������������ɣ����ṩ��ʵ��
	RELEASE_INLINE void judge(const Five_Chess &fc) noexcept override {}
	// ��ȡ�����Ϣ�����ʱ����
	RELEASE_INLINE void put(Five_Chess &fc)			noexcept override;
};