#include <bits/stdc++.h>

#define mem(f, v) memset(f, v, sizeof(f))

typedef long long ll;
const int maxn = 210;
const int inf = 0x3f3f3f3f;
const ll linf = 0x3f3f3f3f3f3f3f3fll;

using namespace std;
vector<int> graph[maxn];
int n, a, b, k;
int dist[maxn], vis[maxn];
priority_queue<pair<int,int>> q;

void init(){
    for (int i = 1; i < maxn; i++) graph[i].clear();
    while(q.size()) q.pop();
}

void dijkstra(){
    mem(dist, 0x3f);
    mem(vis, 0);
    dist[a] = 0;
    q.emplace(make_pair(0,a));
    while(q.size()){
        int x = q.top().second;
        q.pop();
        if (vis[x]) continue;
        vis[x] = 1;
        for (auto &y: graph[x]){
            if (dist[y] > dist[x] + 1){
                dist[y] = dist[x] + 1;
                q.emplace(make_pair(-dist[y], y));
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    while (1){
        cin >> n;
        if (n == 0) break;
        cin >> a >> b;
        init();
        for (int i = 1; i <= n; i++){
            cin >> k;
            if (i + k <= n) graph[i].emplace_back(i + k);
            if (i - k > 0) graph[i].emplace_back(i - k); 
        }
        dijkstra();
        cout << dist[b] << '\n';
    }
    return 0;
}