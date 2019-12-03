#include <bits/stdc++.h>
const int N = 250005;
int cnt, tmp, m, n;
int a[N], next[N], to[N], head[N], l[N], r[N];
std::string s;
int read();
void insert(int, int);
void getdfn(int);
void plus(int, int);
int ans(int);
int lowbit(int);
int main() {
    n = read();
    for (int i = 1; i < n; ++i) {
        insert(read(), read());
    }
    cnt = 0;
    getdfn(1);
    for (int i = 2; i <= n; ++i) {
        plus(l[i], 1);
        plus(r[i] + 1, -1);
    }
    m = read();
    for (int i = 1; i < n + m; ++i) {
        std::cin >> s;
        if (s == (std::string) "W") {
            printf("%d\n", ans(l[read()]));
        } else {
            read();
            tmp = read();
            plus(l[tmp], -1);
            plus(r[tmp] + 1, 1);
        }
    }
    return 0;
}
inline int read() {
    int x = 0, ch = getchar(), val = 1;
    while (ch < '0' || '9' < ch) {
        val = ((ch != '-') << 1) - 1;
        ch = getchar();
    }
    while ('0' <= ch && ch <= '9') {
        x = (x << 1) + (x << 3) + (ch ^ '0');
        ch = getchar();
    }
    return x * val;
}
inline void insert(int x, int y) {
    if (x > y) {
        std::swap(x, y);
    }
    next[++cnt] = head[x];
    head[x] = cnt;
    to[cnt] = y;
}
inline void getdfn(int u) {
    l[u] = ++cnt;
    for (int v = head[u]; v; v = next[v]) {
        getdfn(to[v]);
    }
    r[u] = cnt;
}
inline void plus(int x, int y) {
    while (x <= cnt) {
        a[x] += y;
        x += lowbit(x);
    }
}
inline int ans(int x) {
    int sum = 0;
    while (x) {
        sum += a[x];
        x -= lowbit(x);
    }
    return sum;
}
inline int lowbit(int x) { return x & (-x); }