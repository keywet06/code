#include <bits/stdc++.h>
const int C = 4;
const int N = 5005;
int n, m, x, y, flag, max, cnt;
int p[N], v[N];
int a[N][C];
std::vector<int> to[N];
void pre(int u) {
    p[++cnt] = u, v[u] = cnt;
    for (int i = 0; i < to[u].size(); ++i) if (!v[to[u][i]]) pre(to[u][i]);
}
void dfs(int u, int c) {
    if (u > max) {
        max = u;
        std::cerr << max << '\t' << p[u] << std::endl;
    }
    a[p[u]][0] = c;
    if (u == n) {
        for (int i = 1; i <= n; ++i) {
            std::cout << a[i][0] << ' ';
        }
        std::cout << '\n';
        flag = 1;
        return;
    }
    for (int i = 0; i < to[p[u]].size(); ++i) ++a[to[p[u]][i]][c];
    for (int s = 1; s <= 3; ++s) {
        if (!a[p[u + 1]][s]) dfs(u + 1, s);
        if (flag) return;
    }
    for (int i = 0; i < to[p[u]].size(); ++i) --a[to[p[u]][i]][c];
}
int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        std::cin >> x >> y;
        to[x].push_back(y);
        to[y].push_back(x);
    }
    pre(1);
    std::cerr << "pre is end" << std::endl;
    dfs(1, 1);
    return 0;
}