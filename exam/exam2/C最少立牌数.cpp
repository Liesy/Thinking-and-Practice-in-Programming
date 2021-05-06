#include<bits/stdc++.h>

#define mem(f, v) memset(f,v,sizeof(f))

typedef long long LL;
const int inf = ~(1u << 31u);
const LL linf = ~(1LLu << 63u);

using namespace std;

//csp第二次模测 c题
int n, k, res = 0;
int person[1000010], day[1000010];

int main() {
    ios::sync_with_stdio(false);
    mem(person, 0);
    mem(day, 0);
    cin >> n;
    while (n--) {
        cin >> k;
        int last = 0;
        for (int i = 1; i <= k; i++) {
            cin >> day[i];
            last = max(person[day[i]], last);
        }
        last++;
        res = max(res, last);
        for (int i = 1; i <= k; i++)
            person[day[i]] = last;
    }
    cout << res << endl;
    return 0;
}