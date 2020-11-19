#include <bits/stdc++.h>

const int B = 2;
const int C = 32;
const int N = 100005;
const int Z = 4000005;

int cnt, n, u, v, w, t, ans, now, s;
int val[N];
int son[Z][B];

std::vector<std::pair<int, int> > to[N];

inline void insert(int x) {
    for (int i = C - 1, now = 0; ~i; --i) {
        now = son[now][t = x >> i & 1] ? son[now][t] : (son[now][t] = ++cnt);
    }
}

inline void dfs(int u, int f, int x) {
    insert(val[u] = x);
    for (std::pair<int, int> v : to[u]) {
        if (v.first == f) continue;
        dfs(v.first, u, x ^ v.second);
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i < n; ++i) {
        std::cin >> u >> v >> w;
        to[u].push_back(std::make_pair(v, w));
        to[v].push_back(std::make_pair(u, w));
    }
    dfs(1, 1, 0);
    for (int i = 1; i <= n; ++i) {
        s = now = 0;
        for (int j = C - 1; ~j; --j) {
            if (son[now][t = !(val[i] >> j & 1)]) {
                s |= 1 << j, now = son[now][t];
            } else {
                now = son[now][!t];
            }
        }
        ans = std::max(ans, s);
    }
    std::cout << ans << std::endl;
    return 0;
}