#include<bits/stdc++.h>
using namespace std;

//! 第五周 作业C题 单调队列
int main(){
    int n,k;
    cin>>n>>k;
    vector<long long> num(n);
    for(int i=0;i<n;i++)
        cin>>num[i];
    deque<int> min_que;
    int left,right;
    //先处理最小值
    for(left=0,right=0;right<=n;){
        if(right-left+1<=k){
            if(right==n)
                break;
            if(min_que.empty()||num[right]>=num[min_que.back()]){
                min_que.push_back(right);//入栈的是下标
                right++;
            }
            else{
                while(!min_que.empty()&&num[right]<num[min_que.back()])
                    min_que.pop_back();
                min_que.push_back(right);
                right++;
            }
        }
        else{
            cout<<num[min_que.front()]<<' ';
            left++;
            while(min_que.front()<left)
                min_que.pop_front();
        }
    }
    cout<<endl;
    deque<int> max_que;
    //再处理最大值
    for(left=0,right=0;right<=n;){
        if(right-left+1<=k){
            if(right==n)
                break;
            if(max_que.empty()||num[right]<=num[max_que.back()]){
                max_que.push_back(right);//入栈的是下标
                right++;
            }
            else{
                while(!max_que.empty()&&num[right]>num[max_que.back()])
                    max_que.pop_back();
                max_que.push_back(right);
                right++;
            }
        }
        else{
            cout<<num[max_que.front()]<<' ';
            left++;
            while(max_que.front()<left)
                max_que.pop_front();
        }
    }
    return 0;
}