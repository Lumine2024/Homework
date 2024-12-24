#define _CRT_SECURE_NO_WARNINGS
#include "Graphics Logic.h"
#include "mmsystem.h"
#include <string>
#include <iostream>
#include <fstream>
#pragma comment(lib,"winmm.lib")
using namespace std;
Language language;
// �Ƿ����ڲ�������
bool music_playing;
constexpr COLORREF Board_Background = RGB(200, 131, 63);
RELEASE_INLINE void init() noexcept {
	cin.tie(nullptr)->sync_with_stdio(false);
	// ��ȡ����
	fstream settings("../settings/settings.txt", ios::in);
	cin.rdbuf(settings.rdbuf());
	readsettings();
#ifdef _DEBUG
	// DEBUGģʽ�³�ʼ��������Ϣ
	fstream debuglog("log.txt", ios::out);
	cout.rdbuf(debuglog.rdbuf());
#endif
	// ����BGM
	mciSendString(_T("open ../resources/FiveChess.mp3 alias bgm"), nullptr, 0, nullptr);
	if(music_playing) {
		mciSendString(_T("play bgm repeat"), nullptr, 0, nullptr);
	}
	// ��ʼ��ͼ�ν���
	initgraph(680, 680);
	setbkcolor(Board_Background);
	setlinecolor(BLACK);
	cleardevice();
	BeginBatchDraw();
}

RELEASE_INLINE void printhint(int x, int y, const TCHAR *str) {
	if(language == Chinese) {
		settextstyle(50, 0, _T("��������"));
	}
	else {
		settextstyle(25, 0, _T("Consolas"));
	}
	settextcolor(RED);
	int strlen		= textwidth(str);
	int strhight	= textheight(str);
	int countx		= x - (strlen / 2);
	int county		= y - (strhight / 2);
	outtextxy(countx, county, str);
}

const vector<tstring> Occupied_texts = {
	_T("��λ���ѱ�ռ�ã�������ѡ��"),
	_T("The position has been occupied, please choose again!")
};
RELEASE_INLINE Occupied::Occupied() noexcept {
	printhint(340, 220, Occupied_texts[static_cast<size_t>(language)].c_str());
	FlushBatchDraw();
	Sleep(500);
}

RELEASE_INLINE void printboard(const Five_Chess &game, const MOUSEMSG &msg) noexcept {
	setbkcolor(Board_Background);
	cleardevice();
	// ��������
	setlinecolor(BLACK);
	for(int i = 0; i < 15; ++i) {
		int offset = 50 + i * 40;
		line(50,		offset,		610,		offset);
		line(offset,	50,			offset,		610);
	}
	// ������
	for(int i = 0; i < 15; ++i) {
		for(int j = 0; j < 15; ++j) {
			int x = 50 + i * 40;
			int y = 50 + j * 40;
			if(game.chessboard[i][j] == '1') {
				setfillcolor(WHITE);
				setlinecolor(BLACK);
				solidcircle(x, y, 15);
				circle(x, y, 15);
			}
			else if(game.chessboard[i][j] == '2') {
				setfillcolor(BLACK);
				solidcircle(x, y, 15);
			}
		}
	}
	// Ϊ�������ӱ�Ǻ��
	if(game.lastx != -1 && game.lasty != -1) {
		setfillcolor(RED);
		solidcircle(50 + game.lastx * 40, 50 + game.lasty * 40, 5);
	}
	// ���������Ϣ������·����ӣ�����ʾ
	if(msg.x < 5 && msg.y < 5) return;
	int _x = (msg.x - 25) / 40, _y = (msg.y - 25) / 40;
	if(_x >= 0 && _x < 15 && _y >= 0 && _y < 15 &&
		game.chessboard[_x][_y] == ' ') {
		int x = 50 + _x * 40;
		int y = 50 + _y * 40;
		if(game.white_player_playing)	setfillcolor(LIGHTGRAY);
		else							setfillcolor(DARKGRAY);
		solidcircle(x, y, 15);
	}
	FlushBatchDraw();
}

// ��ť�࣬���ڲ�����Ҫ��ͼ��������ļ���ʹ�ã����Բ�����Graphics Logic.h��
class Button {
public:
	// ���캯��
	Button(int x, int y, int width, int height, const TCHAR *text) noexcept :
		x(x), y(y), width(width), height(height) {
		_tcscpy(this->text, text);
	}
	// ���ư�ť
	void draw(MOUSEMSG &msg) const noexcept {
		if(msg.x >= x && msg.x <= x + width && msg.y >= y && msg.y <= y + height) {
			setfillcolor(RGB(233, 233, 233));
			setbkcolor(RGB(233, 233, 233));
		}
		else {
			setfillcolor(RGB(188, 188, 188));
			setbkcolor(RGB(188, 188, 188));
		}
		fillrectangle(x, y, x + width, y + height);
		if(language == Chinese) {
			settextstyle(20, 0, _T("����"));
		}
		else {
			settextstyle(20, 0, _T("Consolas"));
		}
		settextcolor(RGB(0, 0, 0));
		int textWidth	= textwidth(text);
		int textHeight	= textheight(text);
		// ��֤���־���
		int textX		= x + (width - textWidth) / 2;
		int textY		= y + (height - textHeight) / 2;
		outtextxy(textX, textY, text);
		setbkcolor(RGB(255, 255, 255));
	}
	// ���ظð�ť�Ƿ񱻰���
	bool isClicked(MOUSEMSG &msg) const noexcept {
		return msg.x >= x && msg.x <= x + width && msg.y >= y && msg.y <= y + height &&
			msg.uMsg == WM_LBUTTONDOWN;
	}
private:
	int x, y, width, height;
	TCHAR text[100];
};
// �����ť��fnΪ��Ҫִ�е�����������ӡ���⣬���ر�����İ�ť���±�
template<class Function> int multibutton(const vector<Button> &buttons, Function fn) noexcept {
	MOUSEMSG msg;
	while(true) {
		msg = GetMouseMsg();
		setbkcolor(Board_Background);
		cleardevice();
		fn();
		for(int i = 0; i < buttons.size(); ++i) {
			buttons[i].draw(msg);
			if(buttons[i].isClicked(msg)) {
				return i;
			}
		}
		FlushBatchDraw();
		Sleep(4);
	}
}

RELEASE_INLINE void printmenu(int x, int y, const TCHAR *str) {
	settextcolor(RGB(0, 0, 0));
	if(language == Chinese) {
		settextstyle(50, 0, _T("����"));
	}
	else {
		settextstyle(50, 0, _T("Consolas"));
	}
	int strlen		= textwidth(str);
	int strhight	= textheight(str);
	int countx		= x - (strlen / 2);
	int county		= y - (strhight / 2);
	outtextxy(countx, county, str);
}

const vector<tstring> Menu_buttons_texts = {
	_T("������Ϸ"),		_T("Single player"),
	_T("˫����Ϸ"),		_T("Two players"),
	_T("AI���Ҷ���"),	_T("AI self fight"),
	_T("ѡ��"),			_T("Options"),
	_T("�˳���Ϸ"),		_T("Exit game")
#ifdef _DEBUG
	,_T("�򿪹����ļ�debug"),_T("Open project file to debug")
#endif
};

const vector<tstring> Menu_texts = {
	_T("������"),_T("Five Chess")
};
RELEASE_INLINE int menu() noexcept {
	vector<Button> menu_buttons = {
		Button(280, 250, 120, 50, Menu_buttons_texts[		static_cast<size_t>(language)].c_str()),
		Button(280, 320, 120, 50, Menu_buttons_texts[2 +	static_cast<size_t>(language)].c_str()),
		Button(280, 390, 120, 50, Menu_buttons_texts[4 +	static_cast<size_t>(language)].c_str()),
		Button(280, 460, 120, 50, Menu_buttons_texts[6 +	static_cast<size_t>(language)].c_str()),
		Button(280, 530, 120, 50, Menu_buttons_texts[8 +	static_cast<size_t>(language)].c_str())
		#ifdef _DEBUG
		,Button(50, 600, 200, 50, Menu_buttons_texts[10 +	static_cast<size_t>(language)].c_str()) // ����DEBUGģʽ����Ч
		#endif
	};
	return multibutton(menu_buttons, []() {
		printmenu(340, 100, Menu_texts[language].c_str());
	});
}

const vector<tstring> Options_buttons_texts = {
	_T("�Ƿ񲥷�����"),	_T("Whether to play music"),
	_T("��������"),		_T("Change language"),
	_T("����"),			_T("Return")
};
const vector<tstring> Options_texts = {
	_T("ѡ��"),_T("Options")
};
RELEASE_INLINE void options() noexcept {
	while(true) {
		vector<Button> options_buttons = {
			Button(240, 300, 200, 50, Options_buttons_texts[	static_cast<size_t>(language)].c_str()),
			Button(240, 400, 200, 50, Options_buttons_texts[2 + static_cast<size_t>(language)].c_str()),
			Button(240, 500, 200, 50, Options_buttons_texts[4 + static_cast<size_t>(language)].c_str())
		};
		int choice = multibutton(options_buttons, []() {
			printmenu(340, 100, Options_texts[static_cast<size_t>(language)].c_str());
		});
		if(choice == 0) {
			music_playing = !music_playing;
			if(music_playing) {
				mciSendString(_T("play bgm repeat"), nullptr, 0, nullptr);
			}
			else {
				mciSendString(_T("stop bgm"),		 nullptr, 0, nullptr);
			}
		}
		else if(choice == 1) {
			language = static_cast<Language>((static_cast<int>(language) + 1) % 2);
		}
		else return;
	}
}

const vector<tstring> Side_buttons_texts = {
	_T("����"),		_T("I choose black"),
	_T("����"),		_T("I choose white"),
	_T("����"),		_T("Return")
};
const vector<tstring> Side_texts = {
	_T("ѡ����"),	_T("Choose your side")
};
RELEASE_INLINE int side() noexcept {
	vector<Button> side_buttons = {
		Button(240, 250, 200, 50, Side_buttons_texts[		static_cast<size_t>(language)].c_str()),
		Button(240, 350, 200, 50, Side_buttons_texts[2 +	static_cast<size_t>(language)].c_str()),
		Button(240, 450, 200, 50, Side_buttons_texts[4 +	static_cast<size_t>(language)].c_str())
	};
	return (multibutton(side_buttons, []() {
		printmenu(340, 100, Side_texts[						static_cast<size_t>(language)].c_str());
	}));
}

RELEASE_INLINE void readsettings() noexcept {
	string str;
	while(getline(cin, str)) {
		if(str.find("Language") != string::npos) {
			if(str.find("English") != string::npos) {
				language = English;
			}
			else {
				language = Chinese;
			}
		}
		else if(str.find("Music") != string::npos) {
			if(str.find("Off") != string::npos) {
				music_playing = false;
			}
			else {
				music_playing = true;
			}
		}
	}
}

RELEASE_INLINE void writesettings() noexcept {
	fstream settings("../settings/settings.txt", ios::out);
	cout.rdbuf(settings.rdbuf());
	cout << "Language: ";
	if(language == Chinese) {
		cout << "Chinese"	<< endl;
	}
	else {
		cout << "English"	<< endl;
	}
	cout << "Music: ";
	if(music_playing) {
		cout << "On"		<< endl;
	}
	else {
		cout << "Off"		<< endl;
	}
}