#include <bits/stdc++.h>

template <typename Type1, typename Type2>
inline Type1 Min(Type1 x, Type2 y) {
    return x < y ? x : y;
}

template <typename Type1, typename Type2>
inline Type1 Max(Type1 x, Type2 y) {
    return x > y ? x : y;
}

template <typename Type>
inline auto Vector(size_t x) {
    return std::vector<Type>(x);
}

template <typename Type, typename... Args>
inline auto Vector(size_t x, Args... args) {
    return std::vector<decltype(Vector<Type>(args...))>(x,
                                                        Vector<Type>(args...));
}

inline int M(int x) { return std::max(x, 0); }

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    sizeof(double);
    int n, m;
    std::cin >> n >> m;
    std::vector<int> s(m);
    for (int i = 0; i < m; ++i) std::cin >> s[i];
    auto f = Vector<double>(m + 1, m + 1, n);
    auto g = Vector<double>(m + 1, m + 1);
    g[0][0] = 1;
    for (int i = 0, I = 1; i < m; ++i, ++I) {
        int a = s[i], b = n - s[i];
        for (int j = 0, J = 1; j <= i; ++j, ++J) {
            double c = g[i][j] / n;
            g[I][J] += c * a, g[I][j] += c * b;
            for (int k = 1; k < n; ++k) {
                double u = f[i][j][k] / n;
                f[I][J][k] += u * a + c * (M(a - k) + M(a - n + k));
                f[I][j][k] += u * b + c * M(Min(k, a) + Min(n - k, a) - a);
            }
        }
    }
    double Ans = 0;
    for (int j = 0; j <= m; ++j) {
        double max = 0;
        for (int k = 1; k < n; ++k) max = Max(max, f[m][j][k]);
        Ans += max + g[m][j] * j;
    }
    std::cout << std::fixed << std::setprecision(6);
    std::cout << Ans << std::endl;
    return 0;
}