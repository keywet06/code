#include <bits/stdc++.h>
class point {
    public:
        point *lson, *rson, *fa;
        int size, val;
};
const int N = 500005;
char opt;
int min, n, x, lazy;
point po[N];
point *cnt = po, *root, potmp;
char ReadARealChar();
void update(point*);
void rotate(point*);
void splay(point*);
void makeroot(point*);
void insert(int, point* = root);
point *successor(int, point* = root);
point *rank(int, point* = root);
int main() {
    scanf("%d %d", &n, &min);
    for (int i = 1; i <= n; ++i) {
        opt = ReadARealChar();
        scanf("%d", &x);
        if (opt == 'I') {
            if (root) {
                insert(x - lazy);
            } else {
                root = ++cnt;
                po[root]->size = 1;
                po[root]->val = x;
            }
        } else if (opt == 'A') {
            lazy += x;
        } else if (opt == 'S') {
            lazy -= x;
            potmp = successor(x - lazy);
            if (potmp) {
                makeroot(potmp);
                root->lson = 0;
                update(root);
            }
        } else {
            printf("%d\n", rank(x)->val);
        }
    }
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
    v->size = (v->lson ? v->lson->size : 0) + (v->rson ? v->rson->size : 0);
}
inline void rotate(point *v) {
    if (v->fa->lson == v) {
        v->fa->lson = v->rson;
        if (v->rson) {
            v->rson->fa = v->fa;
        }
        v->rson = v->fa;
        v->fa = v->rson->fa;
        if (v->fa) {
            if (v->fa->lson == v->rson) {
                v->fa->lson = v;
            } else {
                v->fa->rson = v;
            }
        }
        v->rson->fa = v;
        update(v->rson);
    } else {
        v->fa->rson = v->lson;
        if (v->lson) {
            v->lson->fa = v->fa;
        }
        v->lson = v->fa;
        v->fa = v->lson->fa;
        if (v->fa) {
            if (v->fa->rson == v->lson) {
                v->fa->rson = v;
            } else {
                v->fa->lson = v;
            }
        }
        v->lson->fa = v;
        update(v->lson);
    }
    update(v);
}
inline void splay(point *v) {
    if (v->fa == root) {
        rotate(v);
        root->fa = v;
        root = v;
        root->fa = 0;
    } else if ((v->fa->lson == v && v->fa->fa->lson == v->fa) || (v->fa->rson == v && v->fa->fa->rson == v->fa)) {
        rotate(v->fa);
        rotate(v);
    } else {
        rotate(v);
    }
}
inline void makeroot(point *v) {
    while (v != root) {
        splay(v);
    }
}
inline void insert(int, point *v) {
    
}