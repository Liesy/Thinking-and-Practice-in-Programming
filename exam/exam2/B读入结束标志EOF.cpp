#include<bits/stdc++.h>
using namespace std;
int main(){
    int pos,add_pos=1;
    char c;
    c=getchar();
    if(c>='A'&&c<='Z')
        add_pos=c-'A'+1;
    if(c>='0'&&c<='9')
        add_pos=c-'0';
    while(c!=EOF){
        if(c>='A'&&c<='Z'){
            pos='A'+(c-'A'+add_pos)%26;
            cout<<char(pos);
        }
        else if(c>='0'&&c<='9'){
            pos='0'+(c-'0'+add_pos)%10;
            cout<<char(pos);
        }
        else
            cout<<c;
        c=getchar();
    }
    cout<<endl;
    return 0;
}