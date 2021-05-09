#include<bits/stdc++.h>

#define mem(f,v) memset(f,v,sizeof(f))

typedef long long ll;
const int inf=~(1u<<31u);
const ll linf=~(1LLu<<63u);

using namespace std;

//第十周作业 A csp第一题原题
int red,yellow,green;
int n,k,t;
ll res=0;

int main(){
    ios::sync_with_stdio(false);
    cin>>red>>yellow>>green;
    cin>>n;
    while(n--){
        cin>>k>>t;
        if(k==0)//直接通过
            res+=t;
        else if(k==1)//看到红灯
            res+=t;
        else if(k==2)//看到黄灯
            res+=(t+red);
    }
    cout<<res<<endl;
    return 0;
}