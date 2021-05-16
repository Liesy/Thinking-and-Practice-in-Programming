#include <bits/stdc++.h>

#define mem(f, v) memset(f, v, sizeof(f))

typedef long long ll;
const int maxn = 1000010;
const int inf = ~(1u << 31u);
const ll linf = ~(1llu << 63u);

using namespace std;

//第十一周作业 B
int n, a;
int cnt[maxn];
ll dp[maxn]; //在大小为1-i的数中，能得到的最大分数

int main(){
    ios::sync_with_stdio(false);
    cin >> n;
    mem(cnt, 0);
    mem(dp, 0ll);
    for (int i = 1; i <= n; i++){
        cin >> a;
        cnt[a]++;
    }
    dp[1] = cnt[1];
    for (int i = 2; i < maxn; i++)
        dp[i] = max(dp[i - 1], dp[i - 2] + cnt[i] * i);
    cout << dp[maxn - 1] << '\n';
    return 0;
}