#include <bits/stdc++.h>

using int64 = long long;

const int N = 100005;
const int M = 1000005;


int64 ans, n, m, d;
int64 ans1[M], ans2[M], s[N], r[N];

inline void Solve(int e, int64 *ans) {
    if (!e) return;
    int64 sum = s[0], Left = e - 1, Now;
    for (int i = 0; i < m; ++i) {
        Now = std::min(Left, r[i + 1] / d - r[i] / d);
        Left -= Now, sum += Now * s[i];
    }
    for (int i = 1; i <= m; ++i) {
        if (e * d <= r[i]) break;
        ans[r[i] % d + 1] += s[i] - s[i - 1];
    }
    for (int i = 1; i <= d; ++i) ans[i] += ans[i - 1];
    for (int i = 0; i <= d; ++i) ans[i] += sum;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> m >> d;
    for (int i = 0; i <= m; ++i) std::cin >> r[i];
    for (int i = 0; i < m; ++i) std::cin >> s[i];
    Solve(n / 2, ans1), Solve(n - n / 2, ans2);
    for (int i = 0; i <= d; ++i) {
        ans = std::max(ans, ans1[i] + ans2[d - i]);
    }
    std::cout << ans << std::endl;
    return 0;
}
