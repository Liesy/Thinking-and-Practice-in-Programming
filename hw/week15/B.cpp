#include <bits/stdc++.h>

#define mem(f, v) memset(f, v, sizeof(f))

typedef long long ll;
const int inf = 0x3f3f3f3f;
const ll linf = 0x3f3f3f3f3f3f3f3fll;

using namespace std;

//第十五周作业 B
const int p = 1e+9 + 7;
long long n, ans;
int t, k;
int m[12][12];

void init(){
    m[1][0] = 1;
    for (int i = 1; i <= 10; i++) m[i][i] = 1;
    for (int i = 2; i <= 10; i++)
        for (int j = 0; j < i; j++)
            m[i][j] = m[i - 1][j] + m[i - 1][j - 1];
}

struct matrix{
    int N;
    long long x[12][12];

    matrix operator*(matrix &t){
        matrix ret;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++){
                ret.x[i][j] = 0;
                for (int k = 0; k < N; k++){
                    ret.x[i][j] += x[i][k] * t.x[k][j] % p;
                    ret.x[i][j] %= p;
                }
            }
        return ret;
    }

    matrix(){
        mem(x, 0);
        N = k + 2;
    }
};

matrix quick_pow(matrix a, long long x){
    matrix ret;
    for (int i = 0; i < k + 2; i++) ret.x[i][i] = 1;
    while (x){
        if (x & 1) ret = ret * a;
        a = a * a;
        x >>= 1;
    }
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    init();
    cin >> t;
    while (t--){
        cin >> n >> k;
        ans = 0;
        matrix a;
        for (int i = 0; i < k + 2; i++) a.x[i][i] = 1;
        for (int i = 1; i < k + 2; i++)
            for (int j = 0; j < i; j++)
                a.x[i][j] = 0;
        for (int i = 1; i < k + 2; i++) a.x[0][i] = m[k][i - 1];
        for (int i = 1; i < k + 2; i++)
            for (int j = i + 1; j < k + 2; j++)
                a.x[i][j] = m[k - i + 1][j - i];
        a = quick_pow(a, n - 1);
        for (int i = 0; i < k + 2; i++){
            ans = ans + a.x[0][i] % p;
            ans = ans % p;
        }
        cout << ans << '\n';
    }
    return 0;
}