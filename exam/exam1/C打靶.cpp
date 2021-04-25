#include<bits/stdc++.h>
using namespace std;

//! CSP模测1 C题
set<pair<long long,long long>> sx,sy;
int main(){
    long long n,c,dl,dw;
    cin>>n>>c>>dl>>dw;
    for(int i=1;i<=n;i++){
        long long x,y;
        cin>>x>>y;
        sx.emplace(x,y);
        sy.emplace(y,x);
    }
    long long posi_l=1,posi_w=1;
    long long res_l=0,res_w=0;
    while(!sx.empty()){
        //两人都没靶子打
        long long max_step_l=sy.begin()->first-posi_l;
        long long max_step_w=sx.begin()->first-posi_w;
        if(max_step_l>=dl&&max_step_w>=dw){
            long long v=min(max_step_l/dl,max_step_w/dw);
            posi_l+=v*dl;
            posi_w+=v*dw;
        }
        //L行动
        if(posi_l!=sy.begin()->first)//移动
            posi_l=min(posi_l+dl,sy.begin()->first);
        else{//打靶
            int num=c;//能打靶的个数
            while(num--&&!sy.empty()&&posi_l==sy.begin()->first){
                sx.erase({sy.begin()->second,sy.begin()->first});
                sy.erase(sy.begin());
                res_l++;
            }
        }
        //W行动
        if(posi_w!=sx.begin()->first)//移动
            posi_w=min(posi_w+dw,sx.begin()->first);
        else{//打靶
            int num=1;//能打靶的个数
            while(num--&&!sx.empty()&&posi_w==sx.begin()->first){
                sy.erase({sx.begin()->second,sx.begin()->first});
                sx.erase(sx.begin());
                res_w++;
            }
        }
    }
    cout<<res_l<<' '<<res_w<<endl;
    return 0;
}