#include<bits/stdc++.h>

#define mem(f, v) memset(f,v,sizeof(f))

typedef long long LL;
const int inf = ~(1u << 31u);
const LL linf = ~(1LLu << 63u);

using namespace std;

// 第九周作业 A 2019-12cspT3

//元素集合
struct ele_set {
    map<string, int> ele;

    bool operator==(const ele_set &t) const {//在struct里重载操作符要const和&
        return ele == t.ele;
    }
    void operator+=(const ele_set &t){
        for(auto &x:t.ele) ele[x.first]+=x.second;//! 注意这里遍历时候x的&，下同
    }
    void operator*=(const int v){
        for(auto &x:ele) x.second*=v;
    }
};

//用指定符号分隔，返回结果数组
vector<string> split(string &str, char c) {
    vector<string> res;
    string temp;
    for (auto x:str) {//遍历
        if (x == c) {//遇到分隔符
            if (!temp.empty()) res.emplace_back(temp), temp = "";//清空
            //! 注意这里这个逗号的写法，不用括号，方便
        } else
            temp += x;
    }
    if (!temp.empty()) res.emplace_back(temp), temp = "";
    return res;
}

//读取化学式的数字
int r_int(string str, int &p) {
    int res = 0;
    //isdigit判断某位是否是数字
    while (p < str.length() && isdigit(str[p])) res = res * 10 + str[p] - '0', p++;
    if (res == 0)
        return 1;
    return res;
}

//读取化学式中的元素
string r_ele(string &str,int &p){
    string res;
    if(isupper(str[p])) res+=str[p],p++;
    if(islower(str[p])) res+=str[p],p++;//大小写组合的元素
    return res;
}

//! 递归下降法解析字符串的元素
ele_set str_to_set(string &str, int &p) {
    ele_set res;
    int multi = r_int(str, p);
    while (p < str.length()) {
        if (str[p] == '(') {
            ++p;//跳过左括号
            res += str_to_set(str, p);
        } else if (str[p] == ')') {
            ++p;
            res *= r_int(str, p);
            return res;
        } else{
            string temp=r_ele(str,p);
            res.ele[temp]+= r_int(str,p);
        }
    }
    res*=multi;
    return res;
}

//判断等式是否成立
bool solve(string &str) {
    vector<string> equ = split(str, '=');//将等式分为左右两边
    ele_set res[2];//左右两个等式分别有一个元素集合
    for (int i = 0; i < 2; i++) {
        vector<string> element = split(equ[i], '+');
        //遍历每个化学式，得到元素集合
        for (int j = 0, posi = 0; j < element.size(); j++, posi = 0) {
            res[i] += str_to_set(element[j], posi);
        }
    }
    if (res[0] == res[1])
        return true;
    else
        return false;
}

int main() {
    ios::sync_with_stdio(false);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        string str;
        cin >> str;
        if (solve(str))
            cout << "Y" << endl;
        else
            cout << "N" << endl;
    }
    return 0;
}
