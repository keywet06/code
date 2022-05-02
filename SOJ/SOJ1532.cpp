#include <bits/stdc++.h>

using int64 = long long;

const int N = 200005;

int64 a[N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    while (q--) {
        int Opt;
        std::cin >> Opt;
        if (Opt == 1) {
            int64 Ans = a[1] * n;
            for (int i = 2; i <= n; ++i) {
                Ans += a[i] > a[i - 1] ? (a[i] - a[i - 1]) * (i - 1) * (n - i + 1) : 0;
                Ans += a[i] * (n - i + 1);
            }
            std::cout << Ans << '\n';
        } else {
            int l, r, v;
            std::cin >> l >> r >> v;
            for (int i = l; i <= r; ++i) a[i] += (i - l + 1) * v;
        }
    }
    return 0;
}