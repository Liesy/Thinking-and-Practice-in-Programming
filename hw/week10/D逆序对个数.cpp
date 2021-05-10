#include<bits/stdc++.h>

#define mem(f, v) memset(f,v,sizeof(f))

typedef long long ll;
const int maxn = 1000010;
const int inf = ~(1u << 31u);
const ll linf = ~(1LLu << 63u);

using namespace std;

//第十周作业 D 求逆序对个数

#define lb(x) (x & (-x))

int n;
int BIT[maxn], res[maxn];
pair<int,int> arr[maxn];

void update(int x, int v) {
    for (int i = x; i <= maxn; i += lb(i))//! 这里的范围是y的范围，和n没关系，必须是maxn
        BIT[i] += v;
}

int ask(int x) {
    int res = 0;
    for (int i = x; i >= 1; i -= lb(i))
        res += BIT[i];
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin>>n;
    for (int i = 1; i <= n; i++) {
        cin>>arr[i].first>>arr[i].second;
        arr[i].first++,arr[i].second++;//避开为0的情况
    }
    sort(arr+1,arr+n+1);
    mem(BIT,0);
    mem(res,0);
    for(int i=1;i<=n;i++){
        res[ask(arr[i].second)]++;
        update(arr[i].second,1);
    }
    for(int i=0;i<n;i++)
        cout<<res[i]<<'\n';//! cout不要用endl，否则相当于没关同步
    return 0;
}