#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,p;
    scanf("%d",&n);
    getchar();//read out the \n
    int cnt[6];
    int min_price=999999,res=0;
    for(int i=0;i<n;i++){
        scanf("%d",&p);
        getchar();//read out the space
        char c;
        memset(cnt,0,sizeof(cnt));
        while(1){
            c=getchar();
            if(c=='\n'||c==EOF)
                break;
            if(c>='0'&&c<='5')
                cnt[c-'0']++;
        }
        if(cnt[0]>=2&&cnt[1]>=1&&cnt[5]>=1&&min_price>p){
            min_price=p;
            res=i+1;
        }
    }
    printf("%d\n",res);
    return 0;
}