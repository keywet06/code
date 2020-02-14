#include <bits/stdc++.h>
const int N = 300000;
const int Np = N + 5;
unsigned int ans, n, Q, x, y;
unsigned int w[Np], sum[Np], size[Np], fa[Np], son1[Np], son2[Np];
std::vector<unsigned int> gi1[Np], gi2[Np];
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> Q;
    for (int i = 2; i <= n; ++i) {
        std::cin >> fa[i];
        ++son1[i];
        ++son2[i];
        gi1[fa[i]].push_back(i);
        gi2[fa[fa[i]]].push_back(i);
        ++son1[fa[i]];
        ++son2[fa[i]];
        ++son2[fa[fa[i]]];
    }
    for (int i = 1; i <= n; ++i) {
        std::cin >> w[i];
        sum[i] = w[i];
    }
    for (int i = n; i; --i) {
        size[fa[i]] += ++size[i];
        sum[fa[i]] += sum[i];
    }
    for (int i = 1; i <= Q; ++i) {
        std::cin >> x;
        if (x == 1) {
            std::cin >> x >> y;
            for (auto u: gi2[x]) {
                sum[u] += y;
                w[u] += y;
            }
            for (auto u: gi1[x]) {
                sum[u] += y * son1[u];
                w[u] += y;
            }
            sum[x] += y * son2[x];
            w[x] += y;
            for (auto u = fa[x]; u; u = fa[u]) {
                sum[u] += y * son2[x];
            }
        } else {
            std::cin >> x;
            ans = w[x] * size[x] + sum[x];
            for (auto u: gi1[x]) {
                ans += sum[u] * (size[x] - size[u] - 1);
            }
            std::cout << ans << std::endl;
        }
    }
    return 0;
}