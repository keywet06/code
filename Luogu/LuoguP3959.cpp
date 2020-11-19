#include <bits/stdc++.h>

namespace oct {

void ios();

inline void ios() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
}

}  // namespace oct

const int C = 20;

int ans = INT_MAX >> 4, tmp, cot, cnt, n, m, p;
int ry[C], rt[C], d[C];
int c[C][C], cr[C][C];

inline bool cmp(int a, int b) { return c[p][a] < c[p][b]; }

inline void dfs(int num, int node) {
    for (int i = num; i <= cnt; i++) {
        if (cot + tmp * rt[ry[i]] >= ans) return;
        for (int j = node; j <= d[ry[i]]; j++) {
            if (!rt[cr[ry[i]][j]]) {
                cnt++, ry[cnt] = cr[ry[i]][j];
                tmp -= c[ry[cnt]][cr[ry[cnt]][1]];
                cot += c[ry[i]][ry[cnt]] * rt[ry[i]];
                rt[ry[cnt]] = rt[ry[i]] + 1, dfs(i, j + 1);
                cot -= c[ry[i]][ry[cnt]] * rt[ry[i]];
                rt[ry[cnt]] = 0, tmp += c[ry[cnt]][cr[ry[cnt]][1]];
                cnt--;
            }
        }
        node = 1;
    }
    if (cnt == n) {
        if (cot < ans) ans = cot;
        return;
    }
}

int main() {
    int u, v, w;
    oct::ios();
    std::cin >> n >> m;
    memset(c, 100, sizeof(c));
    for (int i = 1; i <= m; i++) {
        std::cin >> u >> v >> w;
        if (c[u][v] < w) continue;
        if (c[u][v] == **c) cr[u][++d[u]] = v, cr[v][++d[v]] = u;
        c[u][v] = c[v][u] = w;
    }
    for (int i = 1; i <= n; i++) {
        p = i, std::sort(cr[i] + 1, cr[i] + 1 + d[i], cmp);
        tmp += c[i][cr[i][1]];
    }
    for (int i = 1; i <= n; i++) {
        cot = 0, cnt = 1, ry[1] = i, tmp -= c[i][cr[i][1]], rt[i] = 1;
        dfs(1, 1), rt[i] = 0, tmp += c[i][cr[i][1]];
    }
    std::cout << ans << std::endl;
    return 0;
}