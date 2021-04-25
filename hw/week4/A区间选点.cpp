#include<bits/stdc++.h>
using namespace std;

//! 第四周A 区间选点问题
struct section{
    int a,b,num;
    section(){}
    section(int l,int r,int k){
        a=l;
        b=r;
        num=k;
    }
};

bool cmp(section x,section y){
    if(x.b==y.b)
        return x.a>y.a;
    return x.b<y.b;
}

int main(){
    int n,m,l,r,k,sum=0;
    cin>>n>>m;
    vector<bool> used(n+1);
    for(int i=1;i<=n;i++)
        used[i]=false;
    vector<section> zone(m+1);
    for(int i=1;i<=m;i++)
        cin>>zone[i].a>>zone[i].b>>zone[i].num;
    sort(zone.begin()+1,zone.end(),cmp);
    for(int i=1;i<=m;i++){
        for(int j=zone[i].a;j<=zone[i].b;j++){
            if(zone[i].num==0)
                break;
            if(used[j])
                zone[i].num--;
        }
        for(int j=zone[i].b;j>=zone[i].a;j--){
            if(zone[i].num==0)
                break;
            if(!used[j]){
                used[j]=true;
                sum++;
                zone[i].num--;
            }
        }
    }
    cout<<sum<<endl;
    return 0;
}