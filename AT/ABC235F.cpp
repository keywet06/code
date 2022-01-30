#include <bits/stdc++.h>

using int64 = long long;

const int P = 998244353;

inline int Add(int x, int y) { return (x += y) >= P ? x - P : x; }
inline int Sub(int x, int y) { return (x -= y) < 0 ? x + P : x; }
inline int Mul(int x, int y) { return int64(x) * y % P; }
inline int &Adds(int &x, int y) { return (x += y) >= P ? (x -= P) : x; }
inline int &Subs(int &x, int y) { return (x -= y) < 0 ? (x += P) : x; }
inline int &Muls(int &x, int y) { return x = int64(x) * y % P; }

template <typename... Args>
inline int Mul(int x, int y, Args... args) {
    return Mul(Mul(x, y), args...);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int m, x;
    std::string s;
    std::cin >> s >> m;
    int n = s.size(), d = n + 5;
    for (int i = 0; i < n; ++i) s[i] -= '0';
    std::vector<int> c(10);
    std::vector<int> p1(d), pm(d);
    p1[0] = pm[0] = 1;
    for (int i = 1; i < d; ++i) p1[i] = Mul(p1[i - 1], 10);
    for (int i = 1; i < d; ++i) pm[i] = Mul(pm[i - 1], m);
    for (int i = 0; i < m; ++i) std::cin >> x, c[x] = 1;
    std::vector<int> f(n);
    for (int i = n - 1; i >= 0; --i) {
        if (i != n - 1 && c[s[i]]) f[i] = f[i + 1];
        for (int j = 0; j < s[i]; ++j) {
            if (c[j]) Adds(f[i], pm[n - i - 1]);
        }
    }
    f.push_back(1);
    int Ans = 0, Sum = 0, Flag = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j < 10; ++j) {
            if (!c[j]) continue;
            Adds(Ans, Mul(Sum, j, pm[n - i - 1], p1[n - i - 1]));
            if (Flag && j == s[i]) Adds(Ans, Mul(j, f[i + 1], p1[n - i - 1]));
        }
        Muls(Sum, m);
        if (Flag) {
            for (int j = 0; j < s[i]; ++j) Adds(Sum, c[j]);
        }
        Flag &= c[s[i]];
    }
    std::cout << Ans << std::endl;
    return 0;
}