#include <bits/stdc++.h>

using int64 = long long;

const int P = 998244353;

inline int Add(int x, int y) { return (x += y) >= P ? x - P : x; }
inline int Sub(int x, int y) { return (x -= y) < 0 ? x + P : x; }
inline int Mul(int x, int y) { return int64(x) * y % P; }
inline int &Adds(int &x, int y) { return (x += y) >= P ? (x -= P) : x; }
inline int &Subs(int &x, int y) { return (x -= y) < 0 ? (x += P) : x; }
inline int &Muls(int &x, int y) { return x = int64(x) * y % P; }

inline int Pow(int Base, int Exp) {
    int Ret(1);
    while (Exp) {
        if (Exp & 1) Muls(Ret, Base);
        Muls(Base, Base), Exp >>= 1;
    }
    return Ret;
}

inline int BCtz(int x) { return __builtin_ctz(x); }

const int N = 8388608;
const int G = 3;

int w[N];

struct Init {
    inline Init() {
        int x = Pow(G, P - 1 >> BCtz(N) - 1);
        w[N >> 1] = 1;
        for (int i = N >> 1 | 1; i < N; ++i) w[i] = Mul(w[i - 1], x);
        for (int i = (N >> 1) - 1; i; --i) w[i] = w[i << 1];
    }
} _Init;

inline std::vector<int> NTT(std::vector<int> f, bool Flag = false) {
    int n = f.size(), c = BCtz(n);
    std::vector<int> Rev(n);
    for (int i = 1; i < n; ++i) {
        Rev[i] = (Rev[i >> 1] >> 1) | ((i & 1) << c - 1);
        if (Rev[i] > i) std::swap(f[i], f[Rev[i]]);
    }
    for (int i = 1; i < n; i <<= 1) {
        for (int j = 0; j < n; j += i << 1) {
            for (int k = 0; k < i; ++k) {
                int x = f[j | k], y = Mul(f[j | i | k], w[i << 1 | k]);
                f[j | k] = Add(x, y);
                f[j | i | k] = Sub(x, y);
            }
        }
    }
    if (Flag) {
        std::reverse(f.begin() + 1, f.end());
        int x = Pow(n, P - 2);
        for (int i = 0; i < n; ++i) Muls(f[i], x);
    }
    return f;
}

inline std::vector<int> INTT(std::vector<int> f) { return NTT(f, true); }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    int d = n + m + 1, e = 1;
    while (e < d) e <<= 1;
    std::vector<int> a(e), b(e);
    for (int i = 0; i <= n; ++i) std::cin >> a[i];
    for (int i = 0; i <= m; ++i) std::cin >> b[i];
    std::vector<int> na(NTT(a)), nb(NTT(b));
    std::vector<int> nc(e);
    for (int i = 0; i < e; ++i) nc[i] = Mul(na[i], nb[i]);
    std::vector<int> c(INTT(nc));
    for (int i = 0; i < d; ++i) {
        int L = 0, R = std::min(i + 1, d - i) * 10000;
        if (c[i] + P > R) continue;
        for (int j = std::max(0, i - m); j <= i && j <= n; ++j) {
            R += a[j] * b[i - j] - 10000;
            L += a[j] * b[i - j];
            if (L > c[i]) {
                c[i] += P;
                break;
            } else if (R < P + c[i]) {
                break;
            }
        }
    }
    for (int i = 0; i < d; ++i) std::cout << c[i] << " \n"[i == d - 1];
    return 0;
}