#include <bits/stdc++.h>

#define mem(f, v) memset(f, v, sizeof(f))

typedef long long ll;
const int maxn = 5010;
const int inf = 0x3f3f3f3f;
const ll linf = 0x3f3f3f3f3f3f3f3fll;

using namespace std;

//第十三周作业 B 区间dp
string str;
int f[maxn][maxn];

int main(){
    ios::sync_with_stdio(false);
    cin >> str;
    int n = str.size();
    mem(f, 0);
    for (int i = 0; i < n; i++)
        f[i][i] = 1;
    for (int len = 2; len <= n; len++){
        for (int l = 0; l <= n - len; l++){
            int r = l + len - 1;
            if ((str[l] == '(' && str[r] == ')') || (str[l] == '[' && str[r] == ']'))
                f[l][r] = f[l + 1][r - 1];
            else
                f[l][r] = inf;
            for (int k = l; k < r; k++)
                f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r]);
        }
    }
    cout << f[0][n - 1] << '\n';
    return 0;
}