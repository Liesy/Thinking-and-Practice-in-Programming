#include<bits/stdc++.h>
using namespace std;

//!第八周 C 差分约束+SPFA最短路且判负环
int n,m,k,a,b,c;
bool judge;
vector<vector<pair<int,int>>> graph;
int dist[1010],vis[1010],cnt[1010];
void init(){
    for(int i=0;i<=n;i++){
        vector<pair<int,int>> edge;
        graph.emplace_back(edge);
    }
}
void SPFA(){
    judge=true;
    memset(dist,0x3f3f3f3f,sizeof(dist));
    memset(vis,0,sizeof(vis));
    queue<int> que;
    dist[0]=0;//取0为起点
    vis[0]=1;
    que.emplace(0);
    cnt[0]=1;//入队次数
    while(!que.empty()){
        int x=que.front();
        que.pop();
        vis[x]=0;//出队
        for(auto it=graph[x].begin();it!=graph[x].end();++it){
            int y=it->first,z=it->second;
            if(dist[y]>dist[x]+z){
                dist[y]=dist[x]+z;
                cnt[y]=cnt[x]+1;
            
                if(cnt[y]>n){
                    judge=false;//存在负环
                    return;
                }
                if(!vis[y]){
                    que.emplace(y);
                    vis[y]=1;
                }
            }
        }
    }
}
int main(){
    scanf("%d %d",&n,&m);
    init();
    while(m--){
        scanf("%d %d %d %d",&k,&a,&b,&c);
        if(k==1)
            graph[a-1].emplace_back(make_pair(b,c));
        else if(k==2)
            graph[b].emplace_back(make_pair(a-1,-c));
        else if(k==3)
            graph[a-1].emplace_back(make_pair(b,c-1));
        else if(k==4)
            graph[b].emplace_back(make_pair(a-1,-c-1));
        else if(k==5){
            graph[a-1].emplace_back(make_pair(b,c));
            graph[b].emplace_back(make_pair(a-1,-c));
        }
        else;
    }
    //附加条件
    for(int i=1;i<=n;i++){
        graph[i].emplace_back(make_pair(i-1,0));
        graph[i-1].emplace_back(make_pair(i,1));
    }
    SPFA();
    if(!judge)
        printf("impossible\n");
    else
        printf("%d\n",dist[n]);
    return 0;
}