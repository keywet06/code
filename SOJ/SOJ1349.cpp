#include <bits/stdc++.h>

const int N = 300005;

int n, m, x, y, cnt;
int dfn[N], min[N], max[N], rmax[N], ans[N], ex[N], ey[N], fa[N], out[N];

std::vector<int> to[N];

inline void tarjan(int u, int f) {
    dfn[u] = min[u] = ++cnt, fa[u] = f;
    for (int v : to[u]) {
        if (v == f) continue;
        if (!dfn[v]) {
            tarjan(v, u), ++out[u];
            min[u] = std::min(min[u], min[v]);
            if (min[v] > max[u]) {
                rmax[u] = max[u], max[u] = min[v];
            } else if (min[v] > rmax[u]) {
                rmax[u] = min[v];
            }
        } else {
            min[u] = std::min(min[u], dfn[v]);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        std::cin >> x >> y, ex[i] = x, ey[i] = y;
        to[x].push_back(y);
        to[y].push_back(x);
    }
    tarjan(1, 1);
    for (int i = 1; i <= m; ++i) {
        if (dfn[ex[i]] > dfn[ey[i]]) std::swap(ex[i], ey[i]);
        if (fa[ey[i]] != ex[i]) {
            std::cout << int(
                !(max[ex[i]] < dfn[ex[i]] && max[ey[i]] < dfn[ey[i]] ||
                  ex[i] == 1 && out[1] <= 1 && !out[ey[i]]));
        } else {
            std::cout << int(
                !(max[ey[i]] < dfn[ex[i]] &&
                      (max[ex[i]] == min[ey[i]] ? rmax : max)[ex[i]] <
                          dfn[ex[i]] ||
                  ex[i] == 1 && (out[1] == 2 && !out[ey[i]] || out[1] == 1)));
        }
    }
    std::cout << std::endl;
    return 0;
}