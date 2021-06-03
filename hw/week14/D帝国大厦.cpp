#include <bits/stdc++.h>

#define mem(f, v) memset(f, v, sizeof(f))

typedef long long ll;
const int maxn = 5010;
const int inf = 0x3f3f3f3f;
const ll linf = 0x3f3f3f3f3f3f3f3fll;

using namespace std;

//第十四周作业 D 坐电梯 前缀和优化+压维
//参考：https://blog.csdn.net/weixin_30666401/article/details/97943733
const int mod = 1e9 + 7;
int n, a, b, k;
int dp[2][maxn], s[2][maxn];

int main(){
    ios::sync_with_stdio(false);
    cin >> n >> a >> b >> k;
    dp[0][a] = 1;
    for (int i = a; i <= n; i++) s[0][i] = 1;
    for (int i = 1; i <= k; i++)
        for (int j = 1; j <= n; j++){
            int lim;
            if (j > b){
                lim = j - (j - b - 1) / 2;
                dp[i % 2][j] = ((s[(i + 1) % 2][n] 
                                - s[(i + 1) % 2][lim - 1] 
                                - dp[(i + 1) % 2][j]) % mod + mod) % mod;
            }
            if (j < b){
                lim = j + (b - j - 1) / 2;
                dp[i % 2][j] = ((s[(i + 1) % 2][lim] 
                                - dp[(i + 1) % 2][j]) % mod + mod) % mod;
            }
            s[i % 2][j] = (s[i % 2][j - 1] + dp[i % 2][j]) % mod;
        }
    int res = 0;
    for (int i = 1; i <= n; i++){
        res += dp[k % 2][i];
        res %= mod;
    }
    cout << res << '\n';
    return 0;
}

/*
* case 1
5 2 4 1

2
* case 2
5 2 4 2

2
* case 3
5 3 4 1

0
*/