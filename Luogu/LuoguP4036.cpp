#include <bits/stdc++.h>
#define okline() fprintf(stderr, "Debug: Line %d is running\n", __LINE__)
#if __cplusplus < 201103L && !defined(nullptr)
#  define nullptr NULL
#endif
const int N = 100000;
const int Np = N + 5;
const long long mod = 1000000007;
class node;
extern node *root;
extern long long j26[];
class node {
   public:
    node *fa;
    node *son[2];
    char val;
    int size;
    long long hsum;
    inline node() {
        fa = son[0] = son[1] = nullptr;
        val = size = hsum = 0;
    }
    inline int get() { return this && fa ? fa->son[1] == this : -1; }
    inline node *getfa() { return this ? fa : nullptr; }
    inline node *getson(int x) { return this ? son[x] : nullptr; }
    inline char getval() { return this ? val : 0; }
    inline int getsize() { return this ? size : 0; }
    inline long long gethsum() { return this ? hsum : 0; }
    inline node *pushup() {
        size = son[0]->getsize() + son[1]->getsize() + 1;
        hsum = (son[0]->gethsum() + j26[son[0]->getsize()] *
          ((val + 26 * son[1]->gethsum()) % mod)) % mod;
    }
    inline node *rotate() {
        int t = get();
        if (fa->son[t] = son[!t]) {
            son[!t]->fa = fa;
        }
        son[!t] = fa;
        if (fa = fa->fa) {
            fa->son[son[!t]->get()] = this;
        }
        son[!t]->fa = this;
        son[!t]->pushup();
        pushup();
        return fa ? this : root = this;
    }
    inline node *splay() {
        while (this != root) {
            if (fa->fa) {
                (get() == fa->get() ? fa : this)->rotate();
            }
            rotate();
        }
    }
};
inline node *findrank(int kth) {
    node *now = root;
    while (1) {
        if (kth <= now->son[0]->getsize()) {
            now = now->son[0];
        } else {
            kth -= now->son[0]->getsize() + 1;
            if (!kth) {
                return now->splay();
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
        if (!now->son[t = kth <= now->son[0]->getsize()]) {
            break;
        }
        if (t) {
            now = now->son[0];
        } else {
            kth -= now->son[0]->getsize() + 1;
            now = now->son[1];
        }
    }
    (now->son[t] = new node)->fa = now;
    (now = now->son[t])->val = now->hsum = val;
    return now->splay();
}
inline int query(int l, int r) {
    fprintf(stderr, "Debug: query(%d, %d);\n", l, r);
    node *now = findrank(r + 2);
    okline();
    findrank(l);
    okline();
    if (now != root->son[1]) {
        fprintf(stderr, "Debug: now: {\n");
        fprintf(stderr, "Debug:     this: 0x%08X, \n", now);
        fprintf(stderr, "Debug:     fa: {\n");
        fprintf(stderr, "Debug:         this: 0x%08X, \n", now->fa);
        fprintf(stderr, "Debug:         fa: 0x%08X, \n", now->fa->fa);
        fprintf(stderr, "Debug:         son: [0x%08X, 0x%08X]\n", now->fa->son[0], now->fa->son[1]);
        fprintf(stderr, "Debug:     },\n");
        fprintf(stderr, "Debug:     son: [{\n");
        fprintf(stderr, "Debug:         this: 0x%08X, \n", now->son[0]);
        fprintf(stderr, "Debug:         fa: 0x%08X, \n", now->son[0]->fa);
        fprintf(stderr, "Debug:         son: [0x%08X, 0x%08X]\n", now->son[0]->son[0], now->son[0]->son[1]);
        fprintf(stderr, "Debug:     }, {\n");
        fprintf(stderr, "Debug:         this: 0x%08X, \n", now->son[1]);
        fprintf(stderr, "Debug:         fa: 0x%08X, \n", now->son[1]->fa);
        fprintf(stderr, "Debug:         son: [0x%08X, 0x%08X]\n", now->son[1]->son[0], now->son[1]->son[1]);
        fprintf(stderr, "Debug:     }]\n");
        fprintf(stderr, "Debug: }\n");
        okline();
        now->rotate();
    }
    okline();
    return root->son[1]->son[0]->hsum;
}
int n, x, y, l, r, mid;
long long j26[Np];
node *root;
std::string str;
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
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
            l = 1;
            r = root->size - y - 1;
            while (l < r) {
                mid = l + r + 1 >> 1;
                fprintf(stderr, "Debug: l = %d; r = %d; mid = %d;\n", l, r, mid);
                if (query(x, x + mid - 1) != query(y, y + mid - 1)) {
                    r = mid - 1;
                } else {
                    l = mid;
                }
            }
            std::cout << l << std::endl;
        } else if (str[0] == 'R') {
            std::cin >> x >> str;
            findrank(x + 1)->val = str[0] - 'a';
            root->pushup();
        } else {
            std::cin >> x >> str;
            insert(x + 1, str[0]);
        }
    }
    return 0;
}