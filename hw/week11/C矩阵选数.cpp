#include <bits/stdc++.h>

#define mem(f, v) memset(f, v, sizeof(f))

typedef long long ll;
const int maxn = 1000010;
const int inf = ~(1u << 31u);
const ll linf = ~(1llu << 63u);

using namespace std;

//第十一周 C
int n;
int a[maxn][4];
ll dp[maxn][4]; //仅考虑前i列，且第i列选的是第1/2/3个数（不开long long就wa了）

int main(){
    ios::sync_with_stdio(false);
    cin >> n;
    mem(dp,0);
    for (int j = 1; j <= 3; j++)
        for (int i = 1;i <= n; i++)
            cin >> a[i][j];
    for (int i = 2; i <= n; i++)
        for (int j = 1; j <= 3; j++)
            dp[i][j] = min(min(dp[i - 1][1] + abs(a[i][j] - a[i - 1][1]),
                               dp[i - 1][2] + abs(a[i][j] - a[i - 1][2])),
                           dp[i - 1][3] + abs(a[i][j] - a[i - 1][3]));//min仅支持两个数比较
    cout << min(min(dp[n][1], dp[n][2]), dp[n][3]) << '\n';
    return 0;
}