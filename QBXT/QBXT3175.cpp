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

const int N = 805;
const int R = 1605;
const int K = 55;
const int P = 10007;

using MInt = Oct::ModInt<int, P>;

int tx, ty, mx, my, r, k;
int a[N];

MInt Ans, O;
MInt Fac[R], FacR[R];
MInt fx[R][N], gx[R][N], fy[R][N], gy[R][N], fk[R][N];

inline MInt C(int m, int n) { return Fac[m] * FacR[n] * FacR[m - n]; }

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    Fac[0] = 1;
    for (int i = 1; i < R; ++i) Fac[i] = Fac[i - 1] * i;
    FacR[R - 1] = Fac[R - 1].Inv();
    for (int i = R - 1; i; --i) FacR[i - 1] = FacR[i] * i;
    std::cin >> tx >> ty >> mx >> my >> r >> k;
    for (int i = 1; i <= k; ++i) std::cin >> a[i], a[i] /= 10;
    std::sort(a + 1, a + k + 1);
    fk[0][0] = fx[0][0] = gx[0][0] = fy[0][0] = gy[0][0] = 1, O = -1;
    for (int i = 1; i <= tx; ++i) gx[0][i] = 1;
    for (int i = 1; i <= ty; ++i) gy[0][i] = 1;
    for (int i = 1; i <= r; ++i) {
        for (int j = 0; j <= tx; ++j) {
            fx[i][j] = gx[i - 1][j];
            if (j > mx) fx[i][j] -= gx[i - 1][j - mx - 1];
            gx[i][j] = j ? gx[i][j - 1] + fx[i][j] : fx[i][j];
        }
    }
    for (int i = 1; i <= r; ++i) {
        for (int j = 0; j <= ty; ++j) {
            fy[i][j] = gy[i - 1][j];
            if (j > my) fy[i][j] -= gy[i - 1][j - my - 1];
            gy[i][j] = j ? gy[i][j - 1] + fy[i][j] : fy[i][j];
        }
    }
    for (int i = 1; i <= r; ++i) {
        for (int j = std::min(tx, ty) / 10; ~j; --j) {
            for (int l = 0; l <= k && a[l] <= j; ++l) {
                fk[i][j] += fk[i - 1][j - a[l]];
            }
        }
    }
    for (int i = 0; i <= r; ++i) {
        O = -O;
        for (int j = std::min(tx, ty) / 10; ~j; --j) {
            Ans += O * fk[i][j] * fx[r - i][tx - j * 10] *
                   fy[r - i][ty - j * 10] * C(r, i);
        }
    }
    std::cout << Ans.Value() << std::endl;
    return 0;
}
