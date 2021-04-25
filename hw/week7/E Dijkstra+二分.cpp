#include<bits/stdc++.h>
using namespace std;

//!第七周作业 E Dijkstra+二分
struct to{
    int destination;
    int weight;
    int times;
    to(){}
    to(int dd,int w,int t){
        destination=dd;
        weight=w;
        times=t;
    }
};
vector<vector<to>> graph;
long long dist[10010];
int vis[10010];
int n,m,t,a,b,c,d;
void init(){
    graph.clear();
    for(int i=0;i<=10010;i++){
        vector<to> edge;
        graph.emplace_back(edge);
    }
}
void dijkstra(long long max_weight){
    for(int i=1;i<=n;i++){
        dist[i]=0x3f3f3f3f3f3f3f3fLL;
        vis[i]=0;
    }
    priority_queue<pair<int,int>> que;
    dist[1]=0;
    que.emplace(make_pair(0,1));
    while(!que.empty()){
        int x=que.top().second;
        que.pop();
        if(vis[x])
            continue;
        vis[x]=1;
        for(auto it=graph[x].begin();it!=graph[x].end();++it){
            int y=it->destination,z=it->times;
            if(it->weight>=max_weight&&dist[y]>dist[x]+z){
                dist[y]=dist[x]+z;
                que.emplace(make_pair(-dist[y],y));
            }
        }
    }
}
int main(){
    int p;
    cin>>p;
    while(p--){
        cin>>n>>m>>t;
        init();
        for(int i=0;i<m;i++){
            cin>>a>>b>>c>>d;
            graph[a].emplace_back(to(b,c,d));
            graph[b].emplace_back(to(a,c,d));
        }
        long long left=0,right=10000001,res;
        while(left<=right){
            long long mid=(left+right)/2;
            dijkstra(mid);
            if(dist[n]<=t){
                res=mid;
                left=mid+1;
            }
            else
                right=mid-1;
        }
        cout<<res<<endl;
    }
    return 0;
}