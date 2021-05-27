#include <bits/stdc++.h>

#define mem(f, v) memset(f, v, sizeof(f))

typedef long long ll;
const int maxn = 15;
const int inf = 0x3f3f3f3f;
const ll linf = 0x3f3f3f3f3f3f3f3fll;

using namespace std;

//第十三周作业 D 状态压缩dp
int h, w;
ll f[maxn][1 << maxn];
bool s[1 << maxn];

int main(){
    ios::sync_with_stdio(false);
    cin >> h >> w;
    for (int i = 0; i < 1 << h; i++){
        int cnt = 0;
        s[i] = true;
        for (int j = 0; j < h; j++)
            if (i >> j & 1) { if (cnt & 1) s[i] = false; }
            else cnt++;
        if (cnt & 1) s[i] = false;
    }
    mem(f, 0);
    f[0][0] = 1;
    for (int i = 1; i <= w; i++)
        for (int j = 0; j < 1 << h; j++)
            for (int k = 0; k < 1 << h; k++)
                if ((j & k) == 0 && (s[j | k]))
                    f[i][j] += f[i - 1][k];
    cout << f[w][0] << '\n';
    return 0;
}