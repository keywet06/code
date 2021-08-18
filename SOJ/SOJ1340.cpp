#include <bits/stdc++.h>

const int N = 200005;

int n, k, m, x, c, p;
int co[N], next[N], head[N], lit[N];

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> k >> m;
    for (int i = 1; i <= n; ++i) {
        std::cin >> co[i];
        next[i] = head[co[i]];
        head[co[i]] = i;
    }
    for (int i = 1; i <= m; ++i) {
        std::cin >> x, c = lit[head[x]];
        for (int u = head[x]; u; u = next[u]) {
            lit[u] = !c;
            if (lit[u - 1] != lit[u + 1]) continue;
            p += (c ? -1 : 1) * (lit[u - 1] ? -1 : 1);
        }
        std::cout << p << std::endl;
    }
    return 0;
}