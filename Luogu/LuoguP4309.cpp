#include <bits/stdc++.h>
#if __cplusplus < 201103L && !defined(nullptr)
#define nullptr NULL
#endif
namespace Octinc {

class Splay;
class Splay {
   public:
    class node;

   public:
    class node {
       public:
        node *fa;
        node *son[2];
        int val, lazy, size;
        long long ans[2][2];

       public:
        node();
        ~node();
        void free();
        int G();
        node *Fa();
        node *Son(int);
        int Val();
        int Size();
        long long Ans(int, int);
        node *pushdown();
        node *pushup();
        node *rotate();
        node *splay();
        int rank();
    };

   protected:
    void insert(node *, int, int *, int *);

   public:
    Splay();
    ~Splay();
    node *insert(int, int);
    node *insert(int, int *, int *);
    node *find(int);
    node *split(int, int);
    node *split(node *, node *);
    node *remove(int, int);
    node *remove(int);

   public:
    node *root;
};
long long t0(long long);

inline void Splay::insert(node *now, int t, int *start, int *end) {
    if (start == end) {
        return;
    }
    (now->son[t] = new node)->fa = now;
    now = now->son[t];
    int *middle = start + (end - start >> 1);
    now->val = now->ans[0][0] = now->ans[0][1] = now->ans[1][0] =
      now->ans[1][1] = *middle;
    insert(now, 0, start, middle);
    insert(now, 1, middle, end);
    now->pushup();
}
inline Splay::node::node() {
    fa = son[0] = son[1] = nullptr;
    lazy = 0;
    size = 1;
}
inline Splay::node::~node() {}
inline void Splay::node::free() {
    if (this) {
        son[0]->free();
        son[1]->free();
        delete this;
    }
}
inline int Splay::node::G() { return fa->son[1] == this; }
inline Splay::node *Splay::node::Fa() { return this ? fa : nullptr; }
inline Splay::node *Splay::node::Son(int x) { return this ? son[x] : nullptr; }
inline int Splay::node::Val() { return this ? val : 0; }
inline int Splay::node::Size() { return this ? size : 0; }
inline long long Splay::node::Ans(int x, int y) { return this ? ans[x][y] : 0; }
inline Splay::node *Splay::node::pushdown() {
    if (lazy & 2) {
        if (son[0]) {
            son[0]->lazy |= 2;
            son[0]->val = val;
        }
        if (son[1]) {
            son[1]->lazy |= 2;
            son[1]->val = val;
        }
        ans[0][0] = ans[0][1] = ans[1][0] = t0((ans[1][1] = size * val) - val) +
          val;
        lazy ^= 2;
    }
    if (lazy & 1) {
        std::swap(son[0], son[1]);
        std::swap(ans[0][1], ans[1][0]);
        if (son[0]) {
            son[0]->lazy ^= 2;
        }
        if (son[1]) {
            son[1]->lazy ^= 2;
        }
        lazy ^= 1;
    }
    return this;
}
inline Splay::node *Splay::node::pushup() {
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
inline Splay::node *Splay::node::rotate() {
    extern node *root;
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
inline Splay::node *Splay::node::splay() {
    while (fa) {
        if (fa->fa && fa->G() == G()) {
            fa->rotate();
        }
        rotate();
    }
    return this;
}
inline int Splay::node::rank() {
    splay();
    return son[0]->Size() + 1;
}
inline Splay::Splay() { root = nullptr; }
inline Splay::~Splay() { root->free(); }
inline Splay::node *Splay::insert(int rk, int x) {
    if (!root) {
        root = new node;
        root->val = root->ans[0][0] = root->ans[0][1] = root->ans[1][0] =
          root->ans[0][1] = x;
        return root;
    }
    node *now = root;
    int t;
    while (1) {
        now->pushdown();
        if (!now->son[t = rk > now->son[0]->Size()]) {
            break;
        }
        if (t) {
            rk -= now->son[0]->Size();
        }
        now = now->son[1];
    }
    now = ((now->son[t] = new node)->fa = now)->son[t];
    now->val = now->ans[0][0] = now->ans[0][1] = now->ans[1][0] =
      now->ans[1][1] = x;
    return now->splay();
}
inline Splay::node *Splay::insert(int rk, int *start, int *end) {
    if (!root) {
        root = new node;
        insert(root, 0, start, end);
        root = root->son[0];
        delete root->fa;
        root->fa = nullptr;
        return root;
    }
    node *now = root;
    int t;
    while (1) {
        now->pushdown();
        if (!now->son[t = rk > now->son[0]->Size()]) {
            break;
        }
        if (t) {
            rk -= now->son[0]->Size();
        }
        now = now->son[1];
    }
    insert(now, t, start, end);
    return now->pushup()->splay();
}
inline Splay::node *Splay::find(int rk) {
    node *now = root;
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
inline Splay::node *Splay::split(int l, int r) {
    if (l == 1 || r == root->size) {
        return l == 1 ? (r == root->size ? root : find(r + 1)->son[0]) :
          find(l - 1)->son[1];
    }
    node *now = find(r + 1);
    find(l - 1);
    if (now->fa->fa) {
        now->rotate();
    }
    return root->son[1]->son[0];
}
inline Splay::node *Splay::split(node *l, node *r) {
    return split(l->rank(), r->rank());
}
inline Splay::node *Splay::remove(int l, int r) {
    node *now = split(l, r)->fa;
    if (!now) {
        delete root;
        return nullptr;
    }
    delete split(l, r);
    now->pushup()->splay();
    return nullptr;
}
inline Splay::node *Splay::remove(int x) {
    return remove(x, x);
}
inline long long t0(long long x) { return std::max(x, 0ll); }

}  // namespace Octinc
const int N = 500000;
const int Np = N + 5;
int n, m, p, x, y;
int a[N];
std::string str;
Octinc::Splay Splay;
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    Splay.insert(0, a, a + n);
    while (m--) {
        std::cin >> str;
        if (str == (std::string)("INSERT")) {
            std::cin >> x >> p;
            for (int i = 0; i < p; ++i) {
                std::cin >> a[i];
            }
            Splay.insert(x, a, a + p);
        } else if (str == (std::string)("DELETE")) {
            std::cin >> x >> p;
            Splay.remove(x, x + p - 1);
        } else if (str == (std::string)("MAKE-SAME")) {
            std::cin >> x >> p >> y;
            Octinc::Splay::node *now = Splay.split(x, x + p - 1);
            now->lazy |= 2;
            now->val = y;
        } else if (str == (std::string)("REVERSE")) {
            std::cin >> x >> p;
            Splay.split(x, x + p - 1)->lazy ^= 1;
        } else if (str == (std::string)("GET-SUM")) {
            std::cin >> x >> y;
            std::cout << Splay.split(x, y)->ans[1][1] << std::endl;
        } else if (str == (std::string)("MAX-SUM")) {
            std::cout << Splay.root->ans[0][0] << std::endl;
        }
    }
    return 0;
}