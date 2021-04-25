#include<bits/stdc++.h>
using namespace std;

//!第六周作业 E题 最小生成树
int n,m;
long long p,res;
struct edge{
    int a,b;
    long long c;
};
bool cmp(edge x,edge y){return x.c<y.c;}//按照花费从小到大排序
int par[100010];//并查集维护连通性
int find(int x){
    if(par[x]==x)
        return x;
    return par[x]=find(par[x]);
}
edge edges[200010];
void init(){
    cin>>n>>m>>p;
    for(int i=1;i<=n;i++)
        par[i]=i;
    int i=1;
    for(;i<=m;i++)
        cin>>edges[i].a>>edges[i].b>>edges[i].c;
    //抽水机
    for(int j=0;j<n;j++){
        edges[i+j].a=j+1;
        edges[i+j].b=0;
        edges[i+j].c=p;
    }
    sort(edges+1,edges+1+m+n,cmp);
}

int main(){
    init();
    for(int i=1;i<=m+n;i++){
        int pa=find(edges[i].a);
        int pb=find(edges[i].b);
        if(pa==pb)
            continue;
        par[pa]=pb;
        res+=edges[i].c;
    }
    cout<<res<<endl;
    return 0;
}