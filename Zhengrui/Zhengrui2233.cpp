#include <bits/stdc++.h>

#define Deb std::cerr
#define Delin Deb << "[Debug] at line " << __LINE__
#define Debug Delin << " : "
#define Deline Delin << std::endl

using int64 = long long;
using int128 = __int128;
using uint64 = unsigned long long;
using fuint64 = uint_fast64_t;

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

template <typename Type>
inline Type GetPrimitiveRootG(Type n) {
    if (n == 2 || n == 4) return n - 1;
    Type PhiN = n & 1 ? n - 1 : n / 2 - 1;
    auto PFac = GetFac(PhiN);
    std::sort(PFac.begin(), PFac.end());
    PFac.resize(std::unique(PFac.begin(), PFac.end()) - PFac.begin());
    for (Type &a : PFac) a = PhiN / a;
    bool Flag;
    for (Type x = 2; x < n; ++x) {
        if (Pow(x, PhiN, n) != Type(1)) continue;
        Flag = true;
        for (Type &a : PFac) {
            if (Pow(x, a, n) == Type(1)) {
                Flag = false;
                break;
            }
        }
        if (Flag) return x;
    }
    return Type(0);
}

template <typename Type>
inline Type GetPrimitiveRoot(Type n) {
    if (n == 2 || n == 4) return n - 1;
    if (n & 1 && !MillerRabin(n)) return 0;
    if (!(n & 1) && !(MillerRabin(n / 2))) return 0;
    return GetPrimitiveRootG(n);
}

template <typename Type, typename PType>
inline Type BSGS(Type Base, Type Power, PType P, PType Phi) {
    size_t S = ceil(sqrt(P));
    std::unordered_map<Type, size_t> Map;
    Type Now(Power), BaseR(Pow(Base, Phi - 1, P));
    for (size_t i = 0; i < S; ++i) Map[Now] = i, Now = Now * BaseR % P;
    Now = Base, Base = Pow(Base, S, P);
    for (size_t i = 0; i < S; ++i) {
        if (Map.count(Now)) return Map[Now] + i * S + 1;
        Now = Now * Base % P;
    }
    return P;
}

template <typename Type1, typename Type2>
inline Type1 ExGcd(Type1 a, Type1 b, Type2 &x, Type2 &y) {
    if (b == Type1(0)) return x = 1, y = 0, a;
    Type1 Ret = ExGcd(b, a % b, y, x);
    return y -= a / b * x, Ret;
}

const int N = 100005;

int64 PP[N], PS[N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int T;
    std::cin >> T;
    while (T--) {
        int64 x, m, p;
        std::cin >> x >> m >> p;
        int64 g = GetPrimitiveRoot(p);
        int64 X = BSGS(g, x, p, p - 1);
        int64 t = (p - 1) / Gcd(p - 1, X), l = 1, G;
        while ((G = Gcd(t, m)) > 1) t /= G, ++l;
        int64 Phi = t;
        auto Facs = GetFac(t);
        std::sort(Facs.begin(), Facs.end());
        for (int i = 0; i < Facs.size(); ++i) {
            if (i == 0 || Facs[i - 1] < Facs[i]) Phi = Phi / Facs[i] * (Facs[i] - 1);
        }
        size_t S = ceil(sqrt(Phi));
        PP[0] = PS[0] = 1;
        for (int i = 1; i <= S; ++i) PP[i] = PP[i - 1] * m % t;
        for (int i = 1; i <= S; ++i) PS[i] = PS[i - 1] * PP[S] % t;
        int64 Min = t;
        for (int64 i = 1; i * i <= Phi; ++i) {
            if (Phi % i) continue;
            if (PP[i % S] * PS[i / S] % t == 1) {
                Min = i;
                break;
            }
            int64 r = Phi / i;
            if (PP[r % S] * PS[r / S] % t == 1) Min = std::min(Min, r);
        }
        std::cout << l << ' ' << l + Min << std::endl;
    }
    return 0;
}