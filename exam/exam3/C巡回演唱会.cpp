#include <bits/stdc++.h>

#define mem(f, v) memset(f, v, sizeof(f))

typedef long long ll;
const int maxn = 200010;
const int inf = 0x3f3f3f3f;
const ll linf = 0x3f3f3f3f3f3f3f3fll;

using namespace std;

vector<pair<int,ll>> graph[maxn];
int n, m, a, b, vis[maxn];
ll c, d, dist[maxn];
priority_queue<pair<ll,int>> q;

void dijkstra(){
    mem(dist,0x3f);
    mem(vis,0);
    dist[0] = 0;//从0号超级原点开始
    q.emplace(make_pair(0,0));
    while(q.size()){
        int x = q.top().second;
        q.pop();
        if (vis[x]) continue;
        vis[x] = 1;
        for (auto &it: graph[x]){
            int y = it.first;
            ll z = it.second;
            if (dist[y] > dist[x] + z){
                dist[y] = dist[x] + z;
                q.emplace(make_pair(-dist[y],y));
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; i++){
        cin >> a >> b >> c;
        //注意路费是来回的，要乘2
        graph[a].emplace_back(make_pair(b,2 * c));
        graph[b].emplace_back(make_pair(a,2 * c));
    }
    for (int i = 1; i <= n; i++){
        cin >> d;
        graph[0].emplace_back(make_pair(i,d));
    }
    dijkstra();
    for (int i = 1; i <= n; i++) cout << dist[i] << ' ';
    return 0;
}