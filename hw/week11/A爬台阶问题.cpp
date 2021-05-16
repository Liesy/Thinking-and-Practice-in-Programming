#include <bits/stdc++.h>

#define mem(f, v) memset(f, v, sizeof(f))

typedef long long ll;
const int maxn = 1000010;
const int inf = ~(1u << 31u);
const ll linf = ~(1llu << 63u);

using namespace std;

//第十一周作业 A 爬台阶升级版
#define mod 998244353
int n, m, k, d;
int f[maxn], sf[maxn];

int main(){
    ios::sync_with_stdio(false);
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++){
        cin >> d;
        f[d] = inf; //该台阶不能用
    }
    f[0] = 1, sf[0] = 1;
    for (int i = 1; i <= n; i++){
        if (f[i] == inf){
            sf[i] = sf[i - 1];
            continue;
        }
        if (i - k - 1 < 0) f[i] = sf[i - 1] - 0; //从首项开始求和
        else f[i] = (sf[i - 1] + mod - sf[i - k - 1]) % mod;

        sf[i] = (sf[i - 1] + f[i]) % mod;
        //取模之后，sf[i-1]可能比sf[i-k-1]小，但是不取模又爆了
        //所以在求f[i]的时候，让sf[i-1]+mod确保sf的递增
    }
    cout << f[n] % mod << '\n';
    return 0;
}