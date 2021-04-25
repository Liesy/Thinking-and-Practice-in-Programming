#include<bits/stdc++.h>
using namespace std;

//! 第四周C 最大和最小问题
int main(){
    int n,m;
    cin>>n>>m;
    vector<long long> num(n);
    for(int i=0;i<n;i++)
        cin>>num[i];
    long long max=-1;
    long long sum=0;
    for(int i=0;i<n;i++){
        if(max<num[i])
            max=num[i];
        sum+=num[i];
    }
    long long left=max,right=sum,min=sum+1;
    while(left<right){
        long long mid=(left+right)/2;
        long long sum_of_seg=0;
        int flag=0,seg=0;
        for(;flag<n;flag++){
            sum_of_seg+=num[flag];
            if(sum_of_seg<=mid)
                continue;
            sum_of_seg=num[flag];
            seg++;
        }
        seg++;
        if(seg<=m){
            if(mid<min)
                min=mid;
            right=mid-1;
        }
        else
            left=mid+1;
    }
    cout<<min<<endl;
}