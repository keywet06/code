#include <bits/stdc++.h>
class point {
    public:
        point *son[2], *fa;
        int size, num, val, lazy;
};
const int N = 200005;
int m, n, x, y;
point po[N];
point *cnt = po, *root, *tmp;
void update(point*);
void pushdown(point*);
int fason(point*);
void rotate(point*);
void splay(point*);
void insert(int);
point *rank(int);
int main() {
    scanf("%d %d", &n, &m);
    root = ++cnt;
    root->num = 1;
    root->size = 1;
    root->val = 0;
    for (int i = 1; i <= n + 1; ++i) {
        insert(i);
    }
    while (m--) {
        scanf("%d %d", &x, &y);
        splay(rank(y + 2));
        splay(rank(x));
        tmp = rank(y + 2);
        while (tmp != root->son[1]) {
            rotate(tmp);
        }
        root->son[1]->son[0]->lazy ^= 1;
    }
    for (int i = 1; i <= n; ++i) {
        printf("%d ", rank(i + 1)->val);
    }
    printf("\n");
    return 0;
}
inline void update(point *v) {
    v->size = (v->son[0] ? v->son[0]->size : 0) + (v->son[1] ? v->son[1]->size : 0) + v->num;
}
inline void pushdown(point *v) {
    if (v->lazy) {
        std::swap(v->son[0], v->son[1]);
        if (v->son[0]) {
            v->son[0]->lazy ^= 1;
        }
        if (v->son[1]) {
            v->son[1]->lazy ^= 1;
        }
        v->lazy = 0;
    }
}
inline int fason(point *v) {
    return v->fa->son[1] == v;
}
inline void rotate(point *v) {
    pushdown(v->fa);
    pushdown(v);
    if (v->fa == root) {
        root = v;
    }
    int fsv = fason(v);
    v->fa->son[fsv] = v->son[!fsv];
    if (v->son[!fsv]) {
        v->son[!fsv]->fa = v->fa;
    }
    v->son[!fsv] = v->fa;
    v->fa = v->son[!fsv]->fa;
    if (v->fa) {
        v->fa->son[(v->fa->son[fsv] != v->son[!fsv]) ^ fsv] = v;
    }
    v->son[!fsv]->fa = v;
    update(v->son[!fsv]);
    update(v);
}
inline void splay(point *v) {
    while (v != root) {
        if (v->fa == root) {
            rotate(v);
        } else if (fason(v) == fason(v->fa)) {
            rotate(v->fa);
            rotate(v);
        } else {
            rotate(v);
        }
    }
}
inline void insert(int x) {
    point *v = root, *tmp;
    while (x != v->val && v->son[x > v->val]) {
        v = v->son[x > v->val];
    }
    if (x == v->val) {
        ++v->num;
        tmp = v;
    } else {
        (++cnt)->fa = v;
        v = v->son[x > v->val] = cnt;
        v->num = 1;
        v->size = 1;
        v->val = x;
        tmp = cnt;
    }
    while (v != root) {
        update(v);
        v = v->fa;
    }
    update(root);
    splay(tmp);
}
inline point *rank(int x) {
    point *v = root;
    while (1) {
        pushdown(v);
        if (v->son[0] && x <= v->son[0]->size) {
            v = v->son[0];
        } else if (v->son[1] && x > v->size - v->son[1]->size) {
            x -= v->size - v->son[1]->size;
            v = v->son[1];
        } else {
            return v;
        }
    }
    return 0;
}
