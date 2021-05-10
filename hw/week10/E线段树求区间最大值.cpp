#include <bits/stdc++.h>

#define mem(f, v) memset(f, v, sizeof(f))

typedef long long ll;
const int maxn = 200010;
const int inf = ~(1u << 31u);
const ll linf = ~(1LLu << 63u);

using namespace std;

//第十周 E 利用线段树解区间最大值问题
int m, p, t;
ll like, a = 0;
char option;

struct segmentTree {
    int l, r;
    ll dat;
} tree[maxn << 2];

void build(int posi, int l, int r) {
    tree[posi].l = l, tree[posi].r = r;
    if (l == r) {
        tree[posi].dat = 0;
        return;
    }
    int mid = (l + r) / 2;
    build(posi * 2, l, mid);
    build(posi * 2 + 1, mid + 1, r);
    tree[posi].dat = max(tree[posi * 2].dat, tree[posi * 2 + 1].dat);
}

void update(int posi, int x, int v) {
    if (tree[posi].l == tree[posi].r) {
        tree[posi].dat = v;
        return;
    }
    int mid = (tree[posi].l + tree[posi].r) / 2;
    if (x <= mid) update(posi * 2, x, v);
    else update(posi * 2 + 1, x, v);
    tree[posi].dat = max(tree[posi * 2].dat, tree[posi * 2 + 1].dat);
}

ll ask(int posi, int l, int r) {
    if (l <= tree[posi].l && r >= tree[posi].r) return tree[posi].dat;
    int mid = (tree[posi].l + tree[posi].r) / 2;
    ll res = -linf;
    if (l <= mid) res = max(res, ask(posi * 2, l, r));
    if (r > mid) res = max(res, ask(posi * 2 + 1, l, r));
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> m >> p;
    build(1, 1, m);
    int index=0;
    while (m--) {
        cin >> option >> t;
        if (option == 'Q') {
            a = ask(1, index - t + 1, index);
            cout << a << endl;
        } else if (option == 'A') {
            like = (t + a) % p;
            index++;
            update(1, index, like);
        }
    }
    return 0;
}