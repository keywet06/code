#include <bits/stdc++.h>

#ifndef OCT_MODINT_HPP
#define OCT_MODINT_HPP

namespace Oct {

template <typename DataType, DataType Mod, typename OperType = DataType>
class ModInt {
   public:
    using CurrentType = ModInt<DataType, Mod, OperType>;
    using ThisType = CurrentType;

   protected:
    DataType Data;

   public:
    inline ModInt() : Data(0) {}

    inline explicit ModInt(const DataType Val) : Data(Val) {}

    inline explicit operator DataType() { return Data; }

    inline const DataType Value() const { return this->Data; }

    inline DataType &LValue() { return this->Data; }

    inline bool operator==(CurrentType x) const {
        return this->Value() == x.Value();
    }
    inline bool operator!=(CurrentType x) const {
        return this->Value() != x.Value();
    }

    inline CurrentType operator+(CurrentType x) const {
        return CurrentType(
            (x.LValue() += this->Value()) >= Mod ? x.Value() - Mod : x.Value());
    }
    inline CurrentType &operator+=(CurrentType x) {
        if ((this->LValue() += x.Value()) >= Mod) this->LValue() -= Mod;
        return *this;
    }

    inline CurrentType operator-(CurrentType x) const {
        x.LValue() = this->Value() + Mod - x.Value();
        return CurrentType(x.Value() >= Mod ? x.Value() - Mod : x.Value());
    }

    inline CurrentType &operator-=(CurrentType x) {
        this->LValue() += Mod - x.Value();
        if (this->Value() >= Mod) this->LValue() -= Mod;
        return *this;
    }

    inline CurrentType operator+() { return *this; }

    inline CurrentType operator-() { return CurrentType(0) - *this; }

    inline CurrentType &operator++() { return *this += CurrentType(1); }

    inline CurrentType &operator--() { return *this -= CurrentType(1); }

    inline CurrentType operator++(int) {
        return ++*this, *this - CurrentType(1);
    }

    inline CurrentType operator--(int) {
        return --*this, *this + CurrentType(1);
    }

    inline CurrentType operator*(CurrentType x) const {
        return CurrentType(this->Value() * OperType(x.Value()) % Mod);
    }

    inline CurrentType &operator*=(CurrentType x) {
        this->LValue() = this->Value() * OperType(x.Value()) % Mod;
        return *this;
    }

    inline CurrentType Pow(DataType Exp) const {
        CurrentType Base = *this, Ret = CurrentType(1);
        while (Exp) {
            if (Exp & 1) Ret *= Base;
            Base *= Base, Exp >>= 1;
        }
        return Ret;
    }

    inline CurrentType Inv() const { return this->Pow(Mod - 2); }

    inline CurrentType operator/(CurrentType x) const {
        return *this * x.Inv();
    }

    inline CurrentType &operator/=(CurrentType x) { return *this *= x.Inv(); }
};

}  // namespace Oct

#endif

using uint64 = unsigned long long;

template <typename Type>
inline Type Abs(const Type x) {
    return x < 0 ? -x : x;
}

template <typename Type>
inline Type Gcd(Type x, Type y) {
    return y ? Gcd(y, x % y) : x;
}

inline std::mt19937_64 GetRand() {
    return std::mt19937_64(
        std::chrono::system_clock::now().time_since_epoch().count());
}

inline uint64 Random(uint64 x, std::mt19937_64 &Rand) { return Rand() % x; }

inline uint64 Random(uint64 l, uint64 r, std::mt19937_64 &Rand) {
    return Random(r - l, Rand) + l;
}

template <typename Type1, typename Type2>
inline Type1 Pow(Type1 Base, Type2 Exp) {
    Type1 Ret = 1;
    while (Exp) {
        if (Exp & 1) Ret = Ret * Base;
        Base = Base * Base, Exp >>= 1;
    }
    return Ret;
}

template <typename Type1, typename Type2, typename Type3>
inline Type1 Pow(Type1 Base, Type2 Exp, const Type3 P) {
    Type1 Ret = 1;
    while (Exp) {
        if (Exp & 1) Ret = Ret * Base % P;
        Base = Base * Base % P, Exp >>= 1;
    }
    return Ret;
}

const size_t MillerRabinDefaultTestTimes = 16;

template <typename Type>
inline bool MillerRabin(Type n, std::mt19937_64 &Rand,
                        const size_t TestTimes = MillerRabinDefaultTestTimes) {
    if (n < 2 || !(n & 1)) return n == 2;
    Type e = n - 1;
    size_t m = 0;
    while (!(e & 1)) e >>= 1, ++m;
    for (size_t i = 0, j; i < TestTimes; ++i) {
        Type x = Pow(Type(Random(1, n, Rand)), e, n);
        if (x == 1) continue;
        for (j = 0; j < m; ++j) {
            if (x == 1) return false;
            if (x == n - 1) break;
            x = x * x % n;
        }
        if (j == m) return false;
    }
    return true;
}

template <typename Type>
inline bool MillerRabin(Type n,
                        const size_t TestTimes = MillerRabinDefaultTestTimes) {
    std::mt19937_64 Rand(GetRand());
    return MillerRabin(n, Rand, TestTimes);
}

template <typename Type>
inline Type PollardRho(Type n, std::mt19937_64 &Rand) {
    Type s = 0, t = 0, c = Random(1, n, Rand), Val = 1, d;
    for (size_t Step, Len = 1;; Len <<= 1, s = t, Val = 1) {
        for (Step = 0; Step < Len; ++Step) {
            t = (t * t + c) % n;
            Val = Val * Abs(s - t) % n;
            if (!(Step & 127)) {
                d = Gcd(Val, n);
                if (d > 1) return d;
            }
        }
        d = Gcd(Val, n);
        if (d > 1) return d;
    }
}

template <typename Type, typename RetType = std::vector<Type> >
inline RetType GetFac(Type n, std::mt19937_64 &Rand,
                      const size_t TestTimes = MillerRabinDefaultTestTimes) {
    if (n == 1) return RetType();
    if (MillerRabin(n, Rand, TestTimes)) {
        RetType Ret;
        Ret.push_back(n);
        return Ret;
    }
    Type d = PollardRho(n, Rand);
    RetType Ret(GetFac(d, Rand, TestTimes));
    for (Type x : GetFac(n / d, Rand, TestTimes)) Ret.push_back(x);
    return Ret;
}

template <typename Type, typename RetType = std::vector<Type> >
inline RetType GetFac(Type n,
                      const size_t TestTimes = MillerRabinDefaultTestTimes) {
    std::mt19937_64 Rand(GetRand());
    return GetFac(n, Rand, TestTimes);
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
inline Type BSGS(Type Base, Type Power, PType P) {
    size_t S = ceil(sqrt(P));
    std::unordered_map<Type, size_t> Map;
    Type Now(Power), BaseR(Pow(Base, P - 2, P));
    for (size_t i = 0; i < S; ++i) Map[Now] = i, Now = Now * BaseR % P;
    Now = 1, Base = Pow(Base, S, P);
    for (size_t i = 0; i < S; ++i) {
        if (Map.count(Now)) return Map[Now] + i * S;
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

using int64 = long long;
using int128 = __int128;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    int64 p, k, a, g, A, x, y, d;
    std::cin >> p >> k >> a;
    g = GetPrimitiveRootG(p);
    A = BSGS(g, a, p);
    if (A == p) return std::cout << 0 << '\n', 0;
    d = ExGcd(k, p - 1, x, y);
    if (A % d) return std::cout << 0 << '\n', 0;
    x *= A / d, y = (p - 1) / d;
    x = (x % y + y) % y;
    std::vector<int64> Ans;
    while (x < p - 1) Ans.push_back(Pow(g, x, p)), x += y;
    std::sort(Ans.begin(), Ans.end());
    std::cout << Ans.size() << '\n';
    for (int64 &x : Ans) std::cout << x << '\n';
    return 0;
}
