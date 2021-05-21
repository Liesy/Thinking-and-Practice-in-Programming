#include <bits/stdc++.h>

#define mem(f, v) memset(f, v, sizeof(f))

typedef long long ll;
const int maxn = 50;

using namespace std;

//第十二周作业 E 超大背包
int n;
ll v, res = 0;
ll w[maxn], c[maxn];
pair<ll, ll> pa[1 << (40 / 2 + 2)];

int main(){
    ios::sync_with_stdio(false);
    cin >> n >> v;
    for (int i = 0; i < n; i++) //此处从0开始
        cin >> w[i] >> c[i];
    int mid = n / 2;
    //二进制折半枚举前半部分
    for (int i = 0; i < 1 << mid; i++){
        ll sw = 0, sc = 0;
        for (int j = 0; j < mid; j++)
            if ((i >> j) & 1){
                sw += w[j];
                sc += c[j];
            }
        pa[i] = make_pair(sw, sc);
    }
    //去掉价值小重量大的
    sort(pa, pa + (1 << mid));
    int index = 1;
    for (int i = 1; i < 1 << mid; i++)
        if (pa[index - 1].second < pa[i].second)
            pa[index++] = pa[i];
    //枚举后半部分
    //求解
    for (int i = 0; i < 1 << (n - mid); i++){
        ll sw = 0, sc = 0;
        for (int j = 0; j < (n - mid); j++)
            if ((i >> j) & 1){
                sw += w[mid + j];
                sc += c[mid + j];
            }
        if (sw <= v){
            ll temp = (lower_bound(pa, pa + index, make_pair(v - sw, LONG_LONG_MAX)) - 1)->second;
            res = max(res, sc + temp);
        }
    }
    cout << res << '\n';
    return 0;
}