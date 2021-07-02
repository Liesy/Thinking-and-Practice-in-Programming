#include <bits/stdc++.h>
#define rep(i, s, t) for(int i=s;i<=t;i++)
using namespace std;

/* 全局变量 */
int n;                   // 猪的数量
queue<char> allCards;    // 牌堆

struct Pig {
/* 属性 */
    int index;            // 当前猪下标
    int hp = 4;           // 血量
    char type;            // 猪的类型: M, Z, F
    char jumpType = 0;    // 跳的类型: Z(忠), F(反), f(MP视角的类反), 0(空), 注意对MP来说针对F更优先于f
    bool arming = false;  // 有无装备
    list<char> cards;     // 手中的牌
/* 方法定义, 这里是完成本题必须的方法, 可以不必多定义了 */
    void jump(){jumpType = type=='F'?'F':'Z';} // 跳阵营
    bool isJumpItsFriend(Pig* pig) { return pig->type == 'F' ? jumpType == 'F' : jumpType == 'Z'; } // 我跳它朋友了吗?
    Pig* getNextPig();    // 获取存活的下家
    void addCards(int num);// 从牌堆拿牌放到自己手右
    bool del(char c);     // 删掉手里一张牌, 删成功则返回true
    void hurt(Pig* attacker);// 被攻击掉一点血
    bool cost(Pig* attacker, char c);// 被迫消耗手中一张牌, 消耗成功返回true并不减血, 否则减血, 减血到0尝试用桃, 无则死亡, 根据身份对杀者做后续处理
    bool useP();          // 主动使用桃, 满足使用条件就使用, 使用后返回true
    bool useK();          // 主动使用杀, 满足使用条件就使用, 使用后返回true
    bool useF();          // 主动使用决斗, 满足使用条件就使用, 使用后返回true
    bool useN();          // 主动使用南猪入侵, 满足使用条件就使用, 使用后返回true
    bool useW();          // 主动使用万箭齐发, 满足使用条件就使用, 使用后返回true
    bool findJ(Pig* attacker); // 被迫去求无懈可击, 求到则返回true
    bool useJ(Pig* pig);  // 帮某个猪用无懈可击, 用成功返回true
} ps[15];

/* 全局方法 */
bool isGameEnd() {
    if (ps[0].hp <= 0) return true;
    rep(i, 1, n-1)
        if (ps[i].type == 'F' && ps[i].hp > 0)
            return false;
    return true;
}
int cnt = 0;
void judgeGameEnd() {
    if (isGameEnd()) {
        printf(ps[0].hp > 0 ? "MP\n" : "FP\n");
        rep(i, 0, n-1) {
            if (ps[i].hp <= 0) {
                printf("DEAD\n");
            } else {
                for (list<char>::iterator it = ps[i].cards.begin(); it != ps[i].cards.end(); it++)
                    printf(it==ps[i].cards.end()?"%c":"%c ", *it);
                printf("\n");
            }
        }
        exit(0);
    }
}

void solve() {
    ps[0].jump();
    while (true) {
        rep(i, 0, n-1) {
            if (ps[i].hp <= 0) continue;
            ps[i].addCards(2);
            bool usedK = false;
            for (list<char>::iterator it = ps[i].cards.begin(); it != ps[i].cards.end(); it++) {
                bool used = false;
                char c = *it;
                it = ps[i].cards.erase(it);
                switch (c) {
                    case 'P': used = ps[i].useP(); break;
                    case 'K': if (!usedK || ps[i].arming) used = usedK = ps[i].useK(); break;
                    case 'F': used = ps[i].useF(); break;
                    case 'N': used = ps[i].useN(); break;
                    case 'W': used = ps[i].useW(); break;
                    case 'Z': ps[i].arming = used = true; break;
                }
                if (used) it = --ps[i].cards.begin();
                else it = ps[i].cards.insert(it, c);
                if (ps[i].hp <= 0) break;
            }
        }
    }
}
/* 主控方法 */
int main() {
    // Input
    int m; scanf("%d%d", &n, &m);
    char s[5];
    rep(i, 0, n-1) {
        ps[i].index = i;
        scanf("%s", s), ps[i].type = s[0];
        rep(j, 1, 4) scanf("%s", s), ps[i].cards.push_back(s[0]);
    }
    while(m--) scanf("%s", s), allCards.push(s[0]);
    // To solve
    solve();
}

Pig* Pig::getNextPig() {
    int nxt = (index + 1) % n;
    while (ps[nxt].hp <= 0) {
        nxt = (nxt+1) % n;
    }
    return &ps[nxt];
}

void Pig::addCards(int num) {
    rep(i,1,num) {
        cards.push_back(allCards.front());
        allCards.pop();
    }
}

bool Pig::useP() {
    if (hp < 4) {
        hp ++;
        return true;
    }
    return false;
}

bool Pig::useK() {
    // TODO: 补全代码
    Pig* nxt = getNextPig();
    if(this->type=='M')
    {
        if(nxt->jumpType=='F'||nxt->jumpType=='f') 
        {nxt->cost(this,'D');
        return true;}
    }
    if(this->type=='Z')
    {
        if(nxt->jumpType=='F') {
            nxt->cost(this,'D');
         jump();
        return true;}
    }
    if(this->type=='F')
    {
        if(nxt->index==0||nxt->jumpType=='Z')
        {nxt->cost(this,'D');
         jump();
        return true;}
    }
    return false;
}

bool Pig::useF() {
    // TODO: 补全代码
        Pig* nxtZ = 0, *nxtF = 0, *nxtf = 0, *goal = 0;
    for (Pig* nxt = getNextPig(); nxt != this; nxt = nxt->getNextPig()) {
        if (nxt->jumpType == 'Z' && !nxtZ) nxtZ = nxt;
        if (nxt->jumpType == 'F' && !nxtF) nxtF = nxt;
        if (nxt->jumpType == 'f' && !nxtf) nxtf = nxt;
    }

    if (type == 'M') goal = nxtF == 0 ? nxtf : nxtF;
    else if (type == 'Z') goal = nxtF;
    else goal = &ps[0];

    if (goal) {
        jump();
        if (!goal->findJ(this)) {
            while (true) {
                if ((type == 'M' && goal->type == 'Z') || !goal->del('K')) {
                    goal->hurt(this);
                    break;
                }
                else if (!cost(goal, 'K')) break;
            }
        }
        return true;
    }

    return false;
}

bool Pig::useN() {
    for (Pig* nxt = getNextPig(); nxt != this; nxt = nxt->getNextPig()) {
        // TODO: 补全代码
        if (!nxt->findJ(this) && !nxt->cost(this, 'K')) {
            if (nxt->type == 'M' && !jumpType) jumpType = 'f';
        }
    }
    return true;
}

bool Pig::useW() {
    for (Pig* nxt = getNextPig(); nxt != this; nxt = nxt->getNextPig()) {
        // TODO: 补全代码
        if(nxt->findJ(this));
        else
        {
            if (!nxt->cost(this, 'D')  )
            {  if(nxt->type == 'M')
                if(this->jumpType==0)//没有跳身份
                this->jumpType = 'f';
            }
        }
    }
    return true;
}

bool Pig::del(char c) {
    // TODO: 补全代码
    for (auto it = cards.begin(); it != cards.end(); it++) {
        if (c == *it) {
            cards.erase(it);
            return true;            
        }
    }
    return false;
}

void Pig::hurt(Pig *attacker) {
    if (--hp == 0) {
        if (this->del('P')) {
            this->useP();
        } else {
            judgeGameEnd();
            switch(type) {
                case 'F': attacker->addCards(3); break;
                case 'Z': if (attacker->type == 'M') attacker->cards.clear(), attacker->arming=false; break;
            }
        }
    }
}

bool Pig::cost(Pig* attacker, char c) {
    if (this->del(c)) {
        return true;
    }
    hurt(attacker);
    return false;
}

bool Pig::findJ(Pig *attacker) {
    Pig* nxt = attacker;
    do {
        // "找个好心的猪猪帮我挡刀"
        if (this->isJumpItsFriend(nxt) && nxt->del('J')) {
            nxt->jump();
            return !nxt->useJ(this);
        }
        nxt = nxt->getNextPig();
    } while (nxt != attacker);
    return false;
}

bool Pig::useJ(Pig *pig) {
    for (Pig* nxt = getNextPig(); nxt != this; nxt = nxt->getNextPig()) {
        // "套娃指找找有没有猪猪会阻止我帮别人挡刀"
        if (!this->isJumpItsFriend(nxt) && nxt->del('J')) {
            nxt->jump();
            return !pig->findJ(nxt);
        }
    }
    return false;
}