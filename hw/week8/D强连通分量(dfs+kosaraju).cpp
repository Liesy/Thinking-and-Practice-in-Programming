#include<bits/stdc++.h>
using namespace std;

//!第八周作业 D dfs+kosaraju+缩点 求入度为0的强连通分量数
int n, m, a, b;
vector<vector<int>> graph;
vector<vector<int>> rev_graph;//逆图
vector<int> scc_top;
int res = 0, cnt = 0;
int vis[1000010],scc[1000010];
void init() {
    for (int i = 0; i <= n; i++) {
        vis[i] = 0;
        scc[i] = 0;
        vector<int> edge;
        graph.emplace_back(edge);
        rev_graph.emplace_back(edge);
    }
}
void dfs(int x) {
    if (vis[x])
        return;
    vis[x] = 1;
    for (auto it = graph[x].begin(); it != graph[x].end(); ++it)
        dfs(*it);
    scc_top.emplace_back(x);
}
void rev_dfs(int y) {
    if (scc[y])
        return;
    scc[y] = res;
    for (auto it = rev_graph[y].begin(); it != rev_graph[y].end(); ++it)
        rev_dfs(*it);
}
void kosaraju() {
    for (int i = 1; i <= n; i++)
        dfs(i);
    for (int i = n - 1; i >= 0; i--) {
        if (!scc[scc_top[i]]) {
            res++;
            rev_dfs(scc_top[i]);
        }
    }
}
int main() {
    scanf("%d %d",&n,&m);
    init();
    while (m--) {
        scanf("%d %d",&a,&b);
        graph[a].emplace_back(b);
        rev_graph[b].emplace_back(a);
    }
    kosaraju();
    //缩点
    int deg_scc[res+1];
    for(int i=0;i<=res;i++)
        deg_scc[i]=0;
    for(int x=1;x<=n;x++)
        for(auto y=graph[x].begin();y!=graph[x].end();++y){
            if(scc[x]==scc[*y])
                continue;
            deg_scc[scc[*y]]++;
        }
    for(int i=1;i<=res;i++)
        if(deg_scc[i]==0)
            cnt++;
    printf("%d\n",cnt);
    return 0;
}