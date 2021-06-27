#include <bits/stdc++.h>

const int N = 200005;
const int M = 400005;

int cnt, n, x, y;
int hx[N], hy[N], color[N], head[N];
int to[M], next[M];

void insert(int x, int y) {
    next[++cnt] = head[x];
    head[x] = cnt;
    to[cnt] = y;
}

void addedge(int x, int y) { insert(x, y), insert(y, x); }

void dfs(int u) {
    int v;
    for (int e = head[u]; e; e = next[e]) {
        if (color[v = to[e]]) continue;
        color[v] = 3 - color[u], dfs(v);
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> x >> y;
        if (hx[x]) addedge(hx[x], i);
        hx[x] = hx[x] ? 0 : i;
        if (hy[y]) addedge(hy[y], i);
        hy[y] = hy[y] ? 0 : i;
    }
    for (int i = 1; i <= n; ++i) {
        if (!color[i]) color[i] = 1, dfs(i);
    }
    for (int i = 1; i <= n; ++i) std::cout << (color[i] == 1 ? 'r' : 'b');
    std::cout << std::endl;
    return 0;
}