#include <bits/stdc++.h>
const int N = 100005;
int cnt, root, n, opt, x;
int father[N], lson[N], rd[N], rson[N], size[N], val[N];
void insert(int, int = root);
void del(int, int = root);
int get_rank(int, int = root);
int get_num(int, int = root);
int qianqu(int, int = root);
int houji(int, int = root);
void new_point(int, int = root);
void updata(int);
void zig(int);
void zag(int);
int main() {
    scanf("%d", &n);
    while (n--) {
        scanf("%d %d", &opt, &x);
        if (opt == 1) {
            if (!root) {
                new_point(x);
            } else {
                insert(x);
            }
        } else if (opt == 2) {
            del(x);
        } else if (opt == 3) {
            printf("%d\n", get_rank(x));
        } else if (opt == 4) {
            printf("%d\n", get_num(x));
        } else if (opt == 5) {
            printf("%d\n", qianqu(x));
        } else {
            printf("%d\n", houji(x));
        }
    }
    return 0;
}
inline void insert(int x, int u) {
    if (x < val[u]) {
        if (lson[u]) {
            insert(x, lson[u]);
        } else {
            new_point(x, u);
            lson[u] = cnt;
        }
    } else {
        if (rson[u]) {
            insert(x, rson[u]);
        } else {
            new_point(x, u);
            rson[u] = cnt;
        }
    }
    updata(u);
}
inline void del(int x, int u) {
    if (x < val[u]) {
        del(x, lson[u]);
    } else if (x > val[u]) {
        del(x, rson[u]);
    } else {
        if (!lson[u] && !rson[u]) {
            if (lson[father[u]] == u) {
                lson[father[u]] = 0;
            } else {
                rson[father[u]] = 0;
            }
        } else if (!lson[u] && rd[lson[u]] < rd[rson[u]]) {
            zig(u);
        } else {
            zag(u);
        }
    }
}
inline int get_rank(int x, int u) {
    if (val[u] < x) {
        return get_rank(x, lson[u]);
    } else if (val[u] == x) {
        if (!lson[u]) {
            return 1;
        } else {
            return size[lson[u]] + 1;
        }
    } else if (val[u] > x) {
        if (!lson[u]) {
            return get_rank(x, rson[u]) + 1;
        } else {
            return get_rank(x, rson[u]) + size[lson[u]] + 1;
        }
    }
}
inline int get_num(int x, int u) {
    if (!lson) {
        if (u == 1) {
            return val[u];
        } else {
            return get_num(x - 1, rson[u]);
        }
    } else {
        if (u <= size[lson[u]]) {
            return get_num(x, lson[u]);
        } else if (u == size[lson[u]] + 1) {
            return val[u];
        } else {
            return get_num(x - size[lson[u]] - 1, rson[u]);
        }
    }
}