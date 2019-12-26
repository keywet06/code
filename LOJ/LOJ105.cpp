#include <bits/stdc++.h>
#if __cplusplus < 201103L && !defined(nullptr)
#  define nullptr NULL
#endif
struct point {
   public:
    point *fa;
    point *son[2];
    int val, size, lazy;
    point() {
        fa = son[0] = son[1] = nullptr;
        val = size = lazy = 0;
    }
};
point *root;
void build(point *, int, int);
int get(point *);
int size(point *);
void pushup(point *);
void pushdown(point *);
point *rotate(point *);
point *splay(point *);
point *kth(int, int = 1);
inline void build(point *v, int l, int r) {
    v->val = l + r >> 1;
    v->size = r - l + 1;
    if (l < v->val) {
        (v->son[0] = new point)->fa = v;
        build(v->son[0], l, v->val - 1);
    }
    if (v->val < r) {
        (v->son[1] = new point)->fa = v;
        build(v->son[1], v->val + 1, r);
    }
}
inline int get(point *v) { return !v || !v->fa ? -1 : v->fa->son[1] == v; }
inline int size(point *v) { return v ? v->size : 0; }
inline void pushup(point *v) {
    v->size = size(v->son[0]) + size(v->son[1]) + 1;
}
inline void pushdown(point *v) {
    if (!v->lazy) {
        return;
    }
    std::swap(v->son[0], v->son[1]);
    if (v->son[0]) {
        v->son[0]->lazy ^= 1;
    }
    if (v->son[1]) {
        v->son[1]->lazy ^= 1;
    }
    v->lazy = 0;
}
inline point *rotate(point *v) {
    pushdown(v->fa);
    pushdown(v);
    int t = get(v);
    if (v->fa->son[t] = v->son[!t]) {
        v->fa->son[t]->fa = v->fa;
    }
    v->son[!t] = v->fa;
    if (v->fa = v->fa->fa) {
        v->fa->son[get(v->son[!t])] = v;
    } else {
        root = v;
    }
    v->son[!t]->fa = v;
    pushup(v->son[!t]);
    pushup(v);
    return v;
}
inline point *splay(point *v) {
    while (v != root) {
        if (get(v) == get(v->fa)) {
            rotate(v->fa);
        }
        rotate(v);
    }
    return v;
}
inline point *kth(int x, int keep) {
    point *v = root;
    while (1) {
        pushdown(v);
        if (x <= size(v->son[0])) {
            v = v->son[0];
        } else {
            x -= size(v->son[0]) + 1;
            if (x <= 0) {
                return keep ? splay(v) : v;
            }
            v = v->son[1];
        }
    }
}
int n, m, x, y;
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m;
    build(root = new point, 0, n + 1);
    for (int i = 1; i <= m; ++i) {
        std::cin >> x >> y;
        splay(kth(y + 2));
        splay(kth(x));
        point *t = kth(y + 2, 0);
        while (t != root->son[1]) {
            rotate(t);
        }
        root->son[1]->son[0]->lazy ^= 1;
    }
    for (int i = 1; i <= n; ++i) {
        std::cout << kth(i + 1)->val << " ";
    }
    std::cout << std::endl;
    return 0;
}