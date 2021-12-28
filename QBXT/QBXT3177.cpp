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

const int N = 55;
const int M = 105;
const int P = 1000000009;

using MInt = Oct::ModInt<int, P, int64>;

int n, m, lx, ly, px, py, qx, qy, sx, sy, u;
int ca[N], cb[N];

MInt Sum, Ans;
MInt Fac[N], FacR[N];
MInt po1[M];

inline MInt C(int m, int n) { return Fac[m] * FacR[n] * FacR[m - n]; }

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> m;
    po1[0] = Fac[0] = 1;
    for (int i = 1; i < N; ++i) Fac[i] = Fac[i - 1] * i;
    FacR[N - 1] = Fac[N - 1].Inv();
    for (int i = N - 1; i; --i) FacR[i - 1] = FacR[i] * i;
    for (int i = 1; i <= n + m; ++i) po1[i] = po1[i - 1] * -MInt(1);
    for (int i = 1; i <= n; ++i) std::cin >> ca[i];
    for (int i = 1; i <= m; ++i) std::cin >> cb[i];
    std::sort(ca + 1, ca + n + 1, [](int x, int y) { return x > y; });
    std::sort(cb + 1, cb + m + 1, [](int x, int y) { return x > y; });
    if (ca[1] != cb[1]) return std::cout << 0 << std::endl, 0;
    Ans = lx = ly = 1;
    while (lx <= n || ly <= m) {
        u = std::max(ca[lx], cb[ly]);
        while (lx <= n && ca[lx] == u) ++lx, ++px;
        while (ly <= m && cb[ly] == u) ++ly, ++py;
        Sum = 0, sx = px + qx, sy = py + qy;
        for (int x = 0; x <= px; ++x) {
            for (int y = 0; y <= py; ++y) {
                Sum += po1[x + y] * MInt(u).Pow(sx * sy - (sx - x) * (sy - y)) *
                       MInt(u + 1).Pow((sx - x) * (sy - y) - qx * qy) *
                       C(px, x) * C(py, y);
            }
        }
        Ans *= Sum, qx = sx, qy = sy, px = py = 0;
    }
    std::cout << Ans.Value() << std::endl;
    return 0;
}
