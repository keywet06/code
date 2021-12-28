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
        this->LValue() += Mod - x.Value();
        if (this->Value() >= Mod) this->LValue() -= Mod;
        return *this;
    }

    inline CurrentType operator+() { return *this; }
    inline CurrentType operator-() { return CurrentType(0) - *this; }

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

using int64 = long long;

const int N = 2005;
const int P = 1000000007;

using MInt = Oct::ModInt<int, P, int64>;

int n, ca, cb;
int a[N], Num[N];

MInt Ans, O;
MInt Fac[N], FacR[N];

inline MInt C(int m, int n) { return Fac[m] * FacR[n] * FacR[m - n]; }

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    Fac[0] = 1;
    for (int i = 1; i < N; ++i) Fac[i] = Fac[i - 1] * i;
    FacR[N - 1] = Fac[N - 1].Inv();
    for (int i = N - 1; i; --i) FacR[i - 1] = FacR[i] * i;
    std::cin >> n, O = -1;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        if (a[i] > 0) ++Num[a[i]];
        if (a[i] == i) return std::cout << 0 << std::endl, 0;
    }
    for (int i = 1; i <= n; ++i) {
        if (a[i] == -1) ++(Num[i] ? ca : cb);
    }
    for (int i = 0; i <= cb; ++i) {
        Ans += (O = -O) * C(cb, i) * Fac[ca + cb - i];
    }
    std::cout << Ans.Value() << std::endl;
    return 0;
}
