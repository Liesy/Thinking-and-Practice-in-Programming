#include<bits/stdc++.h>
using namespace std;

//!第八周作业 B 拓扑排序
int n,m,a,b;
vector<vector<int>> graph;//邻接链表
int deg[1000010];//存入度
int cnt=0;
int ans[1000010];
void init(){
    for(int i=0;i<=n;i++){
        deg[i]=0;
        ans[i]=0;
        vector<int> edge;
        graph.emplace_back(edge);
    }
}
void toposort(){
    priority_queue<int,vector<int>,greater<int>> que;
    for(int i=1;i<=n;i++)
        if(deg[i]==0)
            que.emplace(i);
    while(!que.empty()){
        int x=que.top();
        que.pop();
        ans[++cnt]=x;
        for(auto it=graph[x].begin();it!=graph[x].end();++it)
            if(--deg[*it]==0)
                que.emplace(*it);
    }
}
int main(){
    scanf("%d %d",&n,&m);
    init();
    while(m--){
        scanf("%d %d",&a,&b);
        graph[a].emplace_back(b);
        deg[b]++;
    }
    toposort();
    for(int i=1;i<=cnt;i++)
        printf("%d ",ans[i]);
    cout<<endl;
    return 0;
}