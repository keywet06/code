#include <bits/stdc++.h>

using int64 = long long;
using int128 = __int128;

const int C = 64;

template <typename Type>
inline std::vector<Type> Vector(int x) {
    return std::vector<Type>(x);
}

template <typename Type, typename... Args>
inline auto Vector(int x, Args... args) {
    return std::vector<decltype(Vector<Type>(args...))>(x,
                                                        Vector<Type>(args...));
}

inline std::ostream &operator<<(std::ostream &out, int128 x) {
    std::stack<char> S;
    if (!x) S.push('0');
    while (x) S.push(x % 10 + '0'), x /= 10;
    while (!S.empty()) out << S.top(), S.pop();
    return out;
}

int main() {
    int64 l, r, V, a, b, c, d;
    std::cin >> l >> r >> V;
    int128 Ans = 0;
    auto Get0 = [&](int64 l, int64 r) -> int64 {
        return l <= r ? (r + 1 >> 2) - (l >> 2) : 0;
    };
    auto Get1 = [&](int64 l, int64 r) -> int64 {
        return l <= r ? (r + 3 >> 2) - (l + 2 >> 2) : 0;
    };
    auto Can = [&](int64 x) -> int64 {
        return (x & 3) == 0 ? x : ((x & 3) == 3 ? x - 1 : 0);
    };
    auto E = [&](int64 x, int i, int c = 1) -> bool {
        return ((x >> i) & 1) == c;
    };
    auto Get = [&](int64 r1, int64 r2, bool Flag) -> int128 {
        if (r1 < 0 || r2 < 0) return 0;
        int128 Ret = 0;
        auto f = Vector<int128>(C, 2, 2, 2);
        f.back()[1][1][1] = 1;
        for (int i = C - 1, I = i - 1; i; --i, --I) {
            for (int a = 0; a < 2; ++a) {
                for (int b = 0; b < 2; ++b) {
                    for (int c = 0; c < 2; ++c) {
                        int128 u = f[i][a][b][c];
                        int X = a ? E(r1, I) : 1;
                        for (int x = 0; x <= X; ++x) {
                            int y = E(V, I) ^ x;
                            if (b && y > E(r2, I)) continue;
                            if (c && y > x) continue;
                            f[I][a && E(r1, I, x)][b && E(r2, I, y)]
                             [c && x == y] += u;
                        }
                    }
                }
            }
        }
        for (int a = 0; a < 2; ++a) {
            for (int b = 0; b < 2; ++b) Ret += f[0][a][b][0];
        }
        if (Flag) {
            for (int a = 0; a < 2; ++a) {
                for (int b = 0; b < 2; ++b) Ret += f[0][a][b][1];
            }
        }
        return Ret;
    };
    auto Q = [&](int64 x, int y) -> int64 { return x - y >> 2; };
    if (V == 0) {
        a = Get0(l - 1, r) + (l == 1);
        Ans += int128(a) * (a - 1) / 2;
        a = Get1(l - 1, r);
        Ans += int128(a) * (a - 1) / 2;
    } else if (V == 1) {
        if (l == 1) Ans += Get1(l, r);
        a = Get0(0, l - 1) << 2 | 3;
        b = Get0(0, r) - 1 << 2 | 3;
        a = Get1(l - 1, a), b = Get1(l - 1, b);
        Ans += int128(a + b) * (b - a + 1) / 2;
        a = Get1(0, l - 1) << 2 | 1;
        b = Get1(0, r) - 1 << 2 | 1;
        a = Get0(l - 1, a), b = Get0(l - 1, b);
        Ans += int128(a + b) * (b - a + 1) / 2;
    } else {
        if (a = Can(V)) {
            if (a >= l && a <= r) Ans += Get0(l - 1, a - 1) + (l == 1);
            if (a >= l - 1 && a < r) Ans += Get0(a + 1, r);
        }
        if (a = Can(V ^ 1)) {
            if (a >= l && a <= r) Ans += Get1(l - 1, a - 1);
            if (a >= l - 1 && a < r) Ans += Get1(a + 1, r);
        }
        if ((V & 3) == 0) {
            V >>= 2;
            a = Q(r, 1), b = Q(l - 1, 1), c = Q(r - 1, 1), d = Q(l - 2, 1);
            Ans += Get(a, c, false) - Get(a, d, false) - Get(b, c, false) +
                   Get(b, d, false);
            a = Q(r, 3), b = Q(l - 1, 3), c = Q(r - 1, 3), d = Q(l - 2, 3);
            Ans += Get(a, c, false) - Get(a, d, false) - Get(b, c, false) +
                   Get(b, d, false);
        } else if ((V & 3) == 3) {
            V >>= 2;
            a = Q(r, 1), b = Q(l - 1, 1), c = Q(r - 1, 3), d = Q(l - 2, 3);
            Ans += Get(a, c, true) - Get(a, d, true) - Get(b, c, true) +
                   Get(b, d, true);
            a = Q(r, 3), b = Q(l - 1, 3), c = Q(r - 1, 1), d = Q(l - 2, 1);
            Ans += Get(a, c, false) - Get(a, d, false) - Get(b, c, false) +
                   Get(b, d, false);
        }
    }
    std::cout << Ans << std::endl;
    return 0;
}