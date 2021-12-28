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

template <typename Type, size_t SN, size_t SM>
class Matrix {
   public:
    using CurrentType = Matrix<Type, SN, SM>;
    using ThisType = CurrentType;

   protected:
    Type Data[SN][SM];

   public:
    inline Matrix() { memset(Data, 0, sizeof(Data)); }
    inline Matrix(const Type x) {
        memset(Data, 0, sizeof(Data));
        for (size_t i = 0; i < SN && i < SM; ++i) Data[i][i] = x;
    }
    inline Matrix(const Type Source[SN][SM]) {
        memcpy(Data, Source, sizeof(Data));
    }
    inline Type *operator[](size_t x) { return Data[x]; }
};

template <typename Type, size_t SN, size_t SK, size_t SM>
inline Matrix<Type, SN, SM> operator*(Matrix<Type, SN, SK> A,
                                      Matrix<Type, SK, SM> B) {
    Matrix<Type, SN, SM> Ret;
    for (size_t i = 0; i < SN; ++i) {
        for (size_t k = 0; k < SK; ++k) {
            for (size_t j = 0; j < SM; ++j) Ret[i][j] += A[i][k] * B[k][j];
        }
    }
    return Ret;
}

template <typename Type, typename DType>
inline Type Pow(Type Base, DType Exp) {
    Type Ret(1);
    while (Exp) {
        if (Exp & 1) Ret = Ret * Base;
        Base = Base * Base, Exp >>= 1;
    }
    return Ret;
}

using int64 = long long;

const int P = int(1e9) + 7;

using MInt = Oct::ModInt<int, P, int64>;
using Vec = Matrix<MInt, 6, 1>;
using Mat = Matrix<MInt, 6, 6>;

int n;

Vec x, b;

Mat A;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    x[0][0] = 1;
    A[0][0] = 1, A[0][1] = 1, A[0][2] = 1;
    A[1][0] = 2, A[1][3] = 1;
    A[2][0] = 2, A[2][3] = 1;
    A[3][3] = 1, A[3][4] = 1, A[3][5] = 1;
    A[4][0] = 1, A[4][3] = 2;
    A[5][0] = 1, A[5][3] = 2;
    std::cin >> n;
    b = Pow(A, n) * x;
    std::cout << b[0][0].Value() << std::endl;
    return 0;
}
