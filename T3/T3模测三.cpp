#include <bits/stdc++.h>

#define mem(f,v) memset(f,v,sizeof(f))

typedef long long ll;
const int maxn = 4010;
const int inf = 0x3f3f3f3f;
const ll linf = 0x3f3f3f3f3f3f3f3fll;

using namespace std;

int n, m;

/*   分数计算
 *   char gender;//性别
 *   //int score;//体育课专项成绩 直接给出
 *   int race;//期末长跑测试成绩 对应分数
 *   int dailyRace;//日常长跑成绩 合法次数对应分数
 *   //char flag;//体测是否通过 直接给出，通过则满分
 *   //int daily;//日常表现分数 直接给出
 *   int counts;//到课次数 对应分数
 *   int sumScore;//总成绩
*/

/*   日常长跑分数
 *   YYYYMMDD 完成日期
 *   p 记录的来源学号；
 *   hh:mm:ss 开始时间
 *   hh:mm:ss 结束时间
 *   l 运动距离(float，精确到2位)
 *   a'b" 总暂停时间
 *   s 总步数
*/

struct raceRecord{
    string YYYYMMDD;
    string start;
    string end;
    float l;
    string pause;
    int s;
};

// vector<pair<string,int>> stu;
map<ll,int> stu;//学号-分数
map<ll,char> stuGender;//学号-性别
map<ll,int> stuCounts;//学号-到课次数
map<ll,vector<raceRecord>> stuRace;//学号-日常长跑记录

int split(string ss){//返回时间字符串对应的总秒数
    vector<int> res;
    int temp = 0;
    for (auto &x: ss){
        if (x >= '0' && x <= '9') temp = 10 * temp + x - '0';
        else res.emplace_back(temp), temp = 0;
    }
    int ret = 0;
    for (auto &x: res) ret = 60 * ret + x;
    return ret;
}

int raceScore(char gen, string ss){//返回期末长跑测试成绩
    int times = split(ss);
    if (gen == 'M'){//男生
        if (times > 18 * 60) return 0;
        else if (times > 17 * 60 + 10) return 2;
        else if (times > 16 * 60 + 30) return 4;
        else if (times > 15 * 60 + 50) return 6;
        else if (times > 15 * 60 + 10) return 8;
        else if (times > 14 * 60 + 30) return 10;
        else if (times > 14 * 60) return 12;
        else if (times > 13 * 60 + 30) return 14;
        else if (times > 13 * 60) return 16;
        else if (times > 12 * 60 + 30) return 18;
        else return 20;
    }
    else if (gen == 'F'){//女生
        if (times > 9 * 60) return 0;
        else if (times > 8 * 60 + 50) return 2;
        else if (times > 8 * 60 + 35) return 4;
        else if (times > 8 * 60 + 20) return 6;
        else if (times > 8 * 60 + 5) return 8;
        else if (times > 7 * 60 + 50) return 10;
        else if (times > 7 * 60 + 31) return 12;
        else if (times > 7 * 60 + 14) return 14;
        else if (times > 6 * 60 + 57) return 16;
        else if (times > 6 * 60 + 40) return 18;
        else return 20;
    }
}

bool preJudge(ll sp, raceRecord rr){
    int startTime = split(rr.start), endTime = split(rr.end);
    float miles = rr.l * 1000;
    int pauseTime = split(rr.pause);
    if (stuGender[sp] == 'M' && miles < 3000.0) return false;
    if (stuGender[sp] == 'F' && miles < 1500.0) return false;
    if (miles / (endTime - startTime) < 2 || miles / (endTime - startTime) > 5) return false;
    if (pauseTime > 4 * 60 + 30) return false;
    if (miles / (rr.s * 1.0) > 1.5) return false;
    return true;
}

int countRace(ll sp){//统计合法的长跑次数
    int index = 1;
    while (stuRace[sp].size() > 1 && index < stuRace[sp].size()){
        if (stuRace[sp][index].YYYYMMDD == stuRace[sp][index - 1].YYYYMMDD){
            int nowStart = split(stuRace[sp][index].start), preEnd = split(stuRace[sp][index - 1].end);
            if (nowStart - preEnd < 6 * 60 * 60) stuRace[sp].erase(stuRace[sp].begin() + index);
            else index++;
        }
        else index++;
    }
    return stuRace[sp].size();
}

void output(){
    for (auto &x: stu){
        cout << x.first << ' ' << x.second << ' ';
        int score = x.second;
        if (score >= 95) cout << "A";
        else if (score >= 90) cout << "A-";
        else if (score >= 85) cout << "B+";
        else if (score >= 80) cout << "B";
        else if (score >= 77) cout << "B-";
        else if (score >= 73) cout << "C+";
        else if (score >= 70) cout << "C";
        else if (score >= 67) cout << "C-";
        else if (score >= 63) cout << "D+";
        else if (score >= 60) cout << "D";
        else cout << "F";
        cout << '\n';
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin >> n;
    // freopen("1.in","r",stdin);
    // freopen("1.out","w",stdout);
    for (int i = 1; i <= n; i++){
        ll p;
        char gender, flag;
        string race;
        int score, daily, counts, sumScore;
        cin >> p >> gender >> score >> race >> flag >> daily >> counts;
        stuGender.emplace(p, gender);
        stuCounts.emplace(p, counts);
        sumScore = score + raceScore(gender, race) + daily;
        if (flag == 'P') sumScore += 10;
        stu.emplace(p, sumScore);
    }
    cin >> m;
    for (int i = 1; i <= m; i++){
        ll p;
        raceRecord r;
        cin >> r.YYYYMMDD >> p >> r.start >> r.end >> r.l >> r.pause >> r.s;
        r.start += ":", r.end += ":";
        if (preJudge(p, r)) stuRace[p].emplace_back(r);
    }
    //处理日常长跑分数
    for (auto &x: stuRace){
        int num = countRace(x.first);
        stuCounts[x.first] += num;
        if (num >= 21) stu[x.first] += 10;
        else if (num >= 19) stu[x.first] += 9;
        else if (num >= 17) stu[x.first] += 8;
        else if (num >= 14) stu[x.first] += 7;
        else if (num >= 11) stu[x.first] += 6;
        else if (num >= 7) stu[x.first] += 4;
        else if (num >= 3) stu[x.first] += 2;
        else continue;
    }
    //处理出勤分数
    for (auto &x: stuCounts){
        int cou = x.second;
        if (cou >= 18) stu[x.first] += 5;
        else if (cou >= 15) stu[x.first] += 4;
        else if (cou >= 12) stu[x.first] += 3;
        else if (cou >= 9) stu[x.first] += 2;
        else if (cou >= 6) stu[x.first] += 1;
        else continue;
    }
    output();
    return 0;
}

/*
1
2015011233 M 34 14'30" P 3 3
8
20210508 2015011233 17:02:33 17:19:33 2.99 0'0 3333
20210509 2015011233 17:12:15 17:38:46 3.01 2'3 4300
20210510 2015011233 22:03:06 22:13:08 3.05 0'0 2772
20210511 2015011233 22:08:05 22:28:13 3.02 5'3 3775
20210512 2015011233 18:03:12 18:17:56 3.02 0'0 2001
20210513 2015011233 17:30:23 17:46:08 3.01 0'0 3020
20210513 2015011233 22:03:34 22:20:08 3.04 2'0 3058
20210514 2015011233 07:16:22 07:32:34 3.00 0'0 3244

2015011233 59 F
*/