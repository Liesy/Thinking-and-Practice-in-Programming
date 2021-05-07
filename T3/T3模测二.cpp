#include<bits/stdc++.h>

#define mem(f, v) memset(f,v,sizeof(f))

typedef long long LL;
const int inf = ~(1u << 31u);
const LL linf = ~(1LLu << 63u);

using namespace std;

//第二次T3测试

int print_num = 1;

struct dateTime {
    int year, month, day, hour, mins, sec;

    dateTime() {}

    dateTime(int yy, int mm, int dd, int hh, int mi, int ss)
            : year(yy), month(mm), day(dd), hour(hh), mins(mi), sec(ss) {}

    ////以下对操作符的重载参考https://blog.csdn.net/weixin_44552961/article/details/106392927

    void operator=(const dateTime &t) {
        year = t.year;
        month = t.month;
        day = t.day;
        hour = t.hour;
        mins = t.mins;
        sec = t.sec;
    }

    bool operator<(const dateTime &t) const {
        if (year != t.year) return year < t.year;
        if (month != t.month) return month < t.month;
        if (day != t.day) return day < t.day;
        if (hour != t.hour) return hour < t.hour;
        if (mins != t.mins) return mins < t.mins;
        if (sec != t.sec) return sec < t.sec;
        return false;
    }

    bool operator>(const dateTime &t) const { return t < *this; }

    bool operator<=(const dateTime &t) const { return !(t < *this); }

    bool operator>=(const dateTime &t) const { return !(*this < t); }

    bool operator==(const dateTime &t) const { return !(*this < t || t < *this); }
};

struct player {
    int tasks;
    vector<dateTime> beginTime;
    vector<dateTime> endTime;

    player() { tasks = 0; }
};

struct timeSegment {
    dateTime startTime, overTime;

    bool operator<(const timeSegment &ts) const {
        if (!(startTime == ts.startTime)) return startTime < ts.startTime;
        else return true;
    }
};

class play {
public:
    vector<dateTime> times;
    vector<player> players;
    vector<timeSegment> canPlay;
    vector<timeSegment> meet;
    bool flag;

    play() { flag = true; }

    void init(int m) {
        while (m--) {
            player p;
            dateTime st, et;
            string s;
            cin >> p.tasks;
            for (int i = 1; i <= p.tasks; i++) {
                cin >> st.year >> st.month >> st.day >> st.hour >> st.mins >> st.sec;
                cin >> et.year >> et.month >> et.day >> et.hour >> et.mins >> et.sec;
                cin >> s;
                p.beginTime.emplace_back(st);
                p.endTime.emplace_back(et);
                times.emplace_back(st);
                times.emplace_back(et);
            }
            players.emplace_back(p);
        }
    }

    bool moreThanAnHour(dateTime st, dateTime et) {
        LL sec1 =
                (LL) st.year * 12 * 30 * 24 * 60 * 60 + (LL) st.month + 30 * 24 * 60 * 60 + (LL) st.day * 24 * 60 * 60 +
                (LL) st.hour * 3600 + (LL) st.mins * 60 + (LL) st.sec;
        LL sec2 =
                (LL) et.year * 12 * 30 * 24 * 60 * 60 + (LL) et.month + 30 * 24 * 60 * 60 + (LL) et.day * 24 * 60 * 60 +
                (LL) et.hour * 3600 + (LL) et.mins * 60 + (LL) et.sec;
        if (sec2 - sec1 >= 3600) return true;
        return false;
    }

    void output() {
        cout << "Scenario #" << print_num << ":" << endl;
        print_num++;
        if (!flag) return;//没有可用时间

        sort(canPlay.begin(), canPlay.end());
        for (auto &it:canPlay) {
            if (!moreThanAnHour(it.startTime, it.overTime)) continue;
            cout << "appointment possible from ";
            printf("%02d/%02d/%04d %02d:%02d:%02d", it.startTime.month, it.startTime.day, it.startTime.year,
                   it.startTime.hour, it.startTime.mins, it.startTime.sec);
            cout << " to ";
            printf("%02d/%02d/%04d %02d:%02d:%02d\n", it.overTime.month, it.overTime.day, it.overTime.year,
                   it.overTime.hour, it.overTime.mins, it.overTime.sec);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    int t, m;
    cin >> t;
    while (t--) {
        cin >> m;
        play game;
        game.init(m);
        game.output();
    }
    return 0;
}