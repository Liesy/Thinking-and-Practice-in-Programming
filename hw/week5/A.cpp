#include<bits/stdc++.h>
using namespace std;

//! 第五周A题
int  deArray[500010][27];
int main(){
    
    //freopen("a.in","r",stdin);
    //freopen("a.out","w",stdout);
    int n,m,l,r;
    cin>>n;
    // vector<vector<int>> deArray;
    // for(int i=0;i<26;i++){
    //     vector<int> narray(n+1);
    //     deArray.emplace_back(narray);
    // }
    memset(deArray,0,sizeof(deArray));
    string str;
    cin >> str;
    cin>>m;
    for(int i=1;i<=n;i++){
        int temp = str[i-1] - 'A';
        for(int j = 0;j < 26;j++)
            deArray[i][j] = deArray[i-1][j];
        deArray[i][temp]++;
    }

    for(int i=0;i<m;i++){
        bool judge=true;
        scanf("%d %d",&l,&r);
        for(int j=0;j<26;j++){
            if(deArray[r][j] - deArray[l-1][j] <= 0)
            {
                judge = false;
                break;
            }
        }
        if(judge)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}