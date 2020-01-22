#include <bits/stdc++.h>
#if __cplusplus < 201103L && !defined(nullptr)
#  define nullptr NULL
#endif
const int N = 100000;
const int Np = N + 5;
const int mod = 1e9 + 7;
class node;
extern node *root;
extern unsigned long long j26[];
class node {
   public:
    node *fa;
    node *son[2];
    char val;
    int size;
    unsigned long long hsum;
    inline node() {
        fa = son[0] = son[1] = nullptr;
        val = size = hsum = 0;
    }
    inline void free() {
        if (!this) {
            return;
        }
        son[0]->free();
        son[1]->free();
        delete this;
    }
    inline int G() { return fa->son[1] == this; }
    inline node *Fa() { return this ? fa : nullptr; }
    inline node *Son(int x) { return this ? son[x] : nullptr; }
    inline char Val() { return this ? val : 0; }
    inline int Size() { return this ? size : 0; }
    inline unsigned long long Hsum() { return this ? hsum : 0; }
    inline void pushup() {
        size = son[0]->Size() + son[1]->Size() + 1;
        hsum = (son[0]->Hsum() + j26[son[0]->Size()] *
          (val + 26 * son[1]->Hsum() % mod)) % mod;
    }
    inline void rotate() {
        int t = G();
        if (fa->son[t] = son[!t]) {
            son[!t]->fa = fa;
        }
        son[!t] = fa;
        if (fa = fa->fa) {
            fa->son[son[!t]->G()] = this;
        }
        son[!t]->fa = this;
        son[!t]->pushup();
        pushup();
        if (!fa) {
            root = this;
        }
    }
    inline void splay() {
        while (fa) {
            if (fa->fa && fa->G() == G()) {
                fa->rotate();
            }
            rotate();
        }
    }
};
inline node *findrank(int kth) {
    node *now = root;
    while (1) {
        if (kth <= now->son[0]->Size()) {
            now = now->son[0];
        } else {
            kth -= now->son[0]->Size() + 1;
            if (!kth) {
                now->splay();
                return now;
            }
            now = now->son[1];
        }
    }
}
inline node *insert(char val, int kth) {
    val -= 'a';
    if (!root) {
        root = new node;
        root->val = root->hsum = val;
        root->size = 1;
        return root;
    }
    node *now = root;
    int t;
    while (1) {
        if (!now->son[t = kth > now->son[0]->Size()]) {
            break;
        }
        if (!t) {
            now = now->son[0];
        } else {
            kth -= now->son[0]->Size() + 1;
            now = now->son[1];
        }
    }
    (now->son[t] = new node)->fa = now;
    now->size = 1;
    (now = now->son[t])->val = now->hsum = val;
    now->splay();
    return now;
}
inline int query(int l, int r) {
    node *now = findrank(r + 2);
    findrank(l);
    if (now != root->son[1]) {
        now->rotate();
    }
    return root->son[1]->son[0]->hsum;
}
int n, x, y, l, r, mid, T;
unsigned long long j26[Np];
node *root, *tmp;
std::string str;
int Main() {
    j26[0] = 1;
    for (int i = 1; i < Np; ++i) {
        j26[i] = j26[i - 1] * 26 % mod;
    }
    std::cin >> str;
    insert('a', 0);
    insert('a', 1);
    for (int i = 0; i < str.size(); ++i) {
        insert(str[i], i + 1);
    }
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> str;
        if (str[0] == 'Q') {
            std::cin >> x >> y;
            if (x > y) {
                std::swap(x, y);
            }
            l = 1;
            r = root->size - y - 1;
            if (query(x, x) != query(y, y)) {
                std::cout << 0 << std::endl;
                continue;
            }
            while (l < r) {
                mid = l + r + 1 >> 1;
                if (query(x, x + mid - 1) != query(y, y + mid - 1)) {
                    r = mid - 1;
                } else {
                    l = mid;
                }
            }
            std::cout << l << std::endl;
        } else if (str[0] == 'R') {
            std::cin >> x >> str;
            (tmp = findrank(x + 1))->val = str[0] - 'a';
            tmp->pushup();
            tmp->splay();
        } else {
            std::cin >> x >> str;
            insert(str[0], x + 1);
        }
    }
    root->free();
    root = nullptr;
    return 0;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> T;
    while (T--) {
        Main();
    }
    return 0;
}