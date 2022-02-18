#include <bits/stdc++.h>

using int32 = int;
using int64 = long long;

inline int BiClz(int32 x) { return __builtin_clz(x); }

inline int BiBlm(int32 x) { return 1 << 32 - BiClz(x - 1); }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int n, m, d;
    std::cin >> n;
    std::vector<int> a(n), b, c;
    for (int i = 0; i < n; ++i) std::cin >> a[i], d = a[i] == 1 ? i : d;
    for (int i = d; i < n; ++i) b.push_back(a[i]);
    for (int i = 0; i < d; ++i) b.push_back(a[i]);
    for (int i = d; i >= 0; --i) c.push_back(a[i]);
    for (int i = n - 1; i > d; --i) c.push_back(a[i]);
    std::vector<std::pair<int, int> > Min(BiBlm(n) << 1);
    using BuildType = std::function<void(int, int, int)>;
    BuildType Build = [&](int u, int l, int r) {
        if (l == r) return void(Min[u] = std::make_pair(b[l], l));
        int Mid = l + r >> 1;
        Build(u << 1, l, Mid);
        Build(u << 1 | 1, Mid + 1, r);
        Min[u] = std::min(Min[u << 1], Min[u << 1 | 1]);
    };

    return 0;
}