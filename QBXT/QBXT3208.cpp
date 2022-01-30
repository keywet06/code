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

inline int BiBlm(int32 x) { return 1 << 32 - BiClz(x - 1); }

const int P = 998244353;
const int G = 3;

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

inline std::vector<int> NTT(std::vector<int> f, bool Flag) {
    const int N = 1 << 23;
    static struct NTTBase {
        std::vector<int> Rev, W;
        NTTBase(int n) : Rev(n), W(n) {
            int c = BiCtz(n) - 1;
            for (int i = 1; i < n; ++i) {
                Rev[i] = Rev[i >> 1] >> 1 | (i & 1) << c;
            }
            int x = Pow(G, P - 1 >> c);
            W[n >> 1] = 1;
            for (int i = n >> 1 | 1; i < n; ++i) W[i] = Mul(W[i - 1], x);
            for (int i = (n >> 1) - 1; i >= 0; --i) W[i] = W[i << 1];
        }
    } Base(N);
    int n = BiBlm(f.size()), Shift = BiCtz(N) - BiCtz(n);
    f.resize(n);
    for (int i = 1, x; i < n; ++i) {
        if ((x = Base.Rev[i] >> Shift) > i) std::swap(f[x], f[i]);
    }
    for (int i = 1; i < n; i <<= 1) {
        for (int j = 0; j < n; j += i << 1) {
            for (int k = 0; k < i; ++k) {
                int x = f[j | k], y = Mul(Base.W[i << 1 | k], f[j | i | k]);
                f[j | k] = Add(x, y), f[j | i | k] = Sub(x, y);
            }
        }
    }
    if (Flag) {
        std::reverse(f.begin() + 1, f.end());
        int x = Inv(n);
        for (int i = 0; i < n; ++i) Muls(f[i], x);
    }
    return f;
}

inline std::vector<int> NTT(std::vector<int> f) { return NTT(f, false); }
inline std::vector<int> INTT(std::vector<int> f) { return NTT(f, true); }

inline std::ostream &operator<<(std::ostream &out, std::vector<int> A) {
    out << '[';
    for (int i = 0, x = 0; i < A.size(); ++i) {
        if (x) out << ", ";
        x = 1, out << A[i];
    }
    return out << ']';
}

inline std::vector<int> Resize(std::vector<int> A, size_t s) {
    return A.resize(s), A;
}

inline std::vector<int> Add(std::vector<int> A, std::vector<int> B) {
    int n = std::max(A.size(), B.size());
    A.resize(n), B.resize(n);
    for (int i = 0; i < n; ++i) Adds(A[i], B[i]);
    return A;
}

inline std::vector<int> Sub(std::vector<int> A, std::vector<int> B) {
    int n = std::max(A.size(), B.size());
    A.resize(n), B.resize(n);
    for (int i = 0; i < n; ++i) Subs(A[i], B[i]);
    return A;
}

inline std::vector<int> Mul(int x, std::vector<int> A) {
    for (int &u : A) Muls(u, x);
    return A;
}

inline std::vector<int> Mul(std::vector<int> A, std::vector<int> B) {
    int d = A.size() + B.size() - 1, r = BiBlm(d);
    A.resize(r), B.resize(r);
    A = NTT(A), B = NTT(B);
    for (int i = 0; i < r; ++i) Muls(A[i], B[i]);
    A = INTT(A), A.resize(d);
    return A;
}

inline std::vector<int> Inv(std::vector<int> f) {
    if (f.size() == 1) return f[0] = Inv(f[0]), f;
    int n = f.size(), m = n + 1 >> 1;
    std::vector<int> T(Inv(Resize(f, m)));
    return Resize(Sub(Mul(2, T), Mul(f, Mul(T, T))), n);
}

inline std::vector<int> Sqrt(std::vector<int> f) {
    if (f.size() == 1) return f[0] = 1, f;
    int n = f.size(), m = n + 1 >> 1;
    std::vector<int> T(Sqrt(Resize(f, m)));
    auto Tmp = Resize(Mul(Add(Mul(T, T), f), Inv(Resize(Mul(2, T), n))), n);
    return Tmp;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    int n;
    std::cin >> n;
    std::vector<int> A(n);
    for (int &x : A) std::cin >> x;
    for (int x : Sqrt(A)) std::cout << x << ' ';
    std::cout << std::endl;
    return 0;
}