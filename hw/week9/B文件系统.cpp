#include<bits/stdc++.h>

#define mem(f, v) memset(f,v,sizeof(f))

typedef long long LL;
const int inf = ~(1u << 31u);
const LL linf = ~(1LLu << 63u);

using namespace std;

// �ھ�����ҵ B 2012-12cspT3

struct file {
    int file_type;// 0��ͨ�ļ� 1Ŀ¼�ļ�
    LL file_size;
    LL all_mx, son_mx;//���
    LL all_used, son_used;//��ǰ��С
    map<string, file *> child;//! ���ļ�ϵͳ��˵��Ϊ��д�ķ���

    file(int type, LL size = 0)//! ע��������캯����д��
            : file_type(type), file_size(size), all_mx(0), son_mx(0), all_used(0), son_used(0) {}

    ~file() {
        for (auto &it:child) delete it.second;
    }

    bool pre_add_size(LL size, bool last = false) const {//Ԥ���䣬�ж��Ƿ������������
        if (all_mx && all_used + size > all_mx)
            return false;
        if (last && son_mx != 0 && son_used + size > son_mx)
            return false;
        return true;
    }

    void add_size(LL size, bool last = false) {//ʵ�ʷ���
        if (last)
            son_used += size;
        all_used += size;
    }

    LL get_size() const {
        if (file_type == 0) return file_size;
        return all_used;
    }

    bool set_size(LL all, LL son) {//�������
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
        root = new file(1);//�½�һ��Ŀ¼�ļ�s
    }

    ~file_system() { delete root; }

    void set_path(string &pa) {
        path.clear();
        string temp;
        for (auto c:pa) {//�ַ����ָ�
            if (c == '/') {
                if (!temp.empty()) path.emplace_back(temp), temp = "";//��ǰ·��Ϊ�գ�����
            } else
                temp += c;
        }
        filename = temp;//·���������ļ���
    }

    pair<file *, int> find() {//�����ļ�ָ����ļ�����
        file *now = root;
        for (auto &np:path) {
            if (!now->child.count(np)) return make_pair(nullptr, 1);//�Ҳ�����������
            if (now->child[np]->file_type == 0) return make_pair(nullptr, 0);//·������
            now = now->child[np];
        }
        if (!filename.empty()) {
            if (!now->child.count(filename)) return make_pair(nullptr, 1);//�Ҳ�������ļ�
            now = now->child[filename];
        }
        return make_pair(now, 2);//�ɹ��ҵ��ļ�
    }

    bool create(LL size) {
        file *now = root;
        for (auto &np:path) {//����·��
            if (!now->pre_add_size(size))
                return false;
            if (!now->child.count(np))//������
                now->child[np] = new file(1);
            now = now->child[np];
        }
        //������һ��
        if (!now->pre_add_size(size, true))
            return false;

        //ʵ�ʷ���
        now = root;
        for (auto &np:path) {//����·��
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
        //·�����
        auto ret = fs.find();
        if (str == "C") {
            LL filesize;
            cin >> filesize;
            if (ret.second == 2) {//·������
                if (ret.first->file_type == 1)//�Ǹ�Ŀ¼
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
            } else if (ret.second == 1) {//·��������
                if (fs.create(filesize))
                    cout << "Y" << endl;
                else
                    cout << "N" << endl;
            } else//·������
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