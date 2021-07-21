#include <bits/stdc++.h>

using dou = double;

const int N = 200005;

int n;

dou p;
dou x[N], y[N], ans[N];

inline dou sqr(dou x) { return x * x; }

inline dou dis(int a, int b) {
    return std::sqrt(sqr(x[a] - x[b]) + sqr(y[a] - y[b]));
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> x[i] >> y[i], ans[i] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            p = dis(i, j), ans[i] += p, ans[j] += p;
        }
    }
    std::cout << std::fixed << std::setprecision(4);
    for (int i = 1; i <= n; ++i) std::cout << ans[i] << '\n';
    return 0;
}