#include <bits/stdc++.h>

#define mem(f, v) memset(f, v, sizeof(f))

typedef long long ll;
const int maxn = 1000010;
const int inf = 0x3f3f3f3f;
const ll linf = 0x3f3f3f3f3f3f3f3fll;

using namespace std;

//第十四周作业 C 最大区间和 单调队列优化dp
int n, m, a[maxn];
ll f[maxn], s[maxn];
deque<int> q;

int main(){
    ios::sync_with_stdio(false);
    cin >> n >> m;
    mem(s,0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        s[i] = s[i - 1] + a[i];
    }
    ll res = -linf;
    for (int i = 1; i <= n; i++){
        while(q.size() && q.front() < i - m) q.pop_front();//区间外的弹出去
        res = max(res, s[i] - s[q.front()]);
        while(q.size() && s[q.back()] >= s[i]) q.pop_back();//队尾位置大于当前值，则忽略
        q.push_back(i);
    }
    cout << res << '\n';
    return 0;
}