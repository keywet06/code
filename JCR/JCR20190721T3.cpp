#include <bits/stdc++.h>
using namespace std;
const int INF = 1000000005;
const int N = 100005;
struct edge {
    int to, next;
};
struct node {
    int l, r, l1, r1, l2, r2, dis, c1, c2;
    void ini(int);
};
node t[12 * N];
char ch[10];
int n, q, cnt, tot, sum;
int last[N];
int v[3 * N], pos[N], c[N];
edge e[2 * N];
int read();
int max(int, int, int);
void update(int, int);
void dfs(int, int);
node query(node, node);
void build(int, int, int);
void modify(int, int);
int main() {
    sum = n = read();
    for (int i = 1; i <= n; i++) {
        c[i] = 1;
    }
    for (int i = 1; i < n; i++) {
        int u = read(), v = read();
        update(u, v);
    }
    dfs(1, 0);
    build(1, 1, tot);
    q = read();
    for (int i = 1; i <= q; i++) {
        scanf("%s", ch);
        if (ch[0] == 'C') {
            int x = read();
            if (c[x]) {
                sum--;
            } else {
                sum++;
            }
            c[x] ^= 1;
            modify(1, pos[x]);
        } else {
            if (sum == 0) {
                puts("-1");
            } else if (sum == 1) {
                puts("0");
            } else
                printf("%d\n", t[1].dis);
        }
    }
    return 0;
}
inline void node::ini(int x) {
    dis = -INF;
    c1 = c2 = 0;
    if (v[x] == -6) c2 = 1;
    if (v[x] == -9) c1 = 1;
    if (v[x] > 0 && c[v[x]])
        l1 = l2 = r1 = r2 = 0;
    else
        l1 = l2 = r1 = r2 = -INF;
}
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
inline int max(int a, int b, int c) { return max(max(a, b), c); }
inline void update(int u, int v) {
    e[++cnt].to = v;
    e[cnt].next = last[u];
    last[u] = cnt;
    e[++cnt].to = u;
    e[cnt].next = last[v];
    last[v] = cnt;
}
inline node query(node s1, node s2) {
    node s;
    int a = s1.c1, b = s1.c2, c = s2.c1, d = s2.c2;
    s.l = s1.l;
    s.r = s2.r;
    s.dis = max(s1.dis, s2.dis);
    s.dis = max(s.dis, s1.r1 + s2.l2, s1.r2 + s2.l1);
    if (b < c)
        s.c1 = a - b + c, s.c2 = d;
    else
        s.c1 = a, s.c2 = b - c + d;
    s.r1 = max(s2.r1, s1.r1 - c + d, s1.r2 + c + d);
    s.r2 = max(s2.r2, s1.r2 + c - d);
    s.l1 = max(s1.l1, s2.l1 - b + a, s2.l2 + b + a);
    s.l2 = max(s1.l2, s2.l2 + b - a);
    return s;
}
inline void dfs(int x, int fa) {
    v[++tot] = -6;
    v[++tot] = x;
    pos[x] = tot;
    for (int i = last[x]; i; i = e[i].next)
        if (e[i].to != fa) dfs(e[i].to, x);
    v[++tot] = -9;
}
inline void build(int k, int l, int r) {
    if (l == r) {
        t[k].l = l;
        t[k].r = r;
        t[k].ini(l);
        return;
    }
    int mid = (l + r) >> 1;
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
    t[k] = query(t[k << 1], t[k << 1 | 1]);
}
inline void modify(int k, int x) {
    int l = t[k].l, r = t[k].r;
    if (l == r) {
        t[k].ini(l);
        return;
    }
    int mid = (l + r) >> 1;
    if (x <= mid)
        modify(k << 1, x);
    else
        modify(k << 1 | 1, x);
    t[k] = query(t[k << 1], t[k << 1 | 1]);
}