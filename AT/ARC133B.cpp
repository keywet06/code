#include <bits/stdc++.h>

template <typename Type1, typename Type2>
inline Type1 &Mad(Type1 &x, Type2 y) {
    return x > y ? x : (x = y);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> a(n + 1), b(n + 1), rb(n + 1);
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    for (int i = 1; i <= n; ++i) std::cin >> b[i], rb[b[i]] = i;
    std::vector<int> f(n + 1);
    auto Pre = [&](int x) -> int {
        int Ret(0);
        while (x) Mad(Ret, f[x]), x &= x - 1;
        return Ret;
    };
    auto Mod = [&](int x, int y) -> void {
        while (x <= n) Mad(f[x], y), x += x & -x;
    };
    for (int i = 1; i <= n; ++i) {
        int R = n / a[i];
        std::vector<int> t(R + 1);
        for (int j = 1; j <= R; ++j) t[j] = Pre(rb[a[i] * j] - 1) + 1;
        for (int j = 1; j <= R; ++j) Mod(rb[a[i] * j], t[j]);
    }
    std::cout << Pre(n) << std::endl;
    return 0;
}