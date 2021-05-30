#include <bits/stdc++.h>

#define mem(f, v) memset(f, v, sizeof(f))

typedef long long ll;
const int maxn = 100010;
const int inf = 0x3f3f3f3f;
const ll linf = 0x3f3f3f3f3f3f3f3fll;

using namespace std;

//五月T3 记事本
int n;
int cnt = 0, paste_cnt = 0;
vector<string> txt;
vector<string> paste;//粘贴板
pair<int, int> cursor = make_pair(1, 1);
pair<int, int> cursor_begin;
pair<int, int> cursor_end;
bool shift_on = false;//是否开启了shift
bool selected = false;//是否有字段被选中

void move() {
    selected = false;//光表进行移动出选中状态
    string opt;
    cin >> opt;
    if (opt == "Home") { cursor.second = 1; }
    else if (opt == "End") { cursor.second = (int) txt[cursor.first - 1].size() + 1; }
    else if (opt == "Up") {
        if (cursor.first == 1) return;
        int up_len = (int) txt[cursor.first - 2].size();
        if (up_len + 1 < cursor.second) {
            cursor.first--;
            cursor.second = up_len + 1;
        } else cursor.first--;
    } else if (opt == "Down") {
        if (cursor.first == txt.size()) return;
        int down_len = (int) txt[cursor.first].size();
        if (down_len + 1 < cursor.second) {
            cursor.first++;
            cursor.second = down_len + 1;
        } else cursor.first++;
    } else if (opt == "Left") {
        if (cursor.first == 1 && cursor.second == 1) return;
        else if (cursor.second == 1) {
            cursor.first--;
            cursor.second = (int) txt[cursor.first - 1].size() + 1;
        } else cursor.second--;
    } else if (opt == "Right") {
        if (cursor.first == txt.size() && cursor.second == txt[cursor.first - 1].size() + 1)
            return;
        else if (cursor.second == txt[cursor.first - 1].size() + 1) {
            cursor.first++;
            cursor.second = 1;
        } else cursor.second++;
    }
}

void backspace() {
    if (cursor.first == 1 && cursor.second == 1) return;//在文件开头
    else if (cursor.second == 1) {//在一行的开头
        cursor.second = txt[cursor.first - 2].size() + 1;//光标位置更新
        //合并
        string a = txt[cursor.first - 2] + txt[cursor.first - 1];
        txt[cursor.first - 2] = a;
        txt.erase(txt.begin() + cursor.first - 1, txt.begin() + cursor.first);
        cursor.first--;//光标位置更新
    } else {
        if (txt[cursor.first - 1][cursor.second - 2] != ' ') cnt--; //删除一个字符
        txt[cursor.first - 1].erase(cursor.second - 2, 1);
        cursor.second--;//光标位置前进
    }
}

void clearSelected() {
    selected = false;
    if (cursor_begin.first > cursor.first ||
        (cursor_begin.first == cursor.first && cursor_begin.second >= cursor.second)) {
        swap(cursor_begin.first, cursor.first);
        swap(cursor_begin.second, cursor.second);
    }
    while (cursor_begin != cursor) {
        backspace();
    }
}

void insert() {
    string opt;
    cin >> opt;
    if (opt == "Char") {
        if (selected) clearSelected();//如果被选中了，清空被选中的区域
        selected = false;//退出选中状态

        string c;
        cin >> c;
        txt[(int) cursor.first - 1].insert(cursor.second - 1, c, 0, 1);
        cursor.second++;
        cnt++;
    } else if (opt == "Enter") {
        if (selected) clearSelected();//如果被选中了，清空被选中的区域
        selected = false;//退出选中状态

        if (cursor.second == txt[cursor.first - 1].size() + 1) {//在一行的结尾换行
            txt.insert(txt.begin() + cursor.first, string());
            cursor.first++;
            cursor.second = 1;
        } else {
            //不是在一行的结尾换行
            string a(txt[cursor.first - 1], 0, cursor.second - 1);
            string b(txt[cursor.first - 1], cursor.second - 1, txt[cursor.first - 1].size() - cursor.second + 1);
            txt[cursor.first - 1] = a;
            txt.insert(txt.begin() + cursor.first, b);
            cursor.first++;
            cursor.second = 1;
        }
    } else if (opt == "Space") {
        if (selected) clearSelected();//如果被选中了，清空被选中的区域
        selected = false;//退出选中状态

        string str = " ";
        txt[cursor.first - 1].insert(cursor.second - 1, str, 0, 1);
        cursor.second++;
    } else if (opt == "Paste") {
        if (paste.empty()) return;
        //剪切板不为空
        if (selected) clearSelected();//退出选中状态
        selected = false;
        string a(txt[cursor.first - 1], 0, cursor.second - 1);
        string b(txt[cursor.first - 1], cursor.second - 1, txt[cursor.first - 1].size() - cursor.second + 1);
        a += paste[0];
        txt[cursor.first - 1] = a;
        //处理n-1行
        for (int k = 1; k < paste.size(); k++) {
            cursor.first++;
            txt.insert(txt.begin() + cursor.first - 1, paste[k]);
        }
        cursor.second = txt[cursor.first - 1].size() + 1;
        //处理最后一行
        txt[cursor.first - 1] += b;
        cnt += paste_cnt;
    }
}

void remove() {
    string opt;
    cin >> opt;
    if (!selected && opt == "Del") {
        //当前在文件的末尾位置
        if (cursor.first == txt.size() && cursor.second == txt[cursor.first - 1].size() + 1)
            return;
        else if (cursor.second == txt[cursor.first - 1].size() + 1) {
            //将两行合并,光标位置不更新
            string a = txt[cursor.first - 1] + txt[cursor.first];
            txt[cursor.first - 1] = a;
            txt.erase(txt.begin() + cursor.first, txt.begin() + cursor.first + 1);
        } else {
            //删除一个字符,光标位置不变
            if (txt[cursor.first - 1][cursor.second - 1] != ' ') cnt--;
            txt[cursor.first - 1].erase(cursor.second - 1, 1);
        }
    } else if (!selected && opt == "Backspace") {
        backspace();
    } else if (selected) {
        clearSelected();
    }
}

void shift() {
    if (!shift_on && !selected) {//如果之前没有开启shift,也没有被选中，将开启shift,
        shift_on = true;
        selected = false;//还没有区域被选中
        //当前位置为记录点
        cursor_begin.first = cursor.first;
        cursor_begin.second = cursor.second;
    } else if (shift_on) {//之前已经开启shift了，将进入选中状态
        shift_on = false;
        selected = true;
        cursor_end.first = cursor.first;
        cursor_end.second = cursor.second;
        if (cursor_begin == cursor)//光标没动
            selected = false;
    } else if (!shift_on && selected) {
        //在选中状态下进入粘滞状态
        //保留上次的记录点为当前的记录点
        shift_on = true;
        selected = false;
    }
}

void find() {
    string str;
    cin >> str;
    int cnt_cmp = 0;
    if (!selected) {
        for (auto & temp : txt)
            for (int j = 0; j < temp.size(); j++) {
                if (temp.size() - j < str.size()) break;
                if (temp[j] == str[0]) {
                    bool com = true;
                    for (int k = 0; k < str.size(); k++)
                        if (temp[j + k] != str[k]) {
                            com = false;
                            break;
                        }
                    if (com)
                        cnt_cmp++;
                }
            }
        cout << cnt_cmp << '\n';
    } else {
        pair<int, int> pos = cursor_begin;
        pair<int, int> pos_end = cursor;
        if (pos > pos_end)
            swap(pos, pos_end);
        int i = pos.first - 1;
        int j = pos.second - 1;
        for (; i < pos_end.first - 1; i++) {
            for (; j < txt[i].size(); j++) {
                if (txt[i].size() - j < str.size()) break;
                if (txt[i][j] == str[0]) {
                    bool com = true;
                    for (int k = 0; k < str.size(); k++)
                        if (txt[i][j + k] != str[k]) {
                            com = false;
                            break;
                        }
                    if (com)
                        cnt_cmp++;
                }
            }
            j = 0;
        }
        for (j = 0; j < pos_end.second - 1; j++) {
            if (txt[i].size() - j < str.size()) break;
            if (txt[i][j] == str[0]) {
                bool com = true;
                for (int k = 0; k < str.size(); k++)
                    if (txt[i][j + k] != str[k]) {
                        com = false;
                        break;
                    }
                if (com)
                    cnt_cmp++;
            }
        }
        cout << cnt_cmp << '\n';
    }
}

void count() {
    if (!selected) {
        cout << cnt << endl;
    } else {
        int cnt_a = 0;
        pair<int, int> pos = cursor_begin;
        pair<int, int> pos_end = cursor;
        if (pos > pos_end)
            swap(pos, pos_end);
        int i = pos.first - 1;
        int j = pos.second - 1;
        for (; i < pos_end.first - 1; i++) {
            for (; j < txt[i].size(); j++) {
                if (txt[i][j] != ' ')
                    cnt_a++;
            }
            j = 0;
        }
        for (; j < pos_end.second - 1; j++)
            if (txt[i][j] != ' ')
                cnt_a++;
        cout << cnt_a << '\n';
    }
}

void copy() {
    if (!selected && !txt[cursor.first - 1].empty()) {
        //当前行不为空
        paste.clear();
        paste.emplace_back(txt[cursor.first - 1]);
        paste_cnt = 0;
        for (char x : paste[0])
            if (x != ' ') paste_cnt++;
    } else if (selected) {
        paste.clear();
        //当标记点和光标出在同一行的时候
        pair<int, int> pos = cursor_begin;
        pair<int, int> pos_end = cursor;
        if (pos > pos_end)
            swap(pos, pos_end);
        //当标记点和光标出在同一行的时候
        if (pos.first == pos_end.first) { //被选中的字段为空？？怎么办
            string a(txt[cursor.first - 1], pos.second - 1, pos_end.second - pos.second);
            paste.push_back(a);
        } else {
            //不在同一行的时候
            string a(txt[pos.first - 1], pos.second - 1, txt[pos.first - 1].size() - pos.second + 1);
            string b(txt[pos_end.first - 1], 0, pos_end.second - 1);
            paste.push_back(a);
            pos.first++;
            for (; pos.first < pos_end.first; pos.first++)
                paste.push_back(txt[pos.first - 1]);
            paste.push_back(b);
        }
        paste_cnt = 0;
        for (auto & temp : paste)
            for (int j = 0; j < temp.size(); j++)
                if (temp[j] != ' ') paste_cnt++;
    }
}

int main() {
    cin >> n;
    txt.emplace_back(string());
    string order;
    for (int i = 0; i < n; i++) {
        cin >> order;
        if (order == "MOVE")
            move();
        else if (order == "INSERT")
            insert();
        else if (order == "REMOVE")
            remove();
        else if (order == "SHIFT")
            shift();
        else if (order == "FIND")
            find();
        else if (order == "COUNT")
            count();
        else if (order == "COPY")
            copy();
        else if (order == "PRINT") {
            for (int j = 0; j < txt.size(); j++)
                cout << txt[j] << '\n';
        }
    }
    return 0;
}