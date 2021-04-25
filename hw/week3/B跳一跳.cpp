#include<bits/stdc++.h>
using namespace std;
int main(){
    string num;
    int now, last_jump = 0, score = 0;
    getline(cin, num);
    stringstream ss(num);
    while (ss >> now){
        if (now == 1){
            score += 1;
            last_jump = 0;
        }
        else if (now == 2){
            if (last_jump > 0){
                last_jump += 2;
                score += last_jump;
            }
            else{
                last_jump = 2;
                score += last_jump;
            }
        }
        else
            break;
    }
    printf("%d",score);
    return 0;
}