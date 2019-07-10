#include <bits/stdc++.h>
const int N = 100005;
int cnt, n, num, opt, root, x;
int father[N], lson[N], rson[N], sum[N], data[N], val[N];
void insert(int, int = root);
void updata(int);
void leftrotate(int);
void rightrotate(int);
void pushup(int);
void del(int = root);
int rank(int = root);
int prank(int = root);
int lx(int = root);
int rx(int = root);
int main() {
    srand(time(NULL));
    scanf("%d", &n);
    while (n--) {
        scanf("%d %d", &opt, &x);
        if (opt == 1) {
            if (!num) {
                root = num = sum[cnt] = 1;
                ++cnt;
                father[cnt] = 0;
                data[cnt] = x;
                val[cnt] = rand();
            } else {
                insert(x);
            }
        } else if (opt == 2) {
            del(x);
        } else if (opt == 3) {
            printf("%d\n", rank(x));
        } else if (opt == 4) {
            printf("%d\n", prank(x));
        } else if (opt == 5) {
            printf("%d\n", lx(x));
        } else if (opt == 6) {
            printf("%d\n", rx(x));
        }
    }
    return 0;
}
inline void insert(int x, int v) {
    if (data[v] < x) {
        if (lson[v]) {
            insert(x, lson[v]);
        } else {
            ++cnt;
            lson[v] = cnt;
            data[cnt] = x;
            sum[cnt] = 1;
            father[cnt] = v;
            val[cnt] = rand();
        }
    } else {
        if (rson[v]) {
            insert(x, rson[v]);
        } else {
            ++cnt;
            rson[v] = cnt;
            data[cnt] = x;
            sum[cnt] = 1;
            father[cnt] = v;
            val[cnt] = rand();
        }
    }
    updata(v);
    pushup(v);
}
inline void updata(int v) {
    if (val[v] < val[father[v]]) {
        if (lson[father[v]] == v) {
            leftrotate(v);
        } else {
            rightrotate(v);
        }
    }
}
inline void leftrotate(int v) {
    
}