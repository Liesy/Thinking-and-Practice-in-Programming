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

    void init() {
        int m;
        scanf("%d", &m);
        while (m--) {
            player p;
            dateTime st, et;
            string s;
            scanf("%d",&p.tasks);
            for (int i = 1; i <= p.tasks; i++) {
                scanf("%d%d%d%d%d%d",&st.year,&st.month,&st.day,&st.hour,&st.mins,&st.sec);
                scanf("%d%d%d%d%d%d",&et.year,&et.month,&et.day,&et.hour,&et.mins,&et.sec);
                getline(cin,s);
                p.beginTime.emplace_back(st);
                p.endTime.emplace_back(et);
                times.emplace_back(st);
                times.emplace_back(et);
            }
            players.emplace_back(p);
        }
    }

    bool canplay(dateTime t1, dateTime t2) {
        int absence = 0;
        for (auto &it:players)
            for (int i = 0; i < it.tasks; i++)
                if (t1 >= it.beginTime[i] && t2 <= it.endTime[i]) {
                    absence++;
                    break;
                }
        if (absence >= 2) return false;
        if (players.size() <= 1) return false;
        if (players.size() == 2 && absence == 1) return false;
        return true;
    }

    void merge() {
        if (meet.empty()) {
            flag = false;
            return;;
        }
        flag = true;
        dateTime t1 = meet[0].startTime, t2 = meet[0].overTime;
        for (int i = 1; i < meet.size(); i++) {
            if (meet[i].startTime == t2) {
                t2 = meet[i].overTime;
                continue;
            } else {
                timeSegment ts;
                ts.startTime = t1, ts.overTime = t2;
                canPlay.emplace_back(ts);
                t1 = meet[i].startTime;
                t2 = meet[i].overTime;
            }
        }
        //最后一段还未处理
        timeSegment ts;
        ts.startTime = t1, ts.overTime = t2;
        canPlay.emplace_back(ts);
    }

    void process() {
        dateTime t1(1800, 1, 1, 0, 0, 0), t2(2200, 1, 1, 0, 0, 0);
        times.emplace_back(t1), times.emplace_back(t2);
        sort(times.begin(), times.end());
        //去重
        times.erase(unique(times.begin(), times.end()), times.end());
        sort(times.begin(), times.end());

        t1 = times[0];
        for (int i = 1; i < times.size(); i++) {
            t2 = times[i];
            if (canplay(t1, t2)) {
                timeSegment ts;
                ts.startTime = t1, ts.overTime = t2;
                meet.emplace_back(ts);
            }
            t1 = t2;
        }
        merge();
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
            printf("appointment possible from %02d/%02d/%04d %02d:%02d:%02d to %02d/%02d/%04d %02d:%02d:%02d\n",
                   it.startTime.month, it.startTime.day, it.startTime.year,
                   it.startTime.hour, it.startTime.mins, it.startTime.sec, it.overTime.month, it.overTime.day,
                   it.overTime.year,
                   it.overTime.hour, it.overTime.mins, it.overTime.sec);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    int t;
    scanf("%d", &t);
    while (t--) {
        play game;
        game.init();
        game.process();
        game.output();
    }
    return 0;
}