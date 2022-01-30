#include <bits/stdc++.h>

#define Deb std::cerr
#define Delin Deb << "[Debug] at Line " << __LINE__
#define Debug Delin << " : "
#define Deline Delin << std::endl

using int64 = long long;

const int P = int(1e9) + 7;
const int F = P - 1;
const int I2 = P + 1 >> 1;

inline int Add(int x, int y) { return (x += y) >= P ? x - P : x; }
inline int Sub(int x, int y) { return (x -= y) < 0 ? x + P : x; }
inline int Mul(int x, int y) { return int64(x) * y % P; }
inline int &Adds(int &x, int y) { return (x += y) >= P ? (x -= P) : x; }
inline int &Subs(int &x, int y) { return (x -= y) < 0 ? (x += P) : x; }
inline int &Muls(int &x, int y) { return x = int64(x) * y % P; }

template <typename... Args>
inline int Add(int x, int y, Args... args) {
    return Add(Add(x, y), args...);
}

template <typename... Args>
inline int Sub(int x, int y, Args... args) {
    return Sub(Sub(x, y), args...);
}

template <typename... Args>
inline int Mul(int x, int y, Args... args) {
    return Mul(Mul(x, y), args...);
}

template <typename... Args>
inline int &Adds(int &x, int y, Args... args) {
    return Adds(Adds(x, y), args...);
}

template <typename... Args>
inline int &Subs(int &x, int y, Args... args) {
    return Subs(Subs(x, y), args...);
}

template <typename... Args>
inline int &Muls(int &x, int y, Args... args) {
    return Muls(Muls(x, y), args...);
}

inline int Pow(int Base, int Exp) {
    int Ret(1);
    while (Exp) {
        if (Exp & 1) Muls(Ret, Base);
        Muls(Base, Base), Exp >>= 1;
    }
    return Ret;
}

inline int Inv(int x) { return Pow(x, P - 2); }

using Matrix = std::vector<std::vector<int> >;

inline size_t GetN(const Matrix A) { return A.size(); }
inline size_t GetM(const Matrix A) { return A.front().size(); }

inline Matrix MakeMatrix(size_t N, size_t M) {
    return Matrix(N, std::vector<int>(M));
}

inline Matrix MakeMatrix(size_t N, size_t M, int x) {
    Matrix Ret(N, std::vector<int>(M));
    for (int i = 0; i < N && i < M; ++i) Ret[i][i] = x;
    return Ret;
}

inline Matrix operator*(Matrix A, Matrix B) {
    assert(GetM(A) == GetN(B));
    int N = GetN(A), K = GetN(B), M = GetM(B);
    Matrix Ret(MakeMatrix(N, M));
    for (int i = 0; i < N; ++i) {
        for (int k = 0; k < K; ++k) {
            for (int j = 0; j < M; ++j) Adds(Ret[i][j], Mul(A[i][k], B[k][j]));
        }
    }
    return Ret;
}

inline Matrix Pow(Matrix Base, int Exp) {
    Matrix Ret(MakeMatrix(GetN(Base), GetM(Base), 1));
    while (Exp) {
        if (Exp & 1) Ret = Ret * Base;
        Base = Base * Base, Exp >>= 1;
    }
    return Ret;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int n, k;
    std::cin >> n >> k;
    Matrix A;
    [&]() {
        int a = Mul(n - 2, n - 3, I2), b = n - 2, c = n - 3, d = Add(a, c),
            e = Add(a, c, c, F);
        A = Pow({{a, 1, 1, 0, 0, 1, 0},
                 {1, a, 0, 1, 1, 0, 0},
                 {b, 0, d, 1, 1, 0, 1},
                 {0, b, 1, d, 0, 1, 1},
                 {0, b, 1, 0, d, 1, 1},
                 {b, 0, 0, 1, 1, d, 1},
                 {0, 0, c, c, c, c, e}},
                k);
    }();
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    std::vector<int> f(n + 1);
    auto Upd = [&](int x) {
        while (x <= n) ++f[x], x += x & -x;
    };
    auto Get = [&](int x) {
        int Ret = 0;
        while (x) Ret += f[x], x &= x - 1;
        return Ret;
    };
    int a0 = A[0][0], a1 = A[1][0], a2 = A[2][0], a3 = A[3][0], a4 = A[4][0],
        a5 = A[5][0], a6 = A[6][0];
    int Ans = 0, Sum = 0, V = Inv(n - 2);
    for (int i = 0; i < n; ++i) {
        int x = a[i], u = Get(x), v = i - u;
        Adds(Ans, Mul(a0, v), Mul(a1, u), Mul(a2, V, Sub(Sum, i, v)),
             Mul(a3, V, Sub(Mul(x - 1, i), u)),
             Mul(a4, V, Sub(Mul(n, i), Sum, u)),
             Mul(a5, V, Sub(Mul(n - x, i), v)), Mul(a6, i, I2));
        Upd(x), Adds(Sum, x);
    }
    std::cout << Ans << std::endl;
    return 0;
}