#include <iostream>
#include <vector>
#include <set>
#include <new>
using namespace std;
//#define _DBG
#ifdef _DBG
#define PRIVATE public
#else
#define PRIVATE private
#endif
template<class _Ty, class _Pr = less<_Ty>, class _Eq = equal_to<_Ty>>
class skiplist {
public:
    using value_type = _Ty;
    using pointer = _Ty*;
    using reference = _Ty&;
    using const_reference = const _Ty&;
    using size_type = size_t;
PRIVATE:
    struct _Node {
        value_type _Myval;
        vector<_Node*> _Forward;
        _Node(int _Val, int _Level) : _Myval(_Val), _Forward(_Level + 1, nullptr) {}
        ~_Node() = default;
    };
    struct _Gen_bool {
        _Gen_bool() {
            srand(time(0));
        }
        bool _Getbool() {
            return rand() % 2;
        }
        bool operator()() {
            return rand() % 2;
        }
    };
public:
    skiplist() : _Nodecnt(0), _Level(0), _Dummy(new _Node(0, max_level)) {}
    skiplist(const initializer_list<value_type>& _Ilist)
        : _Nodecnt(_Ilist.size()), _Dummy(new _Node(0, max_level)) {
        for (const auto& elem : _Ilist) {
            insert(elem);
        }
    }
    skiplist(const skiplist<_Ty, _Pr, _Eq>& other) : _Nodecnt(other._Nodecnt),
        _Dummy(new _Node(0, max_level)), _Controller(other._Controller),
        _Compare(other._Compare), _Equal(other._Equal) {
        _Node* curr = other._Dummy->_Forward[0];
        while (curr) {
            insert(curr->_Myval);
            curr = curr->_Forward[0];
        }
    }
    ~skiplist() {
        _Node* curr = _Dummy;
        while (curr) {
            _Node* tmp = curr;
            curr = curr->_Forward[0];
            delete tmp;
        }
    }
    bool search(const_reference _Val) const {
        _Node* curr = _Dummy;
        for (int i = static_cast<int>(_Level); i >= 0; --i) {
            while (curr->_Forward[i]) {
                if (_Equal(_Val, curr->_Forward[i]->_Myval)) {
                    return true;
                }
                else if (_Compare(curr->_Forward[i]->_Myval, _Val)) {
                    curr = curr->_Forward[i];
                }
                else {
                    break;
                }
            }
        }
        return false;
    }
    void insert(const_reference _Val) {
        vector<_Node*> update(max_level + 1, nullptr);
        _Node* curr = _Dummy;
        for (int i = static_cast<int>(_Level); i >= 0; --i) {
            while (curr->_Forward[i]) {
                if (_Compare(curr->_Forward[i]->_Myval, _Val)) {
                    curr = curr->_Forward[i];
                }
                else {
                    break;
                }
            }
            update[i] = curr;
        }
        size_t level = _Get_random_level();
        if (level > _Level) {
            level = _Level + 1;
            update[level] = _Dummy;
            _Level = level;
        }
        _Node* newnode = new _Node(_Val, level);
        for (size_t i = 0; i <= level; ++i) {
            newnode->_Forward[i] = update[i]->_Forward[i];
            update[i]->_Forward[i] = newnode;
        }
        ++_Nodecnt;
    }
    bool erase(const_reference _Val) {
        _Node* curr = _Dummy;
        for (int i = static_cast<int>(_Level); i >= 0; --i) {
            while (curr->_Forward[i]) {
                if (_Equal(_Val, curr->_Forward[i]->_Myval)) {
                    _Node* to_erase = curr->_Forward[i];
                    for (int j = i; j >= 0; --j) {
                        while (!_Equal(curr->_Forward[j]->_Myval, _Val)) {
                            curr = curr->_Forward[j];
                        }
                        curr->_Forward[j] = to_erase->_Forward[j];
                    }
                    delete to_erase;
                    --_Nodecnt;
                    return true;
                }
                else if (_Compare(curr->_Forward[i]->_Myval, _Val)) {
                    curr = curr->_Forward[i];
                }
                else {
                    break;
                }
            }
        }
        return false;
    }
    size_type size() const {
        return _Nodecnt;
    }
    size_type level() const {
        return _Level;
    }
    void display() const {
        for (int i = static_cast<int>(_Level); i >= 0; --i) {
            cout << "level " << i << ": ";
            _Node* node = _Dummy->_Forward[i];
            while (node != nullptr) {
                cout << node->_Myval << " ";
                node = node->_Forward[i];
            }
            cout << endl;
        }
        cout << endl;
    }
PRIVATE:
    size_t _Get_random_level() {
        for (size_t ret = 0; ret < max_level; ++ret) {
            if (!_Controller._Getbool()) return ret;
        }
        return max_level - 1;
    }
PRIVATE:
    _Node* _Dummy;
    size_type _Level, _Nodecnt;
    _Gen_bool _Controller;
    _Pr _Compare;
    _Eq _Equal;
public:
    static constexpr size_type max_level = 32ULL;
};
int main() {
    skiplist<int> lst = { 2,3,4,5,6 };
    lst.display();
    lst.insert(5);
    lst.display();
    lst.erase(3);
    lst.display();
    skiplist<int> lst2 = lst;
    lst2.display();
    return 0;
}
