#include <bits/stdc++.h>

const int N = 25;
const int K = N * N;
const int M = 1 << N;

int n, m, x, y;
int a[N];
int e[K];
int r[M];

inline void dfs(int c, int x, int v) {
    if (c == n) return void(++e[v]);
    dfs(c + 1, x, v);
    dfs(c + 1, x | 1 << c, v + r[x & a[c]]);
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 1; i < 1 << n; ++i) r[i] = r[i & (i - 1)] + 1;
    for (int i = 1; i <= m; ++i) {
        std::cin >> x >> y;
        if (--x < --y) std::swap(x, y);
        a[x] |= 1 << y;
    }
    dfs(0, 0, 0);
    for (int i = 0; i <= m; ++i) std::cout << e[i] << " \n"[i == m];
    return 0;
}