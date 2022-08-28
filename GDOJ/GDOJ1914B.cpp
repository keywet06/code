#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

using int64 = long long;
using int128 = __int128;
using uint64 = unsigned long long;
using fuint64 = uint_fast64_t;

#ifndef OCT_POLLARD_RHO
#define OCT_POLLARD_RHO

inline int64 ChronoClock() { return std::chrono::system_clock::now().time_since_epoch().count(); }

inline std::mt19937_64 &RandMachine() {
    static std::mt19937_64 Ret(ChronoClock());
    return Ret;
}

inline std::mt19937_64 &SRand(const fuint64 Seed = ChronoClock()) { return RandMachine() = std::mt19937_64(Seed); }

inline fuint64 Random() { return RandMachine()(); }

template <typename Type>
inline Type Random(const Type n) {
    return Random() % n;
}

template <typename Type>
inline Type Random(Type l, Type r) {
    return Random(r - l) + l;
}

template <typename BType, typename EType, typename MType>
inline BType Pow(BType Base, EType Exp, MType Mod) {
    BType Ret(1);
    while (Exp) {
        if (Exp & 1) Ret = Ret * Base % Mod;
        Base = Base * Base % Mod, Exp >>= 1;
    }
    return Ret;
}

template <typename Type>
inline Type Gcd(Type x, Type y) {
    return y == Type(0) ? x : Gcd(y, x % y);
}

template <typename Type>
inline Type Abs(Type x) {
    return x > 0 ? x : -x;
}

const int MillerRabinTestElements[] = {2, 3, 5, 7, 11, 13, 82, 373};

template <typename Type>
inline bool MillerRabin(Type n) {
    if (n <= 2 || !(n & 1)) return n == 2;
    Type e = n - 1, u;
    size_t w = 0, i;
    while (!(e & 1)) ++w, e >>= 1;
    for (const int &t : MillerRabinTestElements) {
        if (!(t % n)) continue;
        u = Pow(Type(t), e, n);
        if (u == Type(1)) continue;
        for (i = 0; i < w; ++i) {
            if (u == Type(n - 1)) break;
            if (u == Type(1)) return false;
            u = u * u % n;
        }
        if (i == w) return false;
    }
    return true;
}

template <typename Type>
inline Type PollardRho(Type n) {
    Type x = Random(Type(1), n), c = Random(Type(1), n), y = x, p = 1, d;
    for (size_t k = 4; k <= 16384; k <<= 1) {
        for (size_t step = 0; step < k; ++step) {
            x = (x * x + c) % n;
            p = p * Abs(x - y) % n;
            if (!(step & 127)) {
                d = Gcd(p, n);
                if (d > 1) return d;
            }
        }
        d = Gcd(p, n), y = x, p = 1;
        if (d > 1) return d;
    }
    return 0;
}

template <typename Type, typename RetType = std::vector<Type> >
inline RetType &GetFac(Type n, RetType &Ret) {
    if (n <= 1) return Ret;
    if (MillerRabin(n)) return Ret.push_back(n), Ret;
    Type d = PollardRho(n);
    while (!d && d != n) d = PollardRho(n);
    return GetFac(d, Ret), GetFac(n / d, Ret);
}

template <typename Type, typename RetType = std::vector<Type> >
inline RetType GetFac(Type n) {
    RetType Ret;
    return GetFac(n, Ret);
}

#endif

#ifndef OCT_MODINT_HPP
#define OCT_MODINT_HPP

namespace Oct {

template <typename Type, Type P, typename MulType = Type>
class ModInt {
   protected:
    Type x;

   public:
    using Self = ModInt<Type, P, MulType>;
    ModInt() : x(0) {}
    ModInt(Type c) : x(c) {}
    explicit operator Type() { return x; }
    Type &Data() { return x; }
    friend Self operator+(Self a, Self b) { return (a.x += b.x) >= P ? a.x - P : a.x; }
    friend Self operator-(Self a, Self b) { return (a.x -= b.x) < 0 ? a.x + P : a.x; }
    friend Self operator*(Self a, Self b) { return MulType(a.x) * b.x % P; }
    friend Self &operator+=(Self &a, Self b) { return (a.x += b.x) >= P ? a.x -= P, a : a; }
    friend Self &operator-=(Self &a, Self b) { return (a.x -= b.x) < 0 ? a.x += P, a : a; }
    friend Self &operator*=(Self &a, Self b) { return a.x = MulType(a.x) * b.x % P, a; }
#define templ template <typename ExpType>
    templ Self Pow(ExpType Exp) {
        Self Base(*this), Ret(1);
        while (Exp) {
            if (Exp & 1) Ret *= Base;
            Base *= Base, Exp >>= 1;
        }
        return Ret;
    }
    templ Self &Pows(ExpType Exp) { return *this = Pow(Exp); }
    templ Self &PowEq(ExpType Exp) { return Pows(Exp); }
    templ Self &PowEqual(ExpType Exp) { return Pows(Exp); }
    templ friend Self Pow(Self Base, ExpType Exp) { return Base.Pow(Exp); }
#undef templ
    Self Inv() { return Pow(P - 2); }
    Self &Invs() { return Pows(P - 2); }
    Self &InvEq() { return Invs(); }
    Self &InvEqual() { return Invs(); }
    friend Self Inv(Self x) { return x.Pow(P - 2); }
    friend Self operator~(Self x) { return x.Inv(); }
    friend Self operator/(Self a, Self b) { return a * ~b; }
    friend Self &operator/=(Self &a, Self b) { return a *= ~b; }
    friend Self &operator++(Self &a) { return a += 1; }
    friend Self &operator--(Self &a) { return a -= 1; }
    friend Self operator++(Self &a, int) {
        Self Tmp = a;
        return a += 1, Tmp;
    }
    friend Self operator--(Self &a, int) {
        Self Tmp = a;
        return a -= 1, Tmp;
    }
    friend Self operator+(Self a) { return a; }
    friend Self operator-(Self a) { return 0 - a; }
    bool operator==(Self a) { return x == int(a); }
};

}  // namespace Oct

#endif

const int P = 998244353;

using MInt = Oct::ModInt<int, P, int64>;

const MInt R2 = ~MInt(2);

inline MInt I(int64 x) { return MInt(x % P); }

inline MInt Solve(int64 x, int64 y) {
    if (x <= 1) return 0;
    int64 t = y / x;
    return I(x) * I(x - 1) * t * R2 + Solve(y % x, x);
}

inline MInt Solve(int64 x, int64 y, int64 X, int64 Y) {
    return I(Y * y + X * x) * I(Y * x + X * y) - I(Y) * I(Y - 1) * I(x) * I(y) - I(X) * I(X - 1) * I(x) * I(y) -
           2 * I(X + Y) * (I(x) * I(y) - Solve(x, y));
}

inline int64 Gcd(int64 x, int64 y) {
    while (y) x %= y, std::swap(x, y);
    return x;
}

inline int64 GetSR1(int64 p) {
    for (;;) {
        int64 a = Random() % (p - 1) + 1;
        int64 b = Pow(int128(a), (p - 1) / 4, p);
        if (b * b % p == p - 1) return b <= (p - 1) / 2 ? b : p - b;
    }
}

inline std::pair<int64, int64> FermatDescent(int64 p) {
    int64 A = GetSR1(p), B = 1, u, v, M = (int128(A) * A + int128(B) * B) / p;
    while (M > 1) {
        u = A % M, v = B % M;
        if (u > M / 2) u -= M;
        if (v > M / 2) v -= M;
        int64 tA = (int128(u) * A + int128(v) * B) / M;
        int64 tB = (int128(v) * A - int128(u) * B) / M;
        A = std::abs(tA), B = std::abs(tB), M = (int128(A) * A + int128(B) * B) / p;
    }
    return std::make_pair(A, B);
}

const int N = 1000000;

std::complex<int64> Drs[N], Muls[N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int T;
    std::cin >> T;
    while (T--) {
        int64 x, y, t;
        std::cin >> x >> y;
        MInt Ans = I(x) * I(y) * (x == y ? 1 : 2);
        t = Gcd(x, y), x /= t, y /= t;
        std::map<int64, int> Map;
        for (auto x : GetFac<int128>(t)) ++Map[x];
        int64 tr = 1, Top = 1;
        Drs[0] = 1;
        for (auto Pair : Map) {
            int64 p = Pair.first, n = Pair.second;
            if (p % 4 == 3) {
                while (n--) tr *= p;
                continue;
            }
            int64 a, b;
            if (p == 2) {
                a = b = 1;
            } else {
                auto Pair = FermatDescent(p);
                a = Pair.first, b = Pair.second;
            }
            n <<= 1;
            std::complex<int64> Pows = {a, b};
            Muls[0] = 1;
            for (int i = 1; i <= n; ++i) Muls[i] = Muls[i - 1] * Pows;
            Pows = 1;
            for (int i = n - 1; i >= 0; --i) Muls[i] *= Pows *= std::complex<int64>(a, -b);
            for (int i = n; i >= 0; --i) {
                for (int j = 0; j < Top; ++j) Drs[i * Top + j] = Drs[j] * Muls[i];
            }
            Top *= n + 1;
        }
        if (Top > 1) {
            std::set<int64> Set{0};
            for (int i = 0; i < Top; ++i) {
                int64 a = std::abs(Drs[i].real()) * tr, b = std::abs(Drs[i].imag()) * tr;
                int64 t = std::min(a, b);
                if (Set.count(t)) continue;
                Set.insert(t);
                Ans += Solve(a, b, x, y) * (x == y ? 2 : 4);
            }
        }
        std::cout << int(Ans) << '\n';
    }
    return 0;
}