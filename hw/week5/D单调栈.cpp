#include<bits/stdc++.h>
using namespace std;

//! 第五周D题 单调栈
int main(){
    int n;
    cin>>n;
    vector<long long> h(n+1);
    for(int i=0;i<n;i++)
        cin>>h[i];
    h[n]=-1;//最后一个元素设为最小值，以最后清空栈
    stack<int> sta;//保存下标
    long long max_s=0,temp_s;
    int top_flag;//栈顶元素
    for(int i=0;i<=n;i++){
        if(sta.empty()||h[i]>=h[sta.top()])
            sta.emplace(i);
        else{
            while(!sta.empty()&&h[i]<h[sta.top()]){
                top_flag=sta.top();
                sta.pop();
                temp_s=(i-top_flag)*h[top_flag];
                if(temp_s>max_s)
                    max_s=temp_s;
            }
            sta.emplace(top_flag);
            h[top_flag]=h[i];
        }
    }
    cout<<max_s<<endl;
    return 0;
}