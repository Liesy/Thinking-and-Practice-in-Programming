#include <bits/stdc++.h>

#define mem(f, v) memset(f, v, sizeof(f))

typedef long long ll;
const int N = 3;
const int inf = 0x3f3f3f3f;
const ll linf = 0x3f3f3f3f3f3f3f3fll;

using namespace std;
//第十五周作业 C
int t, n, p=998244353;

struct matrix{
    long long x[N][N];
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
    matrix() {mem(x,0);}
};

matrix quick_pow(matrix a, long long x){
    matrix ret;
    ret.x[0][1] = ret.x[1][0] = 0;
    ret.x[0][0] = ret.x[1][1] = 1;
    while (x){
        if (x & 1) ret = ret * a;
        a = a * a;
        x >>= 1;
    }
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    matrix a;
    a.x[0][0] = 1; a.x[0][1] = 0; a.x[0][2] = 1;
	a.x[1][0] = 0; a.x[1][1] = 1; a.x[1][2] = 1;
    a.x[2][0] = 2; a.x[2][1] = 2; a.x[2][2] = 1;
    int f[3] = {1, 0, 2};
    cin >> t;
    while(t--){
        cin >> n;
        matrix ans = quick_pow(a, n-1);
        int res = 0;
        for(int i = 0; i < 3; i++){
   			res += ans.x[0][i] * f[i] % p;
            res %= p;
        }
        cout << res << '\n';
    }
    return 0;
}