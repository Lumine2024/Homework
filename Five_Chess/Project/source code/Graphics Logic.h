#pragma once
#include "Common.h"
#include "Game Logic.h"
#include <graphics.h>
// ���Ե�ö����
enum Language : char {
	Chinese = 0,
	English = 1
};
// ��ǰ������
// ���е�ȫ�ֱ�������ͷ�ļ��ж���Ҫextern
extern Language language;

// ��д����
RELEASE_INLINE void		readsettings()	noexcept;
RELEASE_INLINE void		writesettings() noexcept;
// ��ӡ��ʾ��Ϣ
RELEASE_INLINE void		printhint(int x, int y, const TCHAR *str);
// ��ռ��ʱ�׳����쳣��
class Occupied {
public:
	// ����ʱ������ʾ
	RELEASE_INLINE		Occupied() noexcept;
};
// ��ʼ������
RELEASE_INLINE void		init() noexcept;
// ��ʼ�˵�
RELEASE_INLINE int		menu() noexcept;
// ��������Ͻǵ������Ϣ
const MOUSEMSG no_msg = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
// ��ʾ����
RELEASE_INLINE void		printboard(const Five_Chess &game, const MOUSEMSG &msg = no_msg) noexcept;
// ѡ�����
RELEASE_INLINE void		options() noexcept;
// ѡ��
RELEASE_INLINE int		side() noexcept;