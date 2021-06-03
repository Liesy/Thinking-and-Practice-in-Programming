#include <bits/stdc++.h>
#define mem(f, v) memset(f, v, sizeof(f))

typedef long long ll;
const int maxn = 50010;
const int inf = 0x3f3f3f3f;
const ll linf = 0x3f3f3f3f3f3f3f3fll;

using namespace std;

// 2019-9 CSP T5 参考：https://blog.csdn.net/Code92007/article/details/102022390
int n, m, k, num[maxn];
bool imp[maxn];
ll dp[maxn][110], temp[110];//dp表示在以节点i为根的子树中选j个重要节点时，在这个子树里的最小路径和
vector<vector<pair<int,int>>> graph;

void init() {
    for (int i = 0; i <= n; i++){
        vector<pair<int,int>> edge;
        graph.emplace_back(edge);
    }
}

void dfs(int u, int fa){
    dp[u][0] = 0;
    if (imp[u]){
        num[u] = 1;
        dp[u][1] = 0;
    }
    for (auto &x: graph[u]){
        int y = x.first, z = x.second;
        if (y == fa) continue;
        dfs(y,u);
        int sum = min(k, num[u] + num[y]), minNum = min(k, num[u]);
        for (int i = 0; i <= sum; i++) temp[i] = dp[u][i];
        for (int i = 0; i <= minNum; i++)
            for (int j = 0; i + j <= sum; j++)
                temp[i + j] = min(temp[i + j], dp[u][i] + dp[y][j] + (ll)z * j * (k - j));
        for (int i = 0; i <= sum; i++) dp[u][i] = min(dp[u][i], temp[i]);
        num[u] += num[y];
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin >> n >> m >> k;
    init();
    mem(imp,0);
    mem(dp,0x3f);
    for (int i = 1; i <= m; i++){
        int t;
        cin >> t;
        imp[t] = true;
    }
    for (int i = 1; i <= n - 1; i++){
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].emplace_back(make_pair(b,c));
        graph[b].emplace_back(make_pair(a,c));
    }
    dfs(1,-1);
    cout << dp[1][k] << '\n';
    return 0;
}

/*
5 3 2
1 3 5
1 2 4
1 3 5
1 4 3
4 5 1

4
*/