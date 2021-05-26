#include <bits/stdc++.h>

#define mem(f, v) memset(f, v, sizeof(f))

typedef long long ll;
const int maxn = 510;
const int inf = 0x3f3f3f3f;
const ll linf = 0x3f3f3f3f3f3f3f3fll;

using namespace std;

//第十三周作业 A 环形石子合并问题
int n;
int a[maxn], s[maxn], f_max[maxn][maxn], f_min[maxn][maxn];

int main(){
    ios::sync_with_stdio(false);
    mem(s, 0);
    mem(f_max, 0xc0);
    mem(f_min, 0x3f);
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> a[i];
        a[i + n] = a[i];
    }
    for (int i = 1; i <= n + n; i++){
        s[i] = s[i - 1] + a[i];
        f_max[i][i] = f_min[i][i] = 0;
    }
    for (int len = 2; len <= n; len++){
        for (int l = 1; l <= n + n - len + 1; l++){
            int r = l + len - 1;
            for (int k = l; k < r; k++){
                f_max[l][r] = max(f_max[l][r], f_max[l][k] + f_max[k + 1][r]);
                f_min[l][r] = min(f_min[l][r], f_min[l][k] + f_min[k + 1][r]);
            }
            f_max[l][r] += s[r] - s[l - 1];
            f_min[l][r] += s[r] - s[l - 1];
        }
    }
    int Max = -inf, Min = inf;
    for (int i = 1; i <= n; i++){
        Max = max(Max, f_max[i][i + n - 1]);
        Min = min(Min, f_min[i][i + n - 1]);
    }
    cout << Min << '\n'
         << Max << '\n';
    return 0;
}