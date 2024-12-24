#include "Game Logic.h"
#include "Graphics Logic.h"
#include <string>
using namespace std;
extern HWND game;
RELEASE_INLINE void Five_Chess::putchess(int x, int y) {
	// Ϊ�գ�����
	if(chessboard[x][y] == ' ') {
		chessboard[x][y]		= white_player_playing ? '1' : '2';
		white_player_playing	= !white_player_playing;
		prev_lastx				= lastx;
		prev_lasty				= lasty;
		lastx					= x;
		lasty					= y;
	}
	// ��ռ�ݣ����쳣
	else {
		throw Occupied();
	}
}

RELEASE_INLINE void Five_Chess::rmchess(int x, int y) noexcept {
	// �������
	chessboard[x][y]		= ' ';
	white_player_playing	= !white_player_playing;
	lastx					= prev_lastx;
	lasty					= prev_lasty;
}

RELEASE_INLINE bool Five_Chess::has_ended(char &ch) const noexcept {
	// �������飬��Ϸ����
	for(int i = 0; i < 15; ++i) {
		for(int j = 0; j < 11; ++j) {
			if(chessboard[i][j]			== chessboard[i][j + 1] &&
				chessboard[i][j + 1]	== chessboard[i][j + 2] &&
				chessboard[i][j + 2]	== chessboard[i][j + 3] &&
				chessboard[i][j + 3]	== chessboard[i][j + 4] &&
				chessboard[i][j] != ' ') {
					ch = chessboard[i][j];
					return true;
			}
		}
	}
	for(int i = 0; i < 15; ++i) {
		for(int j = 0; j < 11; ++j) {
			if(chessboard[j][i]			== chessboard[j + 1][i] &&
				chessboard[j + 1][i]	== chessboard[j + 2][i] &&
				chessboard[j + 2][i]	== chessboard[j + 3][i] &&
				chessboard[j + 3][i]	== chessboard[j + 4][i] &&
				chessboard[j][i] != ' ') {
					ch = chessboard[j][i];
					return true;
			}
		}
	}
	for(int i = 0; i < 11; ++i) {
		for(int j = 0; j < 11; ++j) {
			if(chessboard[i][j]				== chessboard[i + 1][j + 1] &&
				chessboard[i + 1][j + 1]	== chessboard[i + 2][j + 2] &&
				chessboard[i + 2][j + 2]	== chessboard[i + 3][j + 3] &&
				chessboard[i + 3][j + 3]	== chessboard[i + 4][j + 4] &&
				chessboard[i][j] != ' ') {
					ch = chessboard[i][j];
					return true;
			}
		}
	}
	for(int i = 4; i < 15; ++i) {
		for(int j = 0; j < 11; ++j) {
			if(chessboard[i][j]				== chessboard[i - 1][j + 1] &&
				chessboard[i - 1][j + 1]	== chessboard[i - 2][j + 2] &&
				chessboard[i - 2][j + 2]	== chessboard[i - 3][j + 3] &&
				chessboard[i - 3][j + 3]	== chessboard[i - 4][j + 4] &&
				chessboard[i][j] != ' ') {
					ch = chessboard[i][j];
					return true;
			}
		}
	}
	// ����ռ������Ϸ����
	if(generate_possible_moves().empty()) {
		ch = '3';
		return true;
	}
	// δ����
	ch = ' ';
	return false;
}

RELEASE_INLINE vector<pair<int, int>> Five_Chess::generate_possible_moves() const noexcept {
	// �������пյ�����
	vector<pair<int, int>> moves;
	for(int i = 0; i < chessboard.size(); ++i) {
		for(int j = 0; j < chessboard[i].size(); ++j) {
			if(chessboard[i][j] == ' ') {
				moves.emplace_back(i, j);
			}
		}
	}
	return moves;
}

RELEASE_INLINE void playgame(Five_Chess &fc,
	Player_Base *player1, Player_Base *player2,
	bool dosleep) noexcept {
	// ������Ϸʱ��ӡ����
	printboard(fc);
	// ��ȡʤ���ߵĴ������
	char ch;
	// ����Ϸ����ǰѭ�����˲���
	while(!fc.has_ended(ch)) {
		player1->judge(fc);
		player1->put(fc);
		printboard(fc);
		FlushBatchDraw();
		// �����һ�����Ӻ���Ϸ�Ѿ���������ֱ���˳�ѭ��
		if(fc.has_ended(ch)) break;
		if(dosleep) Sleep(500);
		player2->judge(fc);
		player2->put(fc);
		printboard(fc);
		FlushBatchDraw();
		if(dosleep && !fc.has_ended(ch)) Sleep(500);
	}
	// ���㶯��
	vector<tstring> texts = {
		_T("�����ʤ��"),	_T("White wins!"),
		_T("�����ʤ��"),	_T("Black wins!"),
		_T("ƽ�֣�"),		_T("Draw!")
	};
	printhint(340, 220, 
		texts[(static_cast<size_t>(ch) - '1') * 2 + static_cast<size_t>(language)].c_str());
	FlushBatchDraw();
	// �ȴ�1s�󷵻����˵�
	Sleep(1000);
	setlinecolor(BLACK);
}

RELEASE_INLINE void Human::put(Five_Chess &fc) noexcept {
	while(true) {
		// ��ȡ�����Ϣ
		MOUSEMSG msg = GetMouseMsg();
		// û�е�������ʱ�򲻶ϻ�ȡ�����Ϣ
		while(msg.uMsg != WM_LBUTTONDOWN) {
			msg = GetMouseMsg();
			printboard(fc, msg);
		}
		// �����ڰ�������ĵط�����
		try {
			// �������Ϣת��Ϊ��������
			int x = (msg.x - 25) / 40;
			int y = (msg.y - 25) / 40;
			// ����������������ӣ������׳��쳣Occupied����catch���д���
			if(msg.uMsg == WM_LBUTTONDOWN && x < 15 && y < 15 && x >= 0 && y >= 0) {
				fc.putchess(x, y);
				// �ɹ����ӣ��˳�ѭ��
				break;
			}
		}
		// ����ʧ�ܣ���λ�ñ�ռ�ã�����ѭ��
		catch(Occupied &) {}
	}
}