#include<bits/stdc++.h>
using namespace std;

//! 第四周B 流水线调度问题
struct stu{
    int a,b,posi;
};

bool cmp(stu x,stu y){//Johnson表达式
    return min(y.b,x.a)<min(x.b,y.a);
}

int main(){
    int n;
    cin>>n;
    vector<stu> movie(n+1);
    for(int i=1;i<=n;i++)
        cin>>movie[i].a;
    for(int i=1;i<=n;i++){
        cin>>movie[i].b;
        movie[i].posi=i;
    }
    sort(movie.begin()+1,movie.end(),cmp);
    int times_a=0,times_all=0;
    for(int i=1;i<=n;i++){
        times_a+=movie[i].a;
        times_all=max(times_a,times_all)+movie[i].b;
    }
    cout<<times_all<<endl;
    return 0;
}