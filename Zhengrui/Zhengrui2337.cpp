#include <bits/stdc++.h>

using int64 = long long;

const int N = 1000005;

int n;

int64 a[N], s[N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    std::sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + a[i];
    int Ans = 0, r = 1;
    for (int i = 1; i <= n; ++i) {
        while (r <= n && s[r] < a[i] * r) ++r;
        Ans = std::max(Ans, r - i);
    }
    std::cout << Ans << '\n';
    return 0;
}