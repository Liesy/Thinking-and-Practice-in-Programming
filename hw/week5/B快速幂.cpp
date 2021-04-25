#include<bits/stdc++.h>
using namespace std;

//* 快速幂 https://blog.csdn.net/qq_19782019/article/details/85621386
//! 第五周B题
int main(){
    int n;
    cin>>n;
    string str;
    cin>>str;
    vector<int> judge(26);
    int result=0,min_res=n;
    int i,temp,l=0;
    for(i=0;i<n;i++){
        temp=str[i]-'A';
        if(!judge[temp])
            result++;
        judge[temp]++;
        while(judge[str[l]-'A']>1){
            judge[str[l]-'A']--;
            l++;
        }
        if(result==26)
            min_res=min(min_res,i-l+1);
    }
    cout<<min_res<<endl;
    return 0;
}