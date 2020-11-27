#include <bits/stdc++.h>

using int64 = long long;

namespace oct {

void ios() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
}

}  // namespace oct

const int N = 1000005;

struct edge {
    int v, nt;
};

int n, ecnt;
int hd[N];

int64 f[N][2];

edge e[N];

void insert(int x, int y) {
    e[++ecnt] = (edge){y, hd[x]};
    hd[x] = ecnt;
}

void dfs(int x, int d) {
    for (int i = hd[x], y = e[i].v; i; i = e[i].nt, y = e[i].v) {
        dfs(y, d + 1);
        int64 p0 = f[x][0], p1 = f[x][1];
        f[x][0] = std::min(p0 + f[y][0] + 1 + d,
                           std::min(p1 + 1 + f[y][0], f[y][1] + 2 + p0));
        f[x][1] = std::min(p1 + f[y][1] + 2,
                           std::min(p1 + 1 + f[y][0], f[y][1] + 2 + p0) + d);
    }
}

int main() {
    oct::ios();
    std::cin >> n;
    for (int i = 2, fa; i <= n; ++i) std::cin >> fa, insert(fa, i);
    dfs(1, 0);
    std::cout << f[1][0] << std::endl;
    return 0;
}