#include <bits/stdc++.h>
inline int read() {
    int k = 1, re = 0;
    char ch = getchar();
    while (ch > '9' || ch < '0') {
        if (ch == '-') k = -1;
        ch = getchar();
    }
    while (ch <= '9' && ch >= '0') {
        re = re * 10 + ch - 48;
        ch = getchar();
    }
    return re * k;
}
inline void write(int x) {
    if (x < 0) return putchar('-'), write(-x), void();
    if (x <= 9) return putchar(x + 48), void();
    return write(x / 10), write(x % 10), void();
}
int T = 900;
std::priority_queue<int> q[505];
std::priority_queue<int, std::vector<int>, std::greater<int> > p[505];
int n, qq;
int a[400005], bl[400005], l[505], r[505];
void cleann(std::priority_queue<int> &q) {
    std::priority_queue<int> p;
    std::swap(p, q);
}
void pushdown(int x) {
    for (int i = l[x]; i <= r[x]; i++) {
        if (p[x].empty()) break;
        if (p[x].top() < a[i]) {
            int t = a[i];
            a[i] = p[x].top();
            p[x].pop();
            p[x].push(t);
        }
    }
    while (!p[x].empty()) p[x].pop();
}
int oracle(int x, int ll, int rr, int v) {
    pushdown(x);
    for (int i = ll; i <= rr; i++) {
        if (v < a[i]) std::swap(v, a[i]);
    }
    cleann(q[x]);
    for (int i = l[x]; i <= r[x]; i++) q[x].push(a[i]);
    return v;
}
int update(int ll, int rr, int v) {
    if (bl[ll] == bl[rr]) return oracle(bl[ll], ll, rr, v);
    v = oracle(bl[ll], ll, r[bl[ll]], v);
    for (int i = bl[ll] + 1; i < bl[rr]; i++) {
        if (q[i].top() > v) {
            int t = v;
            v = q[i].top();
            p[i].push(t);
            q[i].pop();
            q[i].push(t);
        }
    }
    v = oracle(bl[rr], l[bl[rr]], rr, v);
    return v;
}
signed main() {
    n = read();
    qq = read();
    int mx = 0;
    for (int i = 1; i <= n; i++) {
        a[i] = read();

        bl[i] = (i - 1) / T + 1;
        q[bl[i]].push(a[i]);
        if (i % T == 1) l[bl[i]] = i;
        if (i % T == 0) r[bl[i]] = i;
        mx = std::max(mx, bl[i]);
    }
    r[mx] = n;

    int u, v, w;
    for (int i = 1; i <= qq; i++) {
        u = read();
        v = read();
        w = read();
        if (u > v) {
            w = update(u, n, w);
            w = update(1, v, w);
        } else
            w = update(u, v, w);
        write(w);
        puts("");
    }
}