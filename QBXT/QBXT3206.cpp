#include <bits/stdc++.h>

using int64 = long long;

const int P = 998244353;
const int F = P - 1;
const int I2 = (P + 1) / 2;
const int R2 = P - I2;

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

inline int Inv(int x) { return Pow(x, P - 2); }

inline void Gauss(std::vector<std::vector<int> > &a) {
    size_t N = a.size(), M = a.front().size();
    assert(N <= M);
    for (size_t i = 0; i < N; ++i) {
        if (a[i][i] == 0) {
            for (size_t j = i + 1; j < N; ++j) {
                if (a[j][i] == 0) continue;
                for (size_t k = 0; k < M; ++k) std::swap(a[i][k], a[j][k]);
                break;
            }
        }
        int x = Inv(a[i][i]);
        for (size_t j = i; j < M; ++j) Muls(a[i][j], x);
        for (size_t j = 0; j < N; ++j) {
            if (i == j) continue;
            x = Inv(Sub(0, a[j][i]));
            for (size_t k = i; k < M; ++k) Adds(a[j][k], Mul(x, a[i][k]));
        }
    }
}

struct FWTO {
    int c00, c01, c10, c11;
    inline FWTO() {}
    inline FWTO(int f00, int f01, int f10, int f11)
        : c00(f00), c01(f01), c10(f10), c11(f11) {}
};

struct FWTOper {
    FWTO O, I;
    inline FWTOper() {}
    inline FWTOper(int f00, int f01, int f10, int f11) : O(f00, f01, f10, f11) {
        std::vector<std::vector<int> > a = {{f00, f10, 1}, {f01, f11, 0}};
        std::vector<std::vector<int> > b = {{f00, f10, 0}, {f01, f11, 1}};
        Gauss(a), Gauss(b);
        I = FWTO(a[0][2], a[1][2], b[0][2], b[1][2]);
    }
};

const FWTOper Or(1, 0, 1, 1), And(1, 1, 0, 1), Xor(1, F, 1, 1);

inline std::vector<int> FWT(std::vector<int> f, FWTO Oper) {
    int n = f.size(), e = 1;
    while (e < n) e <<= 1;
    f.resize(n = e);
    for (int i = 1; i < n; i <<= 1) {
        for (int j = 0; j < n; j += i << 1) {
            for (int k = 0; k < i; ++k) {
                int a0 = f[j | k], a1 = f[j | i | k];
                f[j | k] = Add(Mul(Oper.c00, a0), Mul(Oper.c01, a1));
                f[j | i | k] = Add(Mul(Oper.c10, a0), Mul(Oper.c11, a1));
            }
        }
    }
    return f;
}

inline std::vector<int> FWT(std::vector<int> f, FWTOper Oper) {
    return FWT(f, Oper.O);
}

inline std::vector<int> IFWT(std::vector<int> f, FWTOper Oper) {
    return FWT(f, Oper.I);
}

inline std::vector<int> Mul(std::vector<int> f, std::vector<int> g) {
    assert(f.size() == g.size());
    int n = f.size();
    std::vector<int> Ret(n);
    for (int i = 0; i < n; ++i) Ret[i] = Mul(f[i], g[i]);
    return Ret;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    int n, m;
    std::cin >> n, m = 1 << n;
    std::vector<int> a(m), b(m), c;
    for (int i = 0; i < m; ++i) std::cin >> a[i];
    for (int i = 0; i < m; ++i) std::cin >> b[i];
    auto Get = [&](FWTOper Oper) {
        return IFWT(Mul(FWT(a, Oper), FWT(b, Oper)), Oper);
    };
    for (int x : Get(Or)) std::cout << x << ' ';
    std::cout << std::endl;
    for (int x : Get(And)) std::cout << x << ' ';
    std::cout << std::endl;
    for (int x : Get(Xor)) std::cout << x << ' ';
    std::cout << std::endl;
    return 0;
}