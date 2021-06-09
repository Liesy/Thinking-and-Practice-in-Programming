#include <bits/stdc++.h>

#define mem(f, v) memset(f, v, sizeof(f))

typedef long long ll;
const int maxn = 100010;
const int inf = 0x3f3f3f3f;
const ll linf = 0x3f3f3f3f3f3f3f3fll;

using namespace std;

int n, m, opt, x, y;
vector<int> a;

void process(){
    //去重
    auto last = unique(a.begin(),a.end());
    a.erase(last,a.end());
}

int main(){
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++){
        int temp;
        cin >> temp;
        a.emplace_back(temp);
    }
    process();
    while(m--) {
        cin >> opt;
        if (opt == 1){
            cin >> x >> y;
            for (auto &num: a) if (num == x) num = y;
        }
        else if (opt == 2){
            process();
            cout << a.size() << '\n';
        }
    }
    return 0;
}