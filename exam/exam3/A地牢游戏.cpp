#include <bits/stdc++.h>

#define mem(f, v) memset(f, v, sizeof(f))

typedef long long ll;
const int maxn = 100010;
const int inf = 0x3f3f3f3f;
const ll linf = 0x3f3f3f3f3f3f3f3fll;

using namespace std;

int n, a[4];

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    while(n--) {
        for (int i = 1; i <= 3; i++)
            cin >> a[i];
        int shoot = 0;
        while(1) {
            shoot++;
            if ((shoot % 7) == 0) {
                if (a[1] == 1 && a[2] == 1 && a[3] == 1){
                    cout << "YES" << '\n';
                    break;
                }
                else if (a[1] < 1 || a[2] < 1 || a[3] < 1){
                    cout << "NO" << '\n';
                    break;
                }
                else for (int i = 1; i <= 3; i++) a[i]--;
            }
            else a[max_element(a + 1, a + 3 + 1) - a]--;
        }
    }
    return 0;
}

/*
3
3 2 4
1 1 1
10 1 7

YES
NO
NO
*/