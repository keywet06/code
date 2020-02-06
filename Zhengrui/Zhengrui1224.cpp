#include <bits/stdc++.h>
const int N = 150;
const int Np = N + 5;
const int M = 18;
int ans, n, m;
int f[Np], a[Np], b[Np], s[Np], t[Np], ct[Np], V[Np], e[Np], p[Np];
std::vector<int> hv[Np];
void dfs(int u, int v) {
    if (u == m + 1) {
        for (int i = 2; i <= n; ++i) {
            v -= a[i] * ct[i] * ct[i] + b[i] * ct[i];
        }
        ans = std::max(ans, v);
        return;
    }
    dfs(u + 1, v);
    for (int i = t[u]; i != s[u]; i = f[i]) {
        ++ct[i];
    }
    dfs(u + 1, v + V[u]);
    for (int i = t[u]; i != s[u]; i = f[i]) {
        --ct[i];
    }
}
int cmp(int x, int y) { return V[x] > V[y]; }
int main() {
    std::cin >> n >> m;
    for (int i = 2; i <= n; ++i) {
        std::cin >> f[i] >> a[i] >> b[i];
    }
    for (int i = 1; i <= m; ++i) {
        std::cin >> s[i] >> t[i] >> V[i];
    }
    if (m <= 18) {
        dfs(1, 0);
        std::cout << ans << std::endl;
    } else {
        for (int i = 1; i <= m; ++i) {
            for (int j = t[i]; j != s[i]; j = f[j]) {
                V[i] -= a[j] + b[j];
                hv[j].push_back(i);
            }
            p[i] = i;
        }
        std::sort(p + 1, p + m + 1, cmp);
        while (m) {
            if (V[p[1]] <= 0) {
                break;
            }
            ans += V[p[1]];
            for (int i = t[p[1]]; i != s[p[1]]; i = f[i]) {
                ++ct[i];
                for (auto &&j: hv[i]) {
                    V[j] -= (2 * ct[i] + 1) * a[i];
                }
            }
            for (int i = 1; i < m; ++i) {
                p[i] = p[i + 1];
            }
            --m;
            std::sort(p + 1, p + m + 1, cmp);
        }
        std::cout << ans << std::endl;
    }
    return 0;
}