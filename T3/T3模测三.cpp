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
*/

// vector<pair<string,int>> stu;
map<ll,int> stu;//学号-分数

int raceScore(char gen, string ss){//返回期末长跑测试成绩
    int min, sec;
    int temp = 0;
    for (auto &x: ss){
        if (x == 'c') min = temp, temp = 0;//遇到分隔符
        else temp = 10 * temp + x - '0';
    }
    sec = temp;
    int times = 60 * min + sec;
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

int countScore(int cou){//返回到课次数对应成绩
    if (cou >= 18) return 5;
    else if (cou >= 15) return 4;
    else if (cou >= 12) return 3;
    else if (cou >= 9) return 2;
    else if (cou >= 6) return 1;
    else return 0;
}

int main(){
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++){
        ll p;
        char gender, flag;
        string race;
        int score, daily, counts, sumScore;
        cin >> p >> gender >> score >> race >> flag >> daily >> counts;
        sumScore = score + raceScore(gender, race) + daily + countScore(counts);
        if (flag == 'P') sumScore += 10;
        stu.emplace(p, sumScore);
    }
    cin >> m;
    for (int i = 1; i <= m; i++){
        ll p;
    }
    return 0;
}

/*
1
2015011233 M 34 14'30 P 3 3
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