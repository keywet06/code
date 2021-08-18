#include <bits/stdc++.h>

using int64 = long long;

const int64 P = 998244353;
const int N = 100005;

int n;

int64 px[N], py[N], ans[N];

inline int64 sqr(int64 x) { return x * x; }

inline int64 dis(int x, int y) {
    return (sqr(px[x] - px[y]) + sqr(py[x] - py[y])) % P;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> px[i] >> py[i], ans[i] = 1;
    for (int i = 1; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            ans[i] = ans[i] * dis(i, j) % P;
            ans[j] = ans[j] * dis(i, j) % P;
        }
    }
    for (int i = 1; i <= n; ++i) {
        std::cout << ans[i] << '\n';
    }
    return 0;
}