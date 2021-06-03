#include <bits/stdc++.h>

#define mem(f, v) memset(f, v, sizeof(f))

typedef long long ll;
const int maxn = 100010;
const int inf = 0x3f3f3f3f;
const ll linf = 0x3f3f3f3f3f3f3f3fll;

using namespace std;

//第十四周作业 A 树的直径及数量 树形dp
int n, a, b, res1 = -1, res2;
int dist[maxn];//表示i这个节点下的最长链的长度
int num[maxn];//表示i这个节点有多少链的长度是最长的
vector<int> graph[maxn];

void dfs(int u, int fa){
    num[u] = 1;
    dist[u] = 0;
    for (auto &y: graph[u]){
        if (y == fa) continue;
        dfs(y,u);
        if (dist[u] + dist[y] + 1 > res1){
            res1 = dist[u] + dist[y] + 1;
            res2 = num[u] * num[y];
        }
        else if (dist[u] + dist[y] + 1 == res1) res2 += num[u] * num[y];

        if (dist[y] + 1 > dist[u]){
            dist[u] = dist[y] + 1;
            num[u] = num[y];
        }
        else if (dist[y] + 1 == dist[u]) num[u] += num[y];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n - 1; i++) {
        cin >> a >> b;
        graph[a].emplace_back(b);
        graph[b].emplace_back(a);
    }
    dfs(1,0);
    cout << res1 << ' ' << res2 << '\n';
    return 0;
}

/*
5
5 1
1 2
2 3
2 4

3 2
*/