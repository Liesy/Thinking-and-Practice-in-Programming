#include <bits/stdc++.h>

#define mem(f, v) memset(f, v, sizeof(f))

typedef long long ll;
const int maxn = 10010;
const int max_int = ~(1u << 31u);
const int min_int = (1u << 31u);
const ll max_ll = ~(1llu << 63u);
const ll min_ll = (1llu << 63u);

using namespace std;

//第十二周作业 C 多重背包 二进制拆分
int n, v, t;
int w[maxn], c[maxn];
int ww[7 * maxn], cc[7 * maxn]; //100最多拆分成7个二进制相加
ll res = 0, f[maxn];

int main(){
    ios::sync_with_stdio(false);
    cin >> n >> v;
    mem(f, min_ll);
    f[0] = 0;
    int cnt = 0;
    for (int i = 1; i <= n; i++){
        cin >> w[i] >> c[i] >> t;
        for (int k = 1; k <= t; k <<= 1){
            cnt++;
            ww[cnt] = k * w[i];
            cc[cnt] = k * c[i];
            t -= k;
        }
        if (t > 0){
            cnt++;
            ww[cnt] = t * w[i];
            cc[cnt] = t * c[i];
        }
    }
    n = cnt;
    for (int i = 1; i <= n; i++)
        for (int j = v; j >= ww[i]; j--)
            f[j] = max(f[j], f[j - ww[i]] + cc[i]);
    for (int i = 0; i <= v; i++)
        res = max(res, f[i]);
    cout << res << '\n';
    return 0;
}