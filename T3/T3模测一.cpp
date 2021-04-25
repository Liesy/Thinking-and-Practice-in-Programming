/*
T3模拟测试1
*/
#include <bits/stdc++.h>

using namespace std;

int first[4][3][3];
int second[4][3][3];

int number[10][3][3]={//有字符即为1
    {//0
        {0,1,0},
        {1,0,1},
        {1,1,1}
    },
    {//1
        {0,0,0},
        {0,0,1},
        {0,0,1}
    },
    {//2
        {0,1,0},
        {0,1,1},
        {1,1,0}
    },
    {//3
        {0,1,0},
        {0,1,1},
        {0,1,1}
    },
    {//4
        {0,0,0},
        {1,1,1},
        {0,0,1}
    },
    {//5
        {0,1,0},
        {1,1,0},
        {0,1,1}
    },
    {//6
        {0,1,0},
        {1,1,0},
        {1,1,1}
    },
    {//7
        {0,1,0},
        {0,0,1},
        {0,0,1}
    },
    {//8
        {0,1,0},
        {1,1,1},
        {1,1,1}
    },
    {//9
        {0,1,0},
        {1,1,1},
        {0,1,1}
    }
};

//判断屏幕first的第num个数字有没有可能是value
int judge_first(int num,int value){
    int reseult=2;//2为一定是，1为有可能，0为不可能
    for(int i=0;i<3;i++){
        int j=0;
        for(;j<3;j++){
            if(number[value][i][j]<first[num][i][j]){
                reseult=0;
                break;
            }
            else if(number[value][i][j]>first[num][i][j])
                reseult=1;
        }
        if(j!=3)
            break;
    }
    return reseult;
}

//判断屏幕second的第num个数字有没有可能是value
int judge_second(int num,int value){
    int reseult=2;//2为一定是，1为有可能，0为不可能
    for(int i=0;i<3;i++){
        int j=0;
        for(;j<3;j++){
            if(number[value][i][j]<second[num][i][j]){
                reseult=0;
                break;
            }
            else if(number[value][i][j]>second[num][i][j])
                reseult=1;
        }
        if(j!=3)
            break;
    }
    return reseult;
}

int main(){
    int t;
    char c;
    scanf("%d",&t);
    c=getchar();//读掉换行符
    for(int i=0;i<t;i++){
        //重置屏幕
        memset(first,0,sizeof(first));
        memset(second,0,sizeof(second));
        //输入
        for(int row=0;row<3;row++){
            //第一块屏幕
            for(int num=0;num<4;num++){
                for(int column=0;column<3;column++){
                    scanf("%c",&c);
                    if(c=='_'||c=='|')
                        first[num][row][column]=1;
                }
            }
            c=getchar();//读掉空格
            //第二块屏幕
            for(int num=0;num<4;num++){
                for(int column=0;column<3;column++){
                    scanf("%c",&c);
                    if(c=='_'||c=='|')
                        second[num][row][column]=1;
                }
            }
            c=getchar();//读掉换行符
        }
        //处理
        int answer,cnt=0;
        for(int time=0;time<=2359;time++){//枚举
            int hour=time/100;//时
            int minu=time%100;//分
            //判断第一块屏幕
            if(!judge_first(0,hour/10))
                continue;
            if(!judge_first(1,hour%10))
                continue;
            if(!judge_first(2,minu/10))
                continue;
            if(!judge_first(3,minu%10))
                continue;
            if(hour>=24||minu>=60)
                continue;
            //第二块屏幕晚15分钟
            if(minu-15<0)
                hour=(hour-1+24)%24;
            minu=(minu-15+60)%60;
            //判断第二块屏幕
            if(!judge_second(0,hour/10))
                continue;
            if(!judge_second(1,hour%10))
                continue;
            if(!judge_second(2,minu/10))
                continue;
            if(!judge_second(3,minu%10))
                continue;
            if(hour>=24||minu>=60)
                continue;
            //能走到这一步说明有符合要求的答案
            cnt++;
            if(cnt>1)
                break;
            answer=time;
        }
        if(cnt!=1)
            printf("Not Sure\n");
        else
            printf("%04d\n",answer);
    }
    return 0;
}