#include <bits/stdc++.h>

const int N = 100005;

int n;
int a[N];

namespace Subtask1 {

const int N = 15;
const int N_ = 10;

int ans;
int c[N], v[N], d[N], p[N];

inline void dfs(int u, int s) {
    if (s >= ans) return;
    if (u > n) {
        ans = s;
        for (int i = 1; i <= n; ++i) d[i] = c[i];
        return;
    }
    for (int i = 1; i <= n; ++i) {
        if (v[i] || u > 1 && !((c[u - 1] + i) & 1)) continue;
        v[i] = 1, c[u] = p[a[i]], dfs(u + 1, s + std::abs(u - p[i])), v[i] = 0;
    }
}

int main() {
    ans = 1000000000;
    for (int i = 1; i <= n; ++i) p[i] = i;
    std::sort(p + 1, p + n + 1, [](int x, int y) { return a[x] < a[y]; });
    dfs(1, 0);
    for (int i = 1; i <= n; ++i) std::cout << d[i] << ' ';
    std::cout << std::endl;
    return 0;
}

}  // namespace Subtask1

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    if (n <= Subtask1::N_) return Subtask1::main();

    return 0;
}