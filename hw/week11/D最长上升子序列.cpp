#include <bits/stdc++.h>

#define mem(f, v) memset(f, v, sizeof(f))

typedef long long ll;
const int maxn = 1000010;
const int inf = ~(1u << 31u);
const ll linf = ~(1llu << 63u);

using namespace std;

// 第十一周作业 D LIS问题+树状数组维护区间最大值
// LIS问题的理解：https://blog.csdn.net/ltrbless/article/details/81318935（n^2复杂度，TLE）

int n, res = 0;
int a[maxn], f[maxn], s[maxn];
#define lb(x) (x & (-x))

void update(int x, int v){
    for (int i = x; i < maxn; i += lb(i)) //注意这里的上限是maxn
        s[i] = max(s[i], v);
}

int ask(int x){
    int ret = 0;
    for (int i = x; i >= 1; i -= lb(i))
        ret = max(ret, s[i]);
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    mem(s, 0);
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> a[i];
        f[i] = ask(a[i] - 1) + 1;
        update(a[i], f[i]);
        res = max(res, f[i]);
    }
    cout << res << '\n';
    return 0;
}