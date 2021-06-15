#include <bits/stdc++.h>

#define mem(f, v) memset(f, v, sizeof(f))

typedef long long ll;
const int maxn = 110;
const int inf = 0x3f3f3f3f;
const ll linf = 0x3f3f3f3f3f3f3f3fll;

using namespace std;
//第十五周作业 D
long long n, m, ans = 0;
int f[maxn][maxn];

struct matrix{
    long long x[maxn][maxn];
    matrix operator*(matrix &t){
        matrix ret;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; j++){
                ret.x[i][j] = 0;
                for (int k = 0; k < m; k++) ret.x[i][j] = max(ret.x[i][j], x[i][k] + t.x[k][j]);
            }
        return ret;
    }
    matrix() {mem(x, 0);}
};

matrix quick_pow(matrix a, long long x){
    matrix ret = a;
    while (x){
        if (x & 1) ret = ret * a;
        a = a * a;
        x >>= 1;
    }
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    matrix a;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++){
            cin >> f[i][j];
            a.x[i][j] = f[i][j];
        }
    matrix tmp = quick_pow(a, n - 2);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            ans = max(ans, tmp.x[i][j]);
    cout << ans << '\n';
    return 0;
}