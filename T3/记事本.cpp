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
int end_index;//最后一行的索引
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
        if (cursorNow.row == end_index)
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
        if (cursorNow.row == end_index && atEnd(cursorNow))
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
        if (atEnd(cursorNow))
            txt[cursorNow.row].push_back(ch);
        else
            txt[cursorNow.row].insert(cursorNow.column, 1, ch);
        return;
    }
    if (option2 == "Enter") {
        //全部后移
        end_index++;
        auto it = begin(txt);
        copy_backward(it + cursorNow.row + 1, it + end_index, it + end_index);
        if (!atEnd(cursorNow)) {
            //截断
            str = txt[cursorNow.row].substr(cursorNow.column);
            txt[cursorNow.row] = txt[cursorNow.row].substr(0, cursorNow.column);
            //换行
            txt[cursorNow.row + 1] = str;
        }
        return;
    }
    if (option2 == "Space") {
        if (atEnd(cursorNow))
            txt[cursorNow.row].push_back(' ');
        else
            txt[cursorNow.row].insert(cursorNow.column, 1, ' ');
        return;
    }
    if (option2 == "Paste") {
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
        } else if (option1 == "SHIFT") {
        } else if (option1 == "FIND") {
        } else if (option1 == "COUNT") {
        } else if (option1 == "COPY") {
        } else if (option1 == "PRINT") {
        }
    }
    return 0;
}