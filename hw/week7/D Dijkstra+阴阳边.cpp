#include<bits/stdc++.h>
using namespace std;

//!第七周作业 D Dijkstra+阴阳边(本质是正反dijsktra)
struct to{
    int destination;
    int cost;
    bool flag;
    to(){}
    to(int d,int cc,bool f){
        destination=d;
        cost=cc;
        flag=f;
    }
};
vector<vector<to>> graph;
int dist[1000010],vis[1000010];
int n,m,s,e,c;
void init(){//初始化邻接链表
    graph.clear();
    for(int i=0;i<=2000010;i++){
        vector<to> edge;
        graph.emplace_back(edge);
    }
}
void Dijkstra(bool judge){
    memset(dist,0x3f,sizeof(dist));
    memset(vis,0,sizeof(vis));
    priority_queue<pair<int,int>> que;//利用相反数变成小根堆
    dist[1]=0;//从1点开始
    que.emplace(make_pair(0,1));
    while(!que.empty()){
        int top=que.top().second;
        que.pop();
        if(vis[top])
            continue;
        vis[top]=1;
        //扫描所有正出边
        for(auto it=graph[top].begin();it!=graph[top].end();++it){
            if(it->flag!=judge)
                continue;
            int nextp=it->destination,z=it->cost;
            if(dist[nextp]>dist[top]+z){
                dist[nextp]=dist[top]+z;
                que.emplace(make_pair(-dist[nextp],nextp));
            }
        }
    }
}
int main(){
    int T;
    cin>>T;
    for(int i=0;i<T;i++){
        int res=0;
        cin>>n>>m;
        init();
        for(int j=0;j<m;j++){
            cin>>s>>e>>c;
            graph[s].emplace_back(to(e,c,true));//阳边
            graph[e].emplace_back(to(s,c,false));//阴边
        }
        Dijkstra(true);
        for(int i=2;i<=n;i++)
            res+=dist[i];
        Dijkstra(false);
        for(int i=2;i<=n;i++)
            res+=dist[i];
        cout<<res<<endl;
    }
    return 0;
}