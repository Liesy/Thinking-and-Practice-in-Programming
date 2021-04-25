#include<bits/stdc++.h>
using namespace std;

//!第七周作业 C SPFA判负环
int n,m,w,s,e,t;
bool judge;
vector<vector<pair<int,int>>> graph;//邻接链表
int dist[510],cnt[510],vis[510];
void init(){//初始化邻接链表
    graph.clear();
    for(int i=0;i<=39999;i++){
        vector<pair<int,int>> edge;
        graph.emplace_back(edge);
    }
}
void SPFA(){
    memset(dist,19999,sizeof(dist));
    memset(vis,0,sizeof(vis));
    judge=true;
    queue<int> que;
    dist[1]=0;//取1为起点
    vis[1]=1;//在队列中
    que.emplace(1);
    cnt[1]=1;//入队次数
    while(!que.empty()){
        int top=que.front();
        que.pop();
        vis[top]=0;//出队了
        //扫描所有出边
        for(auto it=graph[top].begin();it!=graph[top].end();++it){
            pair<int,int> nextp=*it;
            if(dist[nextp.first]>dist[top]+nextp.second){
                dist[nextp.first]=dist[top]+nextp.second;
                cnt[nextp.first]=cnt[top]+1;

                if(cnt[nextp.first]>n){
                    judge=false;
                    return;
                }

                if(!vis[nextp.first]){
                    que.emplace(nextp.first);
                    vis[nextp.first]=1;
                }
            }
        }
    }
}
int main(){
    int f;
    cin>>f;
    for(int i=0;i<f;i++){
        cin>>n>>m>>w;
        init();
        for(int j=0;j<m;j++){//双向正边
            cin>>s>>e>>t;
            graph[s].emplace_back(make_pair(e,t));
            graph[e].emplace_back(make_pair(s,t));
        }
        for(int j=0;j<w;j++){//单向负边
            cin>>s>>e>>t;
            graph[s].emplace_back(make_pair(e,-t));
        }
        SPFA();
        if(judge)
            cout<<"NO"<<endl;
        else
            cout<<"YES"<<endl;
    }
    return 0;
}