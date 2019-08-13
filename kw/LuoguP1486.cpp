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
    }
}
inline void splay(point *v) {
    if (v->fa == root) {
        if (root->lson == v) {
            root->lson = v->rson;
            if (v->rson) {
                v->rson->fa = root;
            }
            v->rson = root;
        } else {
            root->rson = v->lson;
            if (v->lson) {
                v->lson->fa = root;
            }
            v->lson = root;
        }
        root->fa = v;
        root = v;
        root->fa = 0;
    } else if (v->fa->lson == v && v->)
}