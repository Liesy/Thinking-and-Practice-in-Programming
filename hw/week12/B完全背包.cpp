#include <bits/stdc++.h>

#define mem(f, v) memset(f, v, sizeof(f))

typedef long long ll;
const int maxn = 5010;
const int max_int = ~(1u << 31u);
const int min_int = (1u << 31u);
const ll max_ll = ~(1llu << 63u);
const ll min_ll = (1llu << 63u);

using namespace std;

//第十二周作业 B 完全背包
int n, v, res = 0;
int w[maxn], c[maxn], f[maxn];

int main(){
    ios::sync_with_stdio(false);
    cin >> n >> v;
    mem(f, min_int);
    f[0] = 0;
    for (int i = 1; i <= n; i++)
        cin >> w[i] >> c[i];
    for (int i = 1; i <= n; i++)
        for (int j = w[i]; j <= v; j++)
            f[j] = max(f[j], f[j - w[i]] + c[i]);
    for (int j = 0; j <= v; j++)
        res = max(res, f[j]);
    cout << res << '\n';
    return 0;
}