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
    inline ModInt(const DataType Val) : Data(Val) {}

    inline const DataType Value() const { return this->Data; }
    inline DataType &LValue() { return this->Data; }

    inline bool operator==(CurrentType x) const {
        return this->Value() == x.Value();
    }
    inline bool operator!=(CurrentType x) const {
        return this->Value() != x.Value();
    }

    inline CurrentType operator+(CurrentType x) const {
        return (x.LValue() += this->Value()) >= Mod ? x.Value() - Mod
                                                    : x.Value();
    }
    inline CurrentType &operator+=(CurrentType x) {
        if ((this->LValue() += x.Value()) >= Mod) this->LValue() -= Mod;
        return *this;
    }

    inline CurrentType operator-(CurrentType x) const {
        x.LValue() = this->Value() + Mod - x.Value();
        return x.Value() >= Mod ? x.Value() - Mod : x.Value();
    }
    inline CurrentType &operator-=(CurrentType x) {
        x.LValue() = this->Value() + Mod - x.Value();
        if (x.Value() >= Mod) x.LValue() -= Mod;
        return *this;
    }

    inline CurrentType operator+() { return *this; }
    inline CurrentType operator-() { return 0 - *this; }

    inline CurrentType operator*(CurrentType x) const {
        return this->Value() * OperType(x.Value()) % Mod;
    }
    inline CurrentType &operator*=(CurrentType x) {
        this->LValue() = this->Value() * OperType(x.Value()) % Mod;
        return *this;
    }

    inline CurrentType Pow(DataType Exp) const {
        CurrentType x = *this, ret = 1;
        while (Exp) {
            if (Exp & 1) ret *= x;
            x *= x, Exp >>= 1;
        }
        return ret;
    }

    inline CurrentType Inv() const { return this->Pow(Mod - 2); }

    inline CurrentType operator/(CurrentType x) const {
        return *this * x.Inv();
    }
    inline CurrentType &operator/=(CurrentType x) { return *this *= x.Inv(); }
};

}  // namespace Oct

#endif

using int32 = int_fast32_t;
using int64 = int_fast64_t;
using float96 = long double;
using pair = std::pair<int, int>;

const int N = 1000005;
const int P = 1000000007;

using MInt = Oct::ModInt<int32, P, int64>;

float96 Log[N], Fac[N];

MInt MFac[N], MFacR[N];

struct Comb {
    int m, n;
    float96 val;
    Comb(int _m, int _n) : m(_m), n(_n), val(Fac[m] - Fac[n] - Fac[m - n]) {}
    Comb(pair _p) { *this = Comb(_p.first, _p.second); }
    pair p() { return pair(m, n); }
};

inline bool operator<(Comb x, Comb y) { return x.val < y.val; }

inline MInt C(int m, int n) { return MFac[m] * MFacR[n] * MFacR[m - n]; }
inline MInt C(const Comb c) { return C(c.m, c.n); }

std::priority_queue<Comb> Que;

std::set<pair> Set;

inline void Emplace(int m, int n) { Que.emplace(m, n), Set.emplace(m, n); }

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    Log[0] = Fac[0] = 0, MFac[0] = 1;
    for (int i = 1; i < N; ++i) Log[i] = logl(i), Fac[i] = Fac[i - 1] + Log[i];
    for (int i = 1; i < N; ++i) MFac[i] = MFac[i - 1] * i;
    MFacR[N - 1] = MFac[N - 1].Inv();
    for (int i = N - 1; i; --i) MFacR[i - 1] = MFacR[i] * i;
    int n, k;
    MInt Ans;
    std::cin >> n >> k;
    Emplace(n, n / 2);
    while (k--) {
        Comb Now = Que.top();
        int m = Now.m, n = Now.n;
        Que.pop(), Ans += C(Now);
        if (n > 0) {
            if (!Set.count(pair(m, n - 1))) Emplace(m, n - 1);
            if (!Set.count(pair(m - 1, n - 1))) Emplace(m - 1, n - 1);
        }
        if (n < m) {
            if (!Set.count(pair(m - 1, n))) Emplace(m - 1, n);
            if (!Set.count(pair(m, n + 1))) Emplace(m, n + 1);
        }
    }
    std::cout << Ans.Value() << std::endl;
    return 0;
}