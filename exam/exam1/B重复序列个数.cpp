#include<bits/stdc++.h>
using namespace std;

//! CSP模测1 B题
void operate(string &str){
    for(char &c:str)
        if(c=='0')
            c='1';
        else
            c='0';
}

int main(){
    string s="01";
    string temp=s;
    while(s.length()<1000000){
        operate(temp);
        s+=temp;
        temp=s;
    }
    int n;
    string T;
    cin>>n;
    cin>>T;
    int res=0;
    for(int i=0;i<n-T.length()+1;i++){
        bool r=true;
        for(int j=0;j<T.length();j++){
            if(s[i+j]!=T[j]){
                r=false;
                break;
            }
        }
        if(r)
            res++;
    }
    cout<<res<<endl;
    return 0;
}