#include<bits/stdc++.h>

#define mem(f, v) memset(f,v,sizeof(f))

typedef long long ll;
const int maxn = 1000010;
const int inf = ~(1u << 31u);
const ll linf = ~(1LLu << 63u);

using namespace std;

//第十周作业 D 求逆序对个数
#define lb(x) (x & (-x))

int n, times, memory;
int arr[maxn], BIT[maxn], ls[maxn], rs[maxn];

void update(int x, int v) {
    for (int i = x; i <= n; i += lb(i))
        BIT[i] += v;
}

int ask(int x) {
    int res = 0;
    for (int i = x; i >= 1; i -= lb(i))
        res += BIT[i];
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> times >> memory;
        arr[i] = times + memory;
    }
    //正序找左边小过arr[i]的个数
    mem(BIT, 0);
    for (int i = 1; i <= n; i++) {
        ls[i] = ask(arr[i] - 1);
        update(arr[i], 1);
    }

    //逆序找右边小过arr[i]的个数
    mem(BIT, 0);
    for (int i = n; i >= 1; i++) {
        rs[i] = ask(arr[i] - 1);
        update(arr[i], 1);
    }

    for (int i = 1; i <= n; i++)
        cout << ls[i] << ' ' << rs[i] << endl;

    return 0;
}