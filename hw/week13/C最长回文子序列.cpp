#include <bits/stdc++.h>

#define mem(f, v) memset(f, v, sizeof(f))

typedef long long ll;
const int maxn = 3828;//! 小于3828会RE
const int inf = 0x3f3f3f3f;
const ll linf = 0x3f3f3f3f3f3f3f3fll;

using namespace std;

//第十三周作业 C 最长回文子序列
string s;
int f[maxn][maxn];

int main(){
    ios::sync_with_stdio(false);
    cin >> s;
    int n = s.size();
    mem(f, 0);
    for (int i = 0; i < n; i++)
        f[i][i] = 1;
    for (int len = 2; len <= n; len++){
        for (int l = 0; l <= n - len; l++){
            int r = l + len - 1;
            if (s[l] == s[r]) f[l][r] = f[l + 1][r - 1] + 2;
            else f[l][r] = max(f[l + 1][r], f[l][r - 1]);
        }
    }
    cout << f[0][n - 1] << '\n';
    return 0;
}