#include <bits/stdc++.h>
#define okline() fprintf(stderr, "Debug: Line %d is running.\n", __LINE__);
#if __cplusplus < 201103L && !defined(nullptr)
#define nullptr NULL
#endif

class node;
class iterater;

class iterater {
   public:
    unsigned int __node;
    node *operator->() {
        return (node *)(__node);
    }
    iterater &operator=(node *x) {
        __node = (unsigned int)(x);
        return *this;
    }
};

class node {
   public:
    iterater fa;
    iterater son[2];
    char lazy;
    int val, size;
    int ans[2][2];

   public:
    node();
    ~node();
    void free();
    int G();
    int Val();
    int Size();
    int Ans(int, int);
    iterater pushdown();
    iterater pushup();
    iterater rotate();
    iterater splay();
    int rank();
};

void insert(iterater, int, int *, int *);

iterater insert(int, int *, int *);
iterater find(int);
iterater split(int, int);
iterater remove(int, int);

iterater root;

int t0(int);

inline void insert(iterater now, int t, int *start, int *end) {
    if (start == end) {
        return;
    }
    (now->son[t] = new node)->fa = now;
    now = now->son[t];
    int *middle = start + (end - start >> 1);
    now->val = *middle;
    insert(now, 0, start, middle);
    insert(now, 1, middle + 1, end);
    now->pushup();
}
inline node::node() {
    fa = son[0] = son[1] = nullptr;
    lazy = 0;
    size = 1;
}
inline node::~node() {}
inline void node::free() {
    if (this) {
        son[0]->free();
        son[1]->free();
        delete this;
    }
}
inline int node::G() { return fa->son[1] == this; }
inline int node::Val() { return this ? val : 0; }
inline int node::Size() { return this ? size : 0; }
inline int node::Ans(int x, int y) { return this ? ans[x][y] : 0; }
inline iterater node::pushdown() {
    if (lazy & 2) {
        if (son[0]) {
            son[0]->lazy |= 2;
            son[0]->val = val;
            son[0]->ans[0][0] = son[0]->ans[0][1] = son[0]->ans[1][0] =
              t0((son[0]->ans[1][1] = son[0]->size * val) - val) + val;
        }
        if (son[1]) {
            son[1]->lazy |= 2;
            son[1]->val = val;
            son[1]->ans[0][0] = son[1]->ans[0][1] = son[1]->ans[1][0] =
              t0((son[1]->ans[1][1] = son[1]->size * val) - val) + val;
        }
        lazy ^= 2;
    }
    if (lazy & 1) {
        if (son[0]) {
            son[0]->lazy ^= 1;
            std::swap(son[0]->son[0], son[0]->son[1]);
            std::swap(son[0]->ans[0][1], son[0]->ans[1][0]);
        }
        if (son[1]) {
            son[1]->lazy ^= 1;
            std::swap(son[1]->son[0], son[1]->son[1]);
            std::swap(son[1]->ans[0][1], son[1]->ans[1][0]);
        }
        lazy ^= 1;
    }
    return this;
}
inline iterater node::pushup() {
    size = son[0]->Size() + 1 + son[1]->Size();
    ans[1][1] = son[0]->Ans(1, 1) + val + son[1]->Ans(1, 1);
    ans[0][0] = std::max(std::max(son[0]->Ans(0, 0), son[1]->Ans(0, 0)), 
      t0(son[0]->Ans(0, 1)) + val + t0(son[1]->Ans(1, 0)));
    ans[0][1] = std::max(son[1] ? son[1]->Ans(0, 1) : val,
      t0(son[0]->Ans(0, 1)) + val + son[1]->Ans(1, 1));
    ans[1][0] = std::max(son[0] ? son[0]->Ans(1, 0) : val,
      t0(son[1]->Ans(1, 0)) + val + son[0]->Ans(1, 1));
    return this;
}
inline iterater node::rotate() {
    int t = G();
    pushdown();
    if (fa->son[t] = son[!t]) {
        son[!t]->fa = fa;
    }
    son[!t] = fa;
    if (fa = fa->fa) {
        fa->son[son[!t]->G()] = this;
    }
    son[!t]->fa = this;
    son[!t]->pushup();
    return fa ? pushup() : root = pushup();
}
inline iterater node::splay() {
    while (fa) {
        if (fa->fa && fa->G() == G()) {
            fa->rotate();
        }
        rotate();
    }
    return this;
}
inline int node::rank() {
    splay();
    return son[0]->Size() + 1;
}
inline iterater insert(int rk, int *start, int *end) {
    if (!root) {
        insert(root = new node, 0, start, end);
        root = root->son[0];
        delete root->fa;
        root->fa = nullptr;
        return root;
    }
    iterater now = root;
    int t;
    while (1) {
        now->pushdown();
        if (!now->son[t = rk > now->son[0]->Size()]) {
            break;
        }
        if (t) {
            rk -= now->son[0]->Size() + 1;
        }
        now = now->son[t];
    }
    insert(now, t, start, end);
    return now->pushup()->splay();
}
inline iterater find(int rk) {
    int k = rk;
    iterater now = root;
    while (1) {
        now->pushdown();
        if (rk <= now->son[0]->Size()) {
            now = now->son[0];
        } else {
            rk -= now->son[0]->Size() + 1;
            if (!rk) {
                return now->splay();
            }
            now = now->son[1];
        }
    }
}
inline iterater split(int l, int r) {
    if (l == 1 || r == root->size) {
        return l == 1 ? (r == root->size ? root : find(r + 1)->son[0]) :
          find(l - 1)->son[1];
    }
    iterater now = find(r + 1);
    find(l - 1);
    if (root->son[1] != now) {
        now->rotate();
    }
    return root->son[1]->son[0];
}
inline iterater remove(int l, int r) {
    iterater now = split(l, r);
    if (now == root) {
        root->free();
        return root = nullptr;
    }
    int t = now->G();
    delete (now = now->fa)->son[t];
    now->son[t] = nullptr;
    now->pushup()->splay();
    return nullptr;
}
inline int t0(int x) { return std::max(x, 0); }

const int N = 500000;
const int Np = N + 5;
int n, m, p, x, y;
int a[N];
std::string str;
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    insert(0, a, a + n);
    while (m--) {
        std::cin >> str;
        if (str == (std::string)("INSERT")) {
            std::cin >> x >> p;
            for (int i = 0; i < p; ++i) {
                std::cin >> a[i];
            }
            insert(x, a, a + p);
        } else if (str == (std::string)("DELETE")) {
            std::cin >> x >> p;
            remove(x, x + p - 1);
        } else if (str == (std::string)("MAKE-SAME")) {
            std::cin >> x >> p >> y;
            iterater now = split(x, x + p - 1);
            now->lazy |= 2;
            now->val = y;
            now->ans[0][0] = now->ans[0][1] = now->ans[1][0] =
              t0((now->ans[1][1] = now->size * y) - y) + y;
            now->splay();
        } else if (str == (std::string)("REVERSE")) {
            std::cin >> x >> p;
            iterater now = split(x, x + p - 1);
            now->lazy ^= 1;
            std::swap(now->son[0], now->son[1]);
            std::swap(now->ans[0][1], now->ans[1][0]);
            now->splay();
        } else if (str == (std::string)("GET-SUM")) {
            std::cin >> x >> p;
            std::cout << split(x, x + p - 1)->ans[1][1] << std::endl;
        } else if (str == (std::string)("MAX-SUM")) {
            std::cout << root->ans[0][0] << std::endl;
        }
    }
    return 0;
}