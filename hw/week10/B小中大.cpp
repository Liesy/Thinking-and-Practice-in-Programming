#include<bits/stdc++.h>

#define mem(f,v) memset(f,v,sizeof(f))

typedef long long ll;
const int inf=~(1u<<31u);
const ll linf=~(1LLu<<63u);

using namespace std;

//第十周作业 B
int n;
ll k;
vector<ll> num;

int main(){
    num.emplace_back(-linf);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&k);
        num.emplace_back(k);
    }
    sort(num.begin(),num.end());
    // for(auto &x:num)
    //     printf("%lld",x);
    ll mid1;
    double mid2;
    if(n%2==0){
        mid1=num[n/2]+num[(n/2)+1];
        if(mid1%2==0)
            printf("%lld %lld %lld\n",num[n],mid1/2,num[1]);
        else{
            mid2=(double)mid1/2;
            printf("%lld %.1f %lld\n",num[n],mid2,num[1]);
        }
    }
    else {
        mid1=num[(n/2)+1];
        printf("%lld %lld %lld\n",num[n],mid1,num[1]);
    }
    return 0;
}