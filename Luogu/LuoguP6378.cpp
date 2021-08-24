#include <bits/stdc++.h>
#define p1(x) x
#define p0(x) x + n
#define pre1(x) x + 2 * n
#define pre0(x) x + 3 * n
#define maxn 8000010
using namespace std;
template <typename T>
inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool flag = false;
    while (!isdigit(c)) {
        if (c == '-') flag = true;
        c = getchar();
    }
    while (isdigit(c)) {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    if (flag) x = -x;
}
int n, m, k, dfn_cnt, co_cnt, top;
int dfn[maxn], low[maxn], co[maxn], st[maxn], a[maxn];
bool vis[maxn];
struct edge {
    int to, nxt;
} e[maxn];
int head[maxn], edge_cnt;
void add(int from, int to) {
    e[++edge_cnt] = (edge){to, head[from]};
    head[from] = edge_cnt;
}
void tarjan(int x) {
    dfn[x] = low[x] = ++dfn_cnt;
    st[++top] = x, vis[x] = true;
    for (int i = head[x]; i; i = e[i].nxt) {
        int y = e[i].to;
        if (!dfn[y])
            tarjan(y), low[x] = min(low[x], low[y]);
        else if (vis[y])
            low[x] = min(low[x], dfn[y]);
    }
    if (low[x] == dfn[x]) {
        co_cnt++;
        int now;
        do {
            now = st[top--];
            vis[now] = false;
            co[now] = co_cnt;
        } while (now != x);
    }
}
bool check() {
    for (int i = 1; i <= 4 * n; ++i)
        if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= n; ++i)
        if (co[p1(i)] == co[p0(i)] || co[pre1(i)] == co[pre0(i)]) return false;
    return true;
}
int main() {
    read(n), read(m), read(k);
    for (int i = 1; i <= m; ++i) {
        int x, y;
        read(x), read(y);
        add(p0(x), p1(y)), add(p0(y), p1(x));
    }
    for (int i = 1; i <= k; ++i) {
        int w;
        read(w);
        for (int j = 1; j <= w; ++j)
            read(a[j]), add(p1(a[j]), pre1(a[j])), add(pre0(a[j]), p0(a[j]));
        for (int j = 2; j <= w; ++j) {
            add(pre1(a[j - 1]), pre1(a[j])), add(pre0(a[j]), pre0(a[j - 1]));
            add(pre1(a[j - 1]), p0(a[j])), add(p1(a[j]), pre0(a[j - 1]));
        }
    }
    if (check())
        puts("TAK");
    else
        puts("NIE");
    return 0;
}