#include <bits/stdc++.h>

const int N = 1005;

int n, m;
int a[N], s[N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    while (m--) {
        int l, r;
        std::cin >> l >> r;
        for (int i = l; i <= r; ++i) ++s[a[i]];
        for (int i = 1; i <= r - l + 1; ++i) s[i] += s[i - 1];
        int Ans = r - l + 1;
        while (Ans && s[Ans - 1] < Ans) --Ans;
        for (int i = r - l + 1; i; --i) s[i] -= s[i - 1];
        for (int i = l; i <= r; ++i) --s[a[i]];
        std::cout << Ans << '\n';
    }
    return 0;
}