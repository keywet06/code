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

#ifndef OCT_MATRIX_HPP
#define OCT_MATRIX_HPP

namespace Oct {

template <typename Type, typename Vec = std::vector<Type>,
          typename Vec2D = std::vector<Vec> >
class Matrix {
   protected:
    Vec2D Data;

   public:
    inline Matrix() : Data() {}

    inline Matrix(const size_t N, const size_t M) : Data(N, Vec(M)) {}

    inline Matrix(const size_t N, const size_t M, const Type X)
        : Data(N, Vec(M)) {
        memset(Data, 0, sizeof(Data));
        for (size_t i = 0; i < N && i < M; ++i) Data[i][i] = X;
    }

    inline size_t SizeN() { return Data.size(); }

    inline size_t SizeM() { return Data.empty() ? 0 : Data.front().size(); }

    inline Matrix(const Vec2D V) : Data(V) {}

    inline Vec &operator[](size_t Id) { return Data[Id]; }

    inline void Swap(size_t Id1, size_t Id2) { Data[Id1].swap(Data[Id2]); }

    inline Matrix &Gauss() {
        for (size_t i = 0, u = 0; i < SizeN() && u < SizeM(); ++i, ++u) {
            do {
                for (size_t j = i; j < SizeM(); ++j) {
                    if (Data[j][u] != Type(0)) {
                        Swap(i, j);
                        break;
                    }
                }
                if (Data[i][u] != Type(0)) break;
            } while (++u < SizeM());
            if (u == SizeM()) break;
            Type Tmp = Type(1) / Data[i][u];
            for (size_t j = u; j < SizeM(); ++j) Data[i][j] *= Tmp;
            for (size_t j = 0; j < SizeN(); ++j) {
                if (Data[j][u] == Type(0) || j == i) continue;
                Tmp = Data[j][u];
                for (size_t k = u; k < SizeM(); ++k) {
                    Data[j][k] -= Tmp * Data[i][k];
                }
            }
        }
        return *this;
    }

    inline Matrix MGauss() { return Matrix(*this).Gauss(); }

    template <typename ArgsType>
    inline Matrix &Gauss(ArgsType &R) {
        for (size_t i = 0, u = 0; i < SizeN() && u < SizeM(); ++i, ++u) {
            do {
                for (size_t j = i; j < SizeM(); ++j) {
                    if (Data[j][u] != Type(0)) {
                        if (i == j) break;
                        Swap(i, j), R = -R;
                        break;
                    }
                }
                if (Data[i][u] != Type(0)) break;
            } while (++u < SizeM());
            if (u == SizeM()) break;
            Type Tmp;
            for (size_t j = 0; j < SizeN(); ++j) {
                if (Data[j][u] == Type(0) || j == i) continue;
                Tmp = Data[j][u] / Data[i][u];
                for (size_t k = u; k < SizeM(); ++k) {
                    Data[j][k] -= Tmp * Data[i][k];
                }
            }
        }
        return *this;
    }

    template <typename ArgsType>
    inline Matrix MGauss(ArgsType &R) {
        return Matrix(*this).Gauss(R);
    }
};

}  // namespace Oct

#endif

using int64 = long long;

const int P = 1000000000;

using MInt = Oct::ModInt<int, P, int64>;

const int N = 15;
const int M = N * N;

char s[N];

int n, m, Cnt;
int Id[N][N], Map[N][N];

int64 a[M][M];

int det(int n) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) a[i][j] = (a[i][j] + P) % P;
    }
    int64 ans = 1, f = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            int64 A = a[i][i], B = a[j][i];
            while (B != 0) {
                int64 t = A / B;
                A %= B;
                std::swap(A, B);
                for (int k = i; k <= n; ++k) {
                    a[i][k] = (a[i][k] - t * a[j][k] % P + P) % P;
                }
                for (int k = i; k <= n; ++k) std::swap(a[i][k], a[j][k]);
                f = -f;
            }
        }
        if (!a[i][i]) return 0;
        ans = ans * a[i][i] % P;
    }
    if (f == -1) return (P - ans) % P;
    return ans;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        std::cin >> s;
        for (int j = 0; j < m; ++j) {
            if (Map[i][j] = s[j] == '.') Id[i][j] = Cnt++;
        }
    }
    if (Cnt <= 1) return std::cout << 1 << std::endl, 0;
    Oct::Matrix<MInt> Mat(Cnt, Cnt);
    for (int i = 0; i + 1 < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (Map[i][j] && Map[i + 1][j]) {
                int x = Id[i][j], y = Id[i + 1][j];
                --Mat[x][y], --Mat[y][x], ++Mat[x][x], ++Mat[y][y];
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j + 1 < m; ++j) {
            if (Map[i][j] && Map[i][j + 1]) {
                int x = Id[i][j], y = Id[i][j + 1];
                --Mat[x][y], --Mat[y][x], ++Mat[x][x], ++Mat[y][y];
            }
        }
    }
    for (int i = 1; i < Cnt; ++i) {
        for (int j = 1; j < Cnt; ++j) a[i][j] = int(Mat[i][j]);
    }
    std::cout << det(Cnt - 1) << std::endl;
    std::vector<int>::iterator;
    return 0;
}