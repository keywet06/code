#include <bits/stdc++.h>
class point {
    public:
        point *son[2], *fa;
        int size, num, val;
};
const int N = 500005;
char opt;
int min, n, x, lazy, num, ans;
point po[N];
point *cnt = po, *root, *potmp;
char ReadARealChar();
void update(point*);
int fason(point*);
void rotate(point*);
void splay(point*);
void insert(int);
point *find(int);
point *rank(int);
int main() {
    scanf("%d %d", &n, &min);
    for (int i = 1; i <= n; ++i) {
        opt = ReadARealChar();
        scanf("%d", &x);
        if (opt == 'I') {
            if (x < min) {
                continue;
            }
            if (root) {
                insert(x - lazy);
            } else {
                root = ++cnt;
                root->num = 1;
                root->size = 1;
                root->val = x - lazy;
            }
        } else if (opt == 'A') {
            lazy += x;
        } else if (opt == 'S') {
            lazy -= x;
            if (!root) {
                continue;
            }
            insert(min - lazy - 1);
            potmp = find(min - lazy - 1);
            splay(potmp);
            ans += root->size - 1;
            if (!root->son[1]) {
                root = 0;
                continue;
            }
            root = root->son[1];
            root->fa = 0;
            update(root);
            ans -= root->size;
        } else {
            printf("%d\n", x > (root ? root->size : 0) ? -1 : rank(root->size - x + 1)->val + lazy);
        }
    }
    printf("%d\n", ans);
    return 0;
}
inline char ReadARealChar() {
    char a = getchar();
    while (a == ' ' || a == '\n' || a == '\r') {
        a = getchar();
    }
    return a;
}
inline void update(point *v) {
    v->size = (v->son[0] ? v->son[0]->size : 0) + (v->son[1] ? v->son[1]->size : 0) + v->num;
}
inline int fason(point *v) {
    return v->fa->son[1] == v;
}
inline void rotate(point *v) {
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
inline point *find(int x) {
    point *v = root;
    while (1) {
        if (v->val == x) {
            return v;
        }
        v = v->son[x > v->val];
    }
    return 0;
}
inline point *rank(int x) {
    point *v = root;
    while (1) {
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