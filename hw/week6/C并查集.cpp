#include<bits/stdc++.h>
using namespace std;

//!第六周作业 C题 并查集
int par[100010];
int findx(int x){
    if(par[x]==x)
        return x;
    return par[x]=findx(par[x]);
}
bool merge(int x,int y){
    int px,py;
    px=findx(x);
    py=findx(y);
    if(px==py)
        return false;
    par[px]=py;
    return true;
}
int main(){
    int n,m,a,b;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        par[i]=i;
    int res=n-1;
    for(int i=0;i<m;i++){
        cin>>a>>b;
        if(merge(a,b))
            res--;
        cout<<res<<endl;
    }
    return 0;
}