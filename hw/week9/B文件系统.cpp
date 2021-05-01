#include<bits/stdc++.h>

#define mem(f, v) memset(f,v,sizeof(f))

typedef long long LL;
const int inf = ~(1u << 31u);
const LL linf = ~(1LLu << 63u);

using namespace std;

// 第九周作业 B 2012-12cspT3

struct file {
    int file_type;// 0普通文件 1目录文件
    LL file_size;
    LL all_mx, son_mx;//配额
    LL all_used, son_used;//当前大小
    map<string, file *> child;//! 对文件系统来说较为好写的方案

    file(int type, LL size = 0)//! 注意这个构造函数的写法
            : file_type(type), file_size(size), all_mx(0), son_mx(0), all_used(0), son_used(0) {}

    ~file() {
        for (auto &it:child) delete it.second;
    }

    bool pre_add_size(LL size, bool last = false) const {//预分配，判断是否满足分配条件
        if (all_mx && all_used + size > all_mx)
            return false;
        if (last && son_mx != 0 && son_used + size > son_mx)
            return false;
        return true;
    }

    void add_size(LL size, bool last = false) {//实际分配
        if (last)
            son_used += size;
        all_used += size;
    }

    LL get_size() const {
        if (file_type == 0) return file_size;
        return all_used;
    }

    bool set_size(LL all, LL son) {//分配配额
        if ((all && all_used > all) || (son && son_used > son))
            return false;
        all_mx = all;
        son_mx = son;
        return true;
    }
};

struct file_system {
    file *root;
    vector<string> path;
    string filename;

    file_system() {
        root = new file(1);//新建一个目录文件s
    }

    ~file_system() { delete root; }

    void set_path(string &pa) {
        path.clear();
        string temp;
        for (auto c:pa) {//字符串分割
            if (c == '/') {
                if (!temp.empty()) path.emplace_back(temp), temp = "";//当前路径为空，创建
            } else
                temp += c;
        }
        filename = temp;//路径最后的是文件名
    }

    pair<file *, int> find() {//返回文件指针和文件类型
        file *now = root;
        for (auto &np:path) {
            if (!now->child.count(np)) return make_pair(nullptr, 1);//找不到，不完整
            if (now->child[np]->file_type == 0) return make_pair(nullptr, 0);//路径错误
            now = now->child[np];
        }
        if (!filename.empty()) {
            if (!now->child.count(filename)) return make_pair(nullptr, 1);//找不到这个文件
            now = now->child[filename];
        }
        return make_pair(now, 2);//成功找到文件
    }

    bool create(LL size) {
        file *now = root;
        for (auto &np:path) {//遍历路径
            if (!now->pre_add_size(size))
                return false;
            if (!now->child.count(np))//不存在
                now->child[np] = new file(1);
            now = now->child[np];
        }
        //检查最后一层
        if (!now->pre_add_size(size, true))
            return false;

        //实际分配
        now = root;
        for (auto &np:path) {//遍历路径
            now->add_size(size);
            now = now->child[np];
        }
        now->add_size(size, true);

        now->child[filename] = new file(0, size);
        return true;
    }

    void remove(LL size) {
        file *now = root;
        for (auto &np:path) {
            now->add_size(-size);
            now = now->child[np];
        }
        if (now->child[filename]->file_type == 1) now->add_size(-size);
        else now->add_size(-size, true);

        delete now->child[filename];
        now->child.erase(filename);
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n;
    file_system fs;
    cin >> n;
    string str, path;
    for (int i = 1; i <= n; i++) {
        cin >> str >> path;
        fs.set_path(path);
        //路径检查
        auto ret = fs.find();
        if (str == "C") {
            LL filesize;
            cin >> filesize;
            if (ret.second == 2) {//路径完整
                if (ret.first->file_type == 1)//是个目录
                    cout << "N" << endl;
                else {
                    LL oldsize = ret.first->get_size();
                    fs.remove(oldsize);
                    if (fs.create(filesize))
                        cout << "Y" << endl;
                    else {
                        fs.create(oldsize);
                        cout << "N" << endl;
                    }
                }
            } else if (ret.second == 1) {//路径不完整
                if (fs.create(filesize))
                    cout << "Y" << endl;
                else
                    cout << "N" << endl;
            } else//路径错误
                cout << "N" << endl;
        } else if (str == "R") {
            if (ret.second == 2)
                fs.remove(ret.first->get_size());
            cout << "Y" << endl;
        } else if (str == "Q") {
            LL allmx, sonmx;
            cin >> sonmx >> allmx;
            if (ret.second == 2 && ret.first->file_type == 1) {
                if (ret.first->set_size(allmx, sonmx))
                    cout << "Y" << endl;
                else
                    cout << "N" << endl;
            } else
                cout << "N" << endl;
        }
    }
    return 0;
}