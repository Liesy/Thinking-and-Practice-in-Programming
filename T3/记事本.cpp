#include<bits/stdc++.h>

#define mem(f, v) memset(f,v,sizeof(f))

typedef long long ll;
const int maxn = 5010;
const int inf = ~(1u << 31u);
const ll linf = ~(1LLu << 63u);

using namespace std;

//五月T3 记事本
int n;
char ch;
string option1, option2, str;

struct Cursor {
    int row;
    int column;

    Cursor() { row = 1, column = 0; }
};

struct paste {//粘贴板
    Cursor start;
    Cursor over;

    paste() {
        start.row = 1, start.column = 0;
        over.row = 1, over.column = 0;
    }
};

string txt[maxn];//记事本
int end_index = 1;//最后一行的索引
Cursor cursorNow;//当前光标位置
Cursor cursorRec;//记录点的光标位置
bool shift = false;//粘滞

bool atEnd(Cursor cur) {
    if (cur.column == txt[cur.row].size())
        return true;
    return false;
}

void move() {
    if (option2 == "Home") {//移至当前行的开头
        cursorNow.column = 0;
        return;
    }
    if (option2 == "End") {//移至当前行的末尾
        cursorNow.column = txt[cursorNow.row].size();
        return;
    }
    if (option2 == "Up") {
        if (cursorNow.row == 1)
            return;
        cursorNow.row--;
        if (txt[cursorNow.row].size() < cursorNow.column)
            cursorNow.column = txt[cursorNow.row].size();
        return;
    }
    if (option2 == "Down") {
        if (cursorNow.row >= end_index)
            return;
        cursorNow.row++;
        if (txt[cursorNow.row].size() < cursorNow.column)
            cursorNow.column = txt[cursorNow.row].size();
        return;
    }
    if (option2 == "Left") {
        if (cursorNow.row == 1 && cursorNow.column == 0)
            return;
        if (cursorNow.column == 0) {
            cursorNow.row--;
            cursorNow.column = txt[cursorNow.row].size();
            return;
        }
        cursorNow.column--;
        return;
    }
    if (option2 == "Right") {
        if (cursorNow.row >= end_index && atEnd(cursorNow))
            return;
        if (atEnd(cursorNow)) {
            cursorNow.row++;
            cursorNow.column = 0;
            return;
        }
        cursorNow.column++;
        return;
    }
}

void insert() {
    if (option2 == "Char") {
        if (cursorNow.row > end_index)
            end_index = cursorNow.row;
        if (atEnd(cursorNow))
            txt[cursorNow.row].push_back(ch);
        else
            txt[cursorNow.row].insert(cursorNow.column, 1, ch);
        cursorNow.column++;
        return;
    }
    if (option2 == "Enter") {
        if (cursorNow.row >= end_index && atEnd(cursorNow)) {//在文章末尾
            cursorNow.row++;
            cursorNow.column = 0;
            return;
        }
        //全部后移
        end_index++;
        for (int i = end_index - 1; i >= cursorNow.row + 1; i--) txt[i + 1] = txt[i];
        txt[cursorNow.row + 1].clear();
        if (!atEnd(cursorNow)) {
            //截断
            str = txt[cursorNow.row].substr(cursorNow.column);
            //换行
            txt[cursorNow.row + 1] = str;
            //同
            str = txt[cursorNow.row].substr(0, cursorNow.column);
            txt[cursorNow.row] = str;
        }
        cursorNow.row++, cursorNow.column = 0;
        return;
    }
    if (option2 == "Space") {
        if (cursorNow.row > end_index)
            end_index = cursorNow.row;
        if (atEnd(cursorNow))
            txt[cursorNow.row].push_back(' ');
        else
            txt[cursorNow.row].insert(cursorNow.column, 1, ' ');
        cursorNow.column++;
        return;
    }
    if (option2 == "Paste") {
        return;
    }
}

void remove() {
    if (option2 == "Del") {
        if (atEnd(cursorNow)) {
            if (cursorNow.row >= end_index)
                return;
            txt[cursorNow.row] += txt[cursorNow.row + 1];
            end_index--;
            for (int i = cursorNow.row + 1; i <= end_index; i++) txt[i] = txt[i + 1];
            txt[end_index + 1].clear();
            return;
        }
        txt[cursorNow.row].erase(cursorNow.column, 1);
        return;
    }
    if (option2 == "Backspace") {
        if (cursorNow.row > end_index && atEnd(cursorNow)) {//在文章末尾
            cursorNow.row--;
            if (cursorNow.row == end_index)
                cursorNow.column = txt[cursorNow.row].size();
            return;
        }
        if (cursorNow.column == 0) {
            if (cursorNow.row == 1)
                return;
            cursorNow.row--;
            cursorNow.column = txt[cursorNow.row].size();
            txt[cursorNow.row] += txt[cursorNow.row + 1];
            end_index--;
            for (int i = cursorNow.row + 1; i <= end_index; i++) txt[i] = txt[i + 1];
            txt[end_index + 1].clear();
            return;
        }
        txt[cursorNow.row].erase(cursorNow.column - 1, 1);
        cursorNow.column--;
        return;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    while (n--) {
        cin >> option1;
        if (option1 == "MOVE") {
            cin >> option2;
            move();
        } else if (option1 == "INSERT") {
            cin >> option2;
            if (option2 == "Char")
                cin >> ch;
            insert();
        } else if (option1 == "REMOVE") {
            cin >> option2;
            remove();
        } else if (option1 == "SHIFT") {
        } else if (option1 == "FIND") {
        } else if (option1 == "COUNT") {
        } else if (option1 == "COPY") {
        } else if (option1 == "PRINT") {
            for (int i = 1; i <= end_index; i++)
                cout << txt[i] << '\n';
            cout << '\n';
        }
    }
    return 0;
}