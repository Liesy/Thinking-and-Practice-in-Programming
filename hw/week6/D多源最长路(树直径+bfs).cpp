#include<bits/stdc++.h>
using namespace std;

//!第六周作业 D题 多源最长路，树直径，bfs
int n,a,b,flag;
vector<vector<int>> graph;
vector<int> max_dist;
void init(){
    for(int i=0;i<=n;i++){
        vector<int> x;
        graph.emplace_back(x);
        max_dist.emplace_back(0);
    }
}
void bfs(int i){
    vector<int> dist(n+1);
    queue<int> que;
    que.emplace(i);
    dist[i]++;
    while(!que.empty()){
        int top=que.front();
        que.pop();
        for(auto it=graph[top].begin();it!=graph[top].end();++it){
            if(dist[*it])
                continue;
            dist[*it]=dist[top]+1;
            if(dist[*it]>max_dist[*it])
                max_dist[*it]=dist[*it];
            que.emplace(*it);
        }
    }
    flag=max_element(dist.begin()+1,dist.end())-dist.begin();
}
int main(){
    cin>>n;
    init();
    for(int i=1;i<n;i++){
        cin>>a>>b;
        graph[a].emplace_back(b);
        graph[b].emplace_back(a);
    }
    bfs(1);
    bfs(flag);
    bfs(flag);
    for(auto it=max_dist.begin()+1;it!=max_dist.end();++it)
        cout<<*it-1<<' ';
    cout<<endl;
    return 0;
}