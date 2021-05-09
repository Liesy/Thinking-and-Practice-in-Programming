#include <bits/stdc++.h>

#define mem(f, v) memset(f, v, sizeof(f))
#define lb(x) (x & (-x))

typedef long long ll;
const int inf = ~(1u << 31u);
const ll linf = ~(1LLu << 63u);

using namespace std;

//第十周 C 树状数组
int n, q;
int k, l, r;
ll arr[1000010], BIT[1000010];

void update(int x, int v){
    for (int i = x; i <= n; i += lb(i))
        BIT[i] += v;
}

ll ask(int x){
    ll res = 0;
    for (int i = x; i >= 1; i -= lb(i))
        res += BIT[i];
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    mem(arr, 0ll);
    mem(BIT, 0ll);
    cin >> n >> q;
    for (int i = 1; i <= n; i++){
        cin >> arr[i];
        update(i, arr[i]);
    }
    while (q--){
        cin >> k;
        if (k == 1){
            cin >> l >> r;
            update(l, r);
        }
        else if (k == 2){
            cin >> l >> r;
            ll res = ask(r) - ask(l - 1);
            cout << res << endl;
        }
    }
    return 0;
}