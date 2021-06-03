#include <bits/stdc++.h>

#define mem(f, v) memset(f, v, sizeof(f))

typedef long long ll;
const int maxn = 100010;
const int inf = 0x3f3f3f3f;
const ll linf = 0x3f3f3f3f3f3f3f3fll;

using namespace std;

int n, m, opt, x, y;
int a[maxn];

int main(){
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    while(m--) {
        cin >> opt;
        if (opt == 1){
            cin >> x >> y;
        }
        else if (opt == 2){

        }
    }
    return 0;
}