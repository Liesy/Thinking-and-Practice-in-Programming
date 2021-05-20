#include <bits/stdc++.h>

#define mem(f, v) memset(f, v, sizeof(f))

typedef long long ll;
const int maxn = 1010;
const int max_int = ~(1u << 31u);
const int min_int = (1u << 31u);
const ll max_ll = ~(1llu << 63u);
const ll min_ll = (1llu << 63u);

using namespace std;

//第十二周作业 D 分组背包
int n, v, ww, cc, kk;
int w[maxn][maxn], c[maxn][maxn], k[maxn], f[maxn];

int main(){
    ios::sync_with_stdio(false);
    cin >> n >> v;
    mem(k, 0);
    for (int i = 1; i <= n; i++){
        cin >> ww >> cc >> kk;
        k[kk]++; //该组商品数+1
        w[kk][k[kk]] = ww;
        c[kk][k[kk]] = cc;
    }
    mem(f, min_int);
    f[0] = 0;
    for (int i = 1; i < maxn; i++)
        for (int j = v; j >= 0; j--)
            for (int m = 1; m <= k[i]; m++)
                if (j >= w[i][m])
                    f[j] = max(f[j], f[j - w[i][m]] + c[i][m]);
    cout << f[v] << '\n';
    return 0;
}