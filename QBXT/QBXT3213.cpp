#include <bits/stdc++.h>

using int32 = int;
using int64 = long long;

inline int BiClz(int32 x) { return __builtin_clz(x); }
inline int BiCtz(int32 x) { return __builtin_ctz(x); }

inline int BiBlm(int32 x) { return 1 << 32 - BiClz(x - 1); }

const int P = 998244353;
const int F = P - 1;
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

inline std::ostream &operator<<(std::ostream &out, std::vector<int> A) {
    out << '[';
    for (int i = 0, x = 0; i < A.size(); ++i) {
        if (x) out << ", ";
        x = 1, out << A[i];
    }
    return out << ']';
}

inline std::vector<int> NTT(std::vector<int> f, bool Flag) {
    const int N = 1 << 23;
    static struct NTTBase {
        std::vector<int> Rev, W;
        NTTBase(int n) : Rev(n), W(n) {
            int c = BiCtz(n) - 1;
            for (int i = 1; i < n; ++i) {
                Rev[i] = Rev[i >> 1] >> 1 | (i & 1) << c;
            }
            int x = Pow(G, F >> c);
            W[n >> 1] = 1;
            for (int i = (n >> 1) + 1; i < n; ++i) W[i] = Mul(W[i - 1], x);
            for (int i = (n >> 1) - 1; i > 0; --i) W[i] = W[i << 1];
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
        for (int &u : f) Muls(u, x);
    }
    return f;
}

inline std::vector<int> NTT(std::vector<int> f) { return NTT(f, false); }
inline std::vector<int> INTT(std::vector<int> f) { return NTT(f, true); }

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
    A.resize(r), B.resize(r), A = NTT(A), B = NTT(B);
    for (int i = 0; i < r; ++i) Muls(A[i], B[i]);
    return (A = INTT(A)).resize(d), A;
}

inline std::vector<int> Sqr(std::vector<int> A) {
    for (int &u : A) Muls(u, u);
    return A;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::string ss, st;
    std::cin >> ss >> st;
    std::vector<int> s(ss.size()), t(st.size());
    char De = 'a' - 1;
    for (int i = 0; i < s.size(); ++i) s[i] = ss[i] - De;
    for (int i = 0; i < t.size(); ++i) t[i] = st[i] == '?' ? 0 : st[i] - De;
    std::reverse(t.begin(), t.end());
    int Sum = 0;
    for (int x : t) Adds(Sum, Mul(x, Mul(x, x)));
    std::vector<int> Num(s.size() + t.size() - 1, Sum);
    Num = Sub(Add(Num, Mul(Sqr(s), t)), Mul(2, Mul(s, Sqr(t))));
    std::vector<int> Ans;
    for (int i = 0; i <= s.size() - t.size(); ++i) {
        if (Num[t.size() - 1 + i] == 0) Ans.push_back(i);
    }
    std::cout << Ans.size() << '\n';
    for (int x : Ans) std::cout << x << '\n';
    return 0;
}