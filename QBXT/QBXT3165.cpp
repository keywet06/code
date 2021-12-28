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

    inline operator const_cast<DataType>() { return Data; }

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

template <typename Type>
inline Type Sqr(Type x) {
    return x * x;
}

using int32 = int_fast32_t;
using int64 = int_fast64_t;
using int128 = __int128;

const int32 P = 1000000007;

using MInt = Oct::ModInt<int32, P, int64>;

const int N = 10000005;

int PCnt;
int Pri[N], Phi[N], V[N];

int64 n;

MInt Ans;
MInt SPhi[N];

std::unordered_map<int64, MInt> Map;

inline MInt GetSPhi(int64 n) {
    if (n < N) return SPhi[n];
    if (Map.count(n)) return Map[n];
    MInt Ret(int128(n) * (n + 1) / 2 % P);
    for (size_t d = 2, Last; d <= n; d = Last + 1) {
        Last = n / (n / d), Ret -= GetSPhi(n / d) * MInt((Last - d + 1) % P);
    }
    return Map[n] = Ret;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    Phi[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (!V[i]) V[i] = i, Pri[PCnt++] = i, Phi[i] = i - 1;
        for (int j = 0, t; j < PCnt && (t = Pri[j] * i) < N; ++j) {
            V[t] = Pri[j], Phi[t] = Phi[i] * (Pri[j] - bool(i % Pri[j]));
            if (i % Pri[j] == 0) break;
        }
    }
    for (int i = 1; i < N; ++i) SPhi[i] = SPhi[i - 1] + MInt(Phi[i] % P);
    std::cin >> n;
    for (size_t d = 1, Last; d <= n; d = Last + 1) {
        Last = n / (n / d);
        Ans += (GetSPhi(Last) - GetSPhi(d - 1)) * Sqr(MInt(n / d % P));
    }
    std::cout << int32(Ans) << std::endl;
    return 0;
}