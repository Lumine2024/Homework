# 2024�����ݽṹ���㷨A��

# �γ����: ������AI

## ������

## 2024080902024

### һ��ʵ�������ƣ�

���ӿƼ���ѧ��ˮ��У��Ʒѧ¥C222

### ����ʵ����Ŀ���ƣ�

����̰���㷨��������������㷨��������AI

### ����ʵ�鲽�裺

1. ��������
> ��������һ�����˶��ĵĲ�����������Ϸ����Ҫ����������Ͻ��кڰ��ӵĽ�����ã�
Ŀ���������ںᡢ����б���������������ͬ�����ӡ�
��ˣ�Ϊ��ʵ��������AI��������Ҫ���һ���ܹ�������Ч���Ծ��ߺ��������㷨������������ʵ�֡�
���ҵ���Ŀ�У��Ҳ������������������̰���㷨ʵ��������ʹ�����Ӻ��Ƿ����ڵ���������ʵ��������

2. �㷨�������Ҫ���
> �ڱ���Ŀ�У���������ʹ�õ�������EasyXʵ����������Ľ���GUI�Ա��û������͵��ԣ�
�������������������̰���㷨��˼�룬ģ�������˼��ģʽдAI����������뷽����

> �������GUI��������ʹ��EasyXʵ�֡�
����EasyX��δ�ṩ���ư�ť�Ľӿڣ��ڲ˵������棬�����ֶ����尴ť�ಢ�������ư�ť�ķ���multibutton��
�������Ǹ�����̬��������״̬�ķ���printboard��
�������͡���һ�����ӵĵص������λ�ö�Ӧ�����ӵ㣬������ҽ��з������ơ�

> �������������Depth-First Search, DFS����һ�ֱ��������㷨��
�ᾡ��������������ķ�֧����ĳһ�ڵ�����ڱ߶�����̽Ѱ�������������ݵ����ָýڵ�������ߵ���ʼ�ڵ㡣
̰���㷨��Greedy Algorithm����һ����ÿһ��ѡ���ж���ȡ�ڵ�ǰ״̬����û����ţ�������������ѡ��
�Ӷ�ϣ�����½������û����ŵ��㷨��
Ȼ�������Ӵ�����������̣�15x15���������������ѣ�ʱ�临�ӶȾ޴󣻶���������̰���㷨���ֻ�ʹ��AI���ӣ�
��������б�Ҫ�������㷨���н�ϡ�
���ҵĴ���ʵ���У��ҽ�������������㷨��̰���㷨��ϣ�ֻ�Ե����������ĵ�������һ�㣬
�������Ա�֤����Ч���㹻���ͬʱ�����Ծ�ȷ���ӵ���ѵص㡣

3. �����㷨����ϸ�����ʵ��
   
	3.1. �������ͼ�ν����ʤ���ж�
   
	3.1.1. �˵���
> �˵�����Ҫʵ���������ܣ�������û�������
> Ϊ��ʵ���û����������Ƕ��尴ť�ࣻ
> ͬʱ��Ϊ�˲˵������Դ�ӡ���ֱ��⣬���ǽ�ʹ�ð�ť�ĺ�������Ϊģ�庯��������һ��lambda���ʽ��
> �Ӷ����Դ�ӡ���ֱ��⡣
```cpp
// source_code/Graphics Logic.cpp
// ��ť�࣬���ڲ�����Ҫ��ͼ��������ļ���ʹ�ã����Բ�����Graphics Logic.h��
class Button {
public:
	// ���캯��
	Button(int x, int y, int width, int height, const TCHAR *text) noexcept :
		x(x), y(y), width(width), height(height) {
		_tcscpy(this->text, text);
	}
	// ���ư�ť
	void draw(MOUSEMSG &msg) const noexcept;
	// ���ظð�ť�Ƿ񱻰���
	bool isClicked(MOUSEMSG &msg) const noexcept;
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
// Ӧ��ʾ������ѡ�ߺ����е���multibutton����
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
```

3.1.2 ���̽���
  
> ���̽����������һ��15x15�Ŀ����̣�
> �ٸ��ݴ����Five_Chess������������Ӧ�����������
> ���������һ�ε����������ʾ�������������Ϣ��ʾ����ڴ˴������ӵĵص㡣
```cpp
// source_code/Graphics Logic.cpp
RELEASE_INLINE void printboard(const Five_Chess &game, const MOUSEMSG &msg) noexcept {
	setbkcolor(Board_Background);
	cleardevice();
	// ��������
	setlinecolor(BLACK);
	for(int i = 0; i < 15; ++i) {
		int offset = 50 + i * 40;
		line(50,		offset, 	610,		offset);
		line(offset,	50,		offset, 	610);
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
		else					setfillcolor(DARKGRAY);
		solidcircle(x, y, 15);
	}
	FlushBatchDraw();
}
```
3.1.3. �ж�ʤ���߼�
> ���ж��������Ƿ���������������ɡ�
3.2. �������AI�㷨
> �ҵ�AI�㷨��������������ľ��飺�Է������Ž⣬�������ҵ����Ž⡣
> ԭ��ܼ򵥣��Է����������������飬�Ҿ�Ҫ�������ס�Է����Է�����������ģ��Ҿ�Ҫ�������ס��
> ������˵���Է������������ס�ң���˵���������������
  
> ���ҵ�AI�㷨�У���ÿһ���ո��ӽ��з���ֵ���㡣
> ����ֵ�Ĺ���������㣺ĳ�����Ӹ����Ƿ������ӣ��Լ������Ƿ���һ�������ڵ���
> ��ÿһ��������У������õ������������пո��ӣ�������Щ�������Ŀո��ӽ��еݹ�������
> ���յõ������������ﵽ�����õ�������ʱ�����ܵõ����������ĸ��ӣ������յ��������ڴ˴���
```cpp
// source_code/Search_AI.h
// ����AI��
class Search_AI : public Player_Base {
public:
	using score_t = unsigned long long;
	Search_AI	(int md = 14) : maxdepth(md), max_of_judgement(0ULL) {}
	void	judge	(const Five_Chess &fc)		noexcept override;
	void	put	(Five_Chess &fc)		noexcept override;
private:
	score_t put	(Five_Chess &fc, int depth) noexcept;			// �ݹ��put��������д��put�������ڴ˺���ʵ��
	std::vector<std::vector<score_t>>	judgement;			// ʹ��judgement����洢ÿһ�����ӵĹ�ֵ
	score_t					max_of_judgement;		// �����ж����ֵ���ռ任ʱ��
	int					maxdepth;			// ������
	static constexpr score_t		inf = static_cast<score_t>(-1) >> 4; // �������4�������
	static constexpr score_t		score_ref[5] = { 1ull, 1ull << 5, 1ULL << 12, 1ULL << 23, 1ULL << 40 }; // �������Ͷ�Ӧ�ĵ÷ֹ�ֵ����
};
// source_code/Search_AI.cpp
Search_AI::score_t Search_AI::put(Five_Chess &fc, int depth) noexcept {
    // ���ж�
    judge(fc);
    // �������ֵ�ĵ�
    vector<pair<int, int>> max_positions;
    // �ݹ鵽�����ֱ�ӷ���
    if(depth >= maxdepth) {
        return max_of_judgement;
    }
    // �����ֵΪ0ʱ��˵����Ϸ��Ϊƽ��
    if(max_of_judgement == 0 && depth == 0) {
        auto [x, y] = fc.generate_possible_moves()[0];
        fc.putchess(x, y);
        return 0ULL;
    }
    else {
        // ��ȡ�����������е�
        for(auto [row, col] : fc.generate_possible_moves()) {
            // ������С��һ��ֵ
            if((abs(static_cast<double>(judgement[row][col] - max_of_judgement))
                / static_cast<double>(max_of_judgement)) < 0.03 &&
                judgement[row][col] != 0) {
                max_positions.emplace_back(row, col);
            }
        }
        // ������ĵ�ֻ��һ����ֱ�ӷ���
        if(max_positions.size() == 1) {
            auto [row, col] = max_positions[0];
            fc.putchess(row, col);
            // ���У���Ϸ�Ƿ����
            char winner;
            if(fc.has_ended(winner)) {
                if(depth != 0) fc.rmchess(row, col); // ֻ�е���Ȳ�Ϊ0ʱ����Ҫ�Ƴ�������
                return  inf * static_cast<double>((maxdepth - depth + 2)) / static_cast<double> (maxdepth);
            }
            judge(fc);
            score_t score = max_of_judgement;
            if(depth != 0) fc.rmchess(row, col);
            else return static_cast<score_t>(-1);
            return      score * static_cast<double>((maxdepth - depth + 2)) / static_cast<double>(maxdepth);
        }
        int best_row = -1, best_col = -1;
        score_t max_score = 0ull;
        // ����ÿһ�����ĵ㣬�ݹ������ڼ������ӵ�����£���Ӧ�����ĵ�
        for(auto [row, col] : max_positions) {
            fc.putchess(row, col);
            char winner;
            if(fc.has_ended(winner)) {
                if(depth != 0) {
                    fc.rmchess(row, col);
                }
                return  inf * static_cast<double>((maxdepth - depth + 2)) / static_cast<double>(maxdepth);
            }
            judge(fc);
            score_t current_score = put(fc, depth + 1);
            if(max_score < current_score) {
                max_score = current_score;
                best_row = row, best_col = col;
            }
            fc.rmchess(row, col);
        }
        // ������Ϊ0������������
        if(depth == 0) {
            fc.putchess(best_row, best_col);
            return static_cast<score_t>(-1);
        }
        else {
            return      max_score * static_cast<double>((maxdepth - depth + 2)) / static_cast<double>(maxdepth);
        }
    }
}
```
### �ġ�ʵ�����ݼ����������
ʵ�����������ҵ�AI��Ȼ������һ���������̲����ӵ�������������ͬѧ�Ķ�����ȡ���˲���ĳɹ�����ԶԶ����ͬѧ�ǵ�AI�����ϵ�AI��

���ҵ�AI������з�����֪���ҵ�AI�ںܶ෽������Ƿȱ��
���磬�������ͼ����������ҵ�AI��ִ�ڣ������ӵ���Ȧ������Ϊ���ҵĴ����ʵ���У���������ֿ��ܻ���ߣ���ʵ�������ӵ��˴������ܽ�����Ӽ���ʤ�������⡣

���⣬�ҵ�AI�Ա߽������Ĵ�����Ȼ�����������⵼���ҵ�AI���ܻ����ӵ��߽��ϸ�������������������ĵص㣬�����Ч���ӡ�
�Լ�������ͬѧ�Ļ���Alpha-Beta��֦�㷨��AI�Ķ��ĵ��У��ҵ�AIչ�ֳ��˽ϴ�����ơ�����Ϊ�������Ҳ������ԭ���йأ��ʵ��Ż����ֺ����ͱ߽����������ܻ�ʹ�ҵ�AIս��������

### �塢�ܽἰ�ĵ���᣺

��ʵ���У��ҵ�AI�㷨���ֳ���һ���ľ����ԡ����ֺ������õĲ������ݹ��е��߼���������⵼�����ҵ�AI��δ��ú�ǿ��ս������
�ڱ��ε�ʵ���У�����ʶ��������ͬ����֮��Ĳ�࣬ͬʱҲ��ȷ���ҽ������ļƻ������߼����㷨������¹���ͨ��������ѵ��ӵ���㹻���㷨����������
�Ӷ����Ը��������������ɸ��Ӹ��ӵ���ʵ���⡣

���⣬��ʵ���У��������ʶ������ǿ����ɶ��Եı�Ҫ�ԡ�
��һ��ʼ���ҵĴ����Եø���ӷ�ף����Ÿ��ֲ���Ҫ�Ŀ����������ͷ���������Ŀɶ���Ҳ�쳣�
�����ҵĶ����ع�֮�£�����Ŀɶ�����ǿ����࣬�ҶԴ�����޸����޲��ٶ�Ҳ�ӿ��˲��١�
��˵����д����ʱ�������õ������淶������ע�ͣ����������Ǹ��õ���д����Ĵ��룬Ҳ�����ں���ά�����޸ġ�

### �����Ա�ʵ����̼��������ֶεĸĽ����鼰չ����

�ڹ����У�����Ϊ���������ø�����ı��ϰ�ߣ��������õ����������ȹ淶�������ں���Debug������¹���ʱ��ʹ�ࡣ

�ڷ����ϣ�����Ϊ���Ը��õı�д�ҵ����ֺ��������Ӹ����Լ��ķ������Ȩ�ص��㷨��ʹ�ø����ӵ��߼��͸��ϸ���㷨��ʵ�ָ���ȷ�����ֺ������Ӷ����õ����ӣ�����AI��ʵ����

���ֶ��ϣ�����Ϊ���Ա�д���Ͻ��ı߽紦�������������������ڱ߽紦�����Ч���ӴӶ�ʧ�ȵĿ����ԣ�����AI���Ĵ��󣬴Ӷ�����ʤ�㡣

-----------

![ս����.jpg](���Ǹ�ս���������Զ��򲻹�.png)
