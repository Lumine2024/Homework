#include "Graphics Logic.h"
#include "Game Logic.h"
#include "Search_AI.h"
#include <iostream>
#include <fstream>
#pragma comment(lib,"winmm.lib")
using namespace std;

int WINAPI WinMain(_In_ HINSTANCE hin, _In_opt_ HINSTANCE hp, _In_ LPSTR cmd, _In_ int ncmd) {
	init(); // �������á���ʾ��Ϸ���沢��������
	while(true) { // ��Ϸѭ��
		int choice = menu(); // ͨ���˵����ķ���ֵ��ȡ���ѡ��
		switch(choice) {
			case 0: { // ������Ϸ
				int			_side = side(); // ѡ�ߣ�0Ϊ���ӣ�1Ϊ���ӣ�2Ϊ����
				Five_Chess	fc;
				Search_AI	ai;
				Human		h;
				if		(_side == 2)	break; // �������˵�
				else if	(_side == 1)	fc.putchess(7, 7); // ���ѡ����ӣ��������м�ֱ�Ӱڷ�һ�ź���
				playgame(fc, &h, &ai); // ������Ϸ
				break;
			} // case 0
			case 1: { // ˫����Ϸ
				Five_Chess	fc;
				Human		h;
				playgame(fc, &h, &h); // �������ҶԿ�
				break;
			} // case 1
			case 2: { // AI���Ҷ���
				// Ϊ�˸�AI�Ծ���������������ԣ����ǹ̶���һ���ӷ������룬�ڶ�������������������Χ
				Five_Chess		fc;
				char			ch = ' ';
				Search_AI		ai;
				SYSTEMTIME		time; // �Ե�ǰ��ʱ����Ϊ�����ڶ����ӵ�����λ��
				GetLocalTime(&time);
				fc.putchess(7, 7);
				printboard(fc);
				FlushBatchDraw();
				int				_x = time.wMilliseconds % 3 - 1,
								_y = (time.wMilliseconds / 3) % 3 - 1;
				if(_x == 0 && _y == 0) ++_y; // �������������ص�
				Sleep(500);
				fc.putchess(7 + _x, 7 + _y);
				printboard(fc);
				FlushBatchDraw();
				Sleep(500);
				playgame(fc, &ai, &ai, true);
				break;
			} // case 2
			case 3: { // ѡ��
				options();
				break;
			}
			case 4: { // �˳���Ϸ
				writesettings();
				closegraph();
				return 0;
			}
		#ifdef _DEBUG
			case 5: {// ��DEBUGģʽ�����½ǻ��С��򿪱���������DEBUG����ѡ�����������ҵı����ļ����Ӷ������ҽ���DEBUG
				ShellExecute(nullptr, _T("open"), _T("D:/�ĵ�/Visual Studio 2022/C++/Five_Chess/Five_Chess.sln"), 0, 0, SW_SHOWNORMAL);
				writesettings();
				closegraph();
				return 0;
			}
		#endif
			default: __assume(false);
		}
	}
}