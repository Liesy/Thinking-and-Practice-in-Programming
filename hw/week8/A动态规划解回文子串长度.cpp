#include<bits/stdc++.h>
using namespace std;

//!第八周作业 A 动态规划解回文子串长度
int main(){
    int n;
    int res=1;
    scanf("%d",&n);
    getchar();//读走换行符
    char c;
    char str[5010];
    bool flag[5010][5010];//用来标识子串i到j是否是回文串
    for(int i=0;i<n;i++){
        scanf("%c",&c);
        if(c=='a'||c=='e'||c=='i'||c=='o'||c=='u')
            str[i]='a';
        else
            str[i]=c;
    }
    //先处理单个字符和两个字符的回文串
    for(int i=0;i<n;i++){
        flag[i][i]=true;
        if((i<n-1)&&str[i]==str[i+1]){
            flag[i][i+1]=true;
            res=2;
        }
    }
    //处理三个字符以上的回文子串
    for(int length=3;length<=n;length++)
        for(int i=0;i<=n-length;i++){
            int j=i+length-1;
            if(flag[i+1][j-1]&&str[i]==str[j]){
                flag[i][j]=true;
                res=length;
            }
        }
    printf("%d\n",res);
    return 0;
}