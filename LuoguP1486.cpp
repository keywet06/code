#include <bits/stdc++.h>
class point {
    public:
        point *lson, *rson, *fa;
        int size, num, val;
};
const int N = 500005;
char opt;
int min, n, x, lazy, num, ans;
point po[N];
point *cnt = po, *root, *potmp;
char ReadARealChar();
void update(point*);
void rotate(point*);
void splay(point*);
void makeroot(point*);
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
                ++ans;
                continue;
            }
            if (root) {
                insert(x - lazy);
            } else {
                root = ++cnt;
                root->num = 1;
                root->size = 1;
                root->val = x;
            }
        } else if (opt == 'A') {
            lazy += x;
        } else if (opt == 'S') {
            lazy -= x;
            fprintf(stderr, "D: insert(%d)\n", min - lazy - 1);
            insert(min - lazy - 1);
            fprintf(stderr, "D: OK1!\n");
            potmp = find(min - lazy - 1);
            fprintf(stderr, "D: OK2!\n");
            makeroot(potmp);
            fprintf(stderr, "D: OK3!\n");
            if (!potmp->rson) {
                ans += root->size - 1;
                root = 0;
                continue;
            }
            fprintf(stderr, "D: OK4!\n");
            rotate(potmp->rson);
            fprintf(stderr, "D: OK5!\n");
            ans += root->lson->size - 1;
            root->lson = 0;
            update(root);
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
    v->size = (v->lson ? v->lson->size : 0) + (v->rson ? v->rson->size : 0) + v->num;
}
inline void rotate(point *v) {
    if (v->fa == root) {
        root = v;
    }
    if (v->fa->lson == v) {
        v->fa->lson = v->rson;
        if (v->rson) {
            v->rson->fa = v->fa;
        }
        v->rson = v->fa;
        v->fa = v->rson->fa;
        if (v->fa) {
            (v->fa->lson == v->rson ? v->fa->lson : v->fa->rson) = v;
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
            (v->fa->rson == v->lson ? v->fa->rson : v->fa->lson) = v;
        }
        v->lson->fa = v;
        update(v->lson);
    }
    update(v);
}
inline void splay(point *v) {
    if (v->fa == root) {
        rotate(v);
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
inline void insert(int x) {
    point *v = root;
    while (x != v->val && x < v->val ? v->lson : v->rson) {
        v = x < v->val ? v->lson : v->rson;
    }
    if (x == v->val) {
        ++v->num;
    } else {
        (++cnt)->fa = v;
        v = (x < v->val ? v->lson : v->rson) = cnt;
        v->num = 1;
        v->size = 1;
        v->val = x;
    }
    while (v != root) {
        update(v);
        v = v->fa;
    }
    update(root);
    makeroot(cnt);
}
inline point *find(int x) {
    point *v = root;
    while (1) {
        if (v->val == x) {
            return v;
        }
        v = v->val < x ? v->lson : v->rson;
    }
    return 0;
}
inline point *rank(int x) {
    point *v = root;
    while (1) {
        if (v->lson && x <= v->lson->size) {
            v = v->lson;
        } else if (v->rson && x > v->size - v->rson->size) {
            v = v->rson;
        } else {
            return v;
        }
    }
    return 0;
}