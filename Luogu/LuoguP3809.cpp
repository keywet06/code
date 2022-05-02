#include <bits/stdc++.h>

using int32 = int;
using int64 = long long;

inline int BiFfs(int32 x) { return __builtin_ffs(x); }
inline int BiClz(int32 x) { return __builtin_clz(x); }
inline int BiCtz(int32 x) { return __builtin_ctz(x); }
inline int BiPop(int32 x) { return __builtin_popcount(x); }
inline int BiPar(int32 x) { return __builtin_parity(x); }
inline int BiFfs(int64 x) { return __builtin_ffsll(x); }
inline int BiClz(int64 x) { return __builtin_clzll(x); }
inline int BiCtz(int64 x) { return __builtin_ctzll(x); }
inline int BiPop(int64 x) { return __builtin_popcountll(x); }
inline int BiPar(int64 x) { return __builtin_parityll(x); }

inline std::vector<int> Inv(std::vector<int> f) {
    std::vector<int> g(f.size());
    for (int i = 0; i < f.size(); ++i) g[f[i]] = i;
    return g;
}

inline std::vector<int> SA(std::string s) {
    int n = s.size(), m = 32 - BiClz(n - 1);
    std::vector<int> f(n), g(n);
    int T = 0;
    [&]() {
        std::vector<int> Id(n);
        for (int i = 0; i < n; ++i) Id[i] = i;
        std::stable_sort(Id.begin(), Id.end(), [&](int x, int y) { return s[x] < s[y]; });
        f[Id[0]] = ++T;
        for (int i = 1; i < n; ++i) f[Id[i]] = T += s[Id[i]] != s[Id[i - 1]];
    }();
    std::vector<std::vector<int> > So1(T + 1), So2(T + 1);
    for (int i = 0, I = 1, c = 1; i < m; ++i, ++I, c <<= 1) {
        auto Sub = [&](int j) { return j + c < n ? f[j + c] : 0; };
        for (int j = 0; j < n; ++j) So1[Sub(j)].push_back(j);
        for (auto v : So1) {
            for (int x : v) So2[f[x]].push_back(x);
        }
        T = 0;
        for (auto v : So2) {
            for (int j = 0; j < v.size(); ++j) g[v[j]] = T += !j || Sub(v[j - 1]) != Sub(v[j]);
        }
        f.swap(g);
        So1.assign(T + 1, std::vector<int>()),So2.assign(T + 2, std::vector<int>());
    }
    for (int &x : f) --x;
    return f;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::string s;
    std::cin >> s;
    s.resize(30000);
    auto Ans = Inv(SA(s));
    for (auto x : Ans) std::cout << x + 1 << ' ';
    std::cout << std::endl;
    return 0;
}