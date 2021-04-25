#include<bits/stdc++.h>
using namespace std;

struct window{
    long long like;
    long long chat;
    bool top;
    window(){}
    window(long long likeability){
        like=likeability;
        chat=0;
        top=false;
    }
};

class TTcat{
public:
    int opid;
    long long u,w;
    vector<window> all_chat;
    TTcat(){opid=1;}
    //*------------------------------
    int find_top(){
        int length=all_chat.size();
        for(int i=0;i<length;i++)
            if(all_chat[i].top)
                return i;
        return -1;
    }
    //*------------------------------
    int find(long long u){
        int length=all_chat.size();
        for(int i=0;i<length;i++)
            if(all_chat[i].like==u)
                return i;
        return -1;
    }
    //*-----------------------------------------
    void add(){
        cin>>u;
        if(find(u)==-1){
            all_chat.emplace_back(window(u));
            cout<<"OpId #"<<opid<<": success."<<endl;
            opid++;
        }
        else{
            cout<<"OpId #"<<opid<<": same likeness."<<endl;
            opid++;
        }
    }
    //*-------------------------------------------------------------------------
    void close(){
        cin>>u;
        int judge=find(u);
        if(judge!=-1){
            cout<<"OpId #"<<opid<<": close "<<u<<" with "<<all_chat[judge].chat<<"."<<endl;
            opid++;
            all_chat.erase(all_chat.begin()+judge);
        }
        else{
            cout<<"OpId #"<<opid<<": invalid likeness."<<endl;
            opid++;
        }
    }
    //*-------------------------------------------------
    void chat_w(){
        cin>>w;
        if(all_chat.empty()){
            cout<<"OpId #"<<opid<<": empty."<<endl;
            opid++;
        }
        else{
            int top=find_top();
            if(top!=-1)
                all_chat[top].chat+=w;
            else
                all_chat[0].chat+=w;
            cout<<"OpId #"<<opid<<": success."<<endl;
            opid++;
        }
    }
    //*----------------------------------------------------
    void rotate_x(){
        int x;
        cin>>x;
        if((x<1)||(x>all_chat.size())){
            cout<<"OpId #"<<opid<<": out of range."<<endl;
            opid++;
        }
        else{
            // window new_window;
            // new_window.like=all_chat[x].like;
            // new_window.chat=all_chat[x].chat;
            // new_window.top=all_chat[x].top;
            // all_chat.erase(all_chat.begin()+x);
            // all_chat.insert(all_chat.begin(),new_window);
            all_chat.insert(all_chat.begin(),all_chat[x-1]);
            all_chat.erase(all_chat.begin()+x);
            cout<<"OpId #"<<opid<<": success."<<endl;
            opid++;
        }
    }
    //*--------------------------------------------------------
    void prior(){
        if(all_chat.empty()){
            cout<<"OpId #"<<opid<<": empty."<<endl;
            opid++;
        }
        else{
            int max_index=0;
            int length=all_chat.size();
            for(int i=0;i<length;i++)
                if(all_chat[i].like>=all_chat[max_index].like)
                    max_index=i;
            all_chat.insert(all_chat.begin(),all_chat[max_index]);
            all_chat.erase(all_chat.begin()+max_index+1);
            cout<<"OpId #"<<opid<<": success."<<endl;
            opid++;
        }
    }
    //*--------------------------------------------------------
    void choose(){
        cin>>u;
        int index=find(u);
        if(index!=-1){
            all_chat.insert(all_chat.begin(),all_chat[index]);
            all_chat.erase(all_chat.begin()+index+1);
            cout<<"OpId #"<<opid<<": success."<<endl;
            opid++;
        }
        else{
            cout<<"OpId #"<<opid<<": invalid likeness."<<endl;
            opid++;
        }
    }
    //*------------------------------------------------------
    void top_window(){
        cin>>u;
        int index_u=find(u);
        if(index_u==-1){
            cout<<"OpId #"<<opid<<": invalid likeness."<<endl;
            opid++;
        }
        else{
            int top_index=find_top();
            if(top_index!=-1)
                all_chat[top_index].top=false;
            all_chat[index_u].top=true;
            cout<<"OpId #"<<opid<<": success."<<endl;
            opid++;
        }
    }
    //*------------------------------------------------------
    void untop(){
        int index_top=find_top();
        if(index_top==-1){
            cout<<"OpId #"<<opid<<": no such person."<<endl;
            opid++;
        }
        else{
            all_chat[index_top].top=false;
            cout<<"OpId #"<<opid<<": success."<<endl;
            opid++;
        }
    }
    //*-------------------------------------------------------------------------------------------------------
    void say_goodbye(){
        int index_top=find_top();
        if(index_top!=-1){
            if(all_chat[index_top].chat!=0){
                cout<<"OpId #"<<opid<<": Bye "<<all_chat[index_top].like<<": "<<all_chat[index_top].chat<<"."<<endl;
                opid++;
            }
            all_chat.erase(all_chat.begin()+index_top);
        }
        while(!all_chat.empty()){
            if(all_chat.front().chat!=0){
                cout<<"OpId #"<<opid<<": Bye "<<all_chat.front().like<<": "<<all_chat.front().chat<<"."<<endl;
                opid++;
            }
            all_chat.erase(all_chat.begin());
        }
    }
};

int main(){
    int t,n;
    cin>>t;
    for(int j=0;j<t;j++){
        cin>>n;
        string s;
        TTcat game;
        for(int i=0;i<n;i++){
            cin>>s;
            if(s=="Add")
                game.add();
            else if(s=="Close")
                game.close();
            else if(s=="Chat")
                game.chat_w();
            else if(s=="Rotate")
                game.rotate_x();
            else if(s=="Prior")
                game.prior();
            else if(s=="Choose")
                game.choose();
            else if(s=="Top")
                game.top_window();
            else if(s=="Untop")
                game.untop();
            else
                exit(1);
        }
        game.say_goodbye();
    }
    return 0;
}