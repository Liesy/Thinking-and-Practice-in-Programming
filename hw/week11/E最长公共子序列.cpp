#include <bits/stdc++.h>

#define mem(f, v) memset(f, v, sizeof(f))

typedef long long ll;
const int maxn = 5010;
const int inf = ~(1u << 31u);
const ll linf = ~(1llu << 63u);

using namespace std;

//第十一周作业 E LCS问题
int n, m;
int a[maxn], b[maxn], f[maxn][maxn];

int main(){
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= m; i++)
        cin >> b[i];
    f[1][0] = 0, f[0][1] = 0, f[0][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i] == b[j]) f[i][j] = f[i - 1][j - 1] + 1;
            else f[i][j] = max(f[i][j - 1], f[i - 1][j]);
    cout << f[n][m] << '\n';
    return 0;
}