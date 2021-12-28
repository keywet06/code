#include <bits/stdc++.h>

template <typename Type>
inline void Mem(Type &Data) {
    memset(Data, 0, sizeof(Data));
}

using int64 = long long;
using int128 = __int128;

const int B = 2;
const int P = 1000007;

struct Mat {
    int64 a[B][B];
    inline Mat() { Mem(a); }
    inline explicit Mat(int64 x) { Mem(a), a[0][0] = a[1][1] = x; }
    int64 *operator[](size_t Id) { return a[Id]; }
};

inline Mat operator*(Mat A, Mat B) {
    Mat Ret;
    Ret[0][0] = (A[0][0] * B[0][0] + A[0][1] * B[1][0]) % P;
    Ret[0][1] = (A[0][0] * B[0][1] + A[0][1] * B[1][1]) % P;
    Ret[1][0] = (A[1][0] * B[0][0] + A[1][1] * B[1][0]) % P;
    Ret[1][1] = (A[1][0] * B[0][1] + A[1][1] * B[1][1]) % P;
    return Ret;
}

inline bool operator<(Mat A, Mat B) {
    if (A[0][0] != B[0][0]) return A[0][0] < B[0][0];
    if (A[0][1] != B[0][1]) return A[0][1] < B[0][1];
    if (A[1][0] != B[1][0]) return A[1][0] < B[1][0];
    return A[1][1] < B[1][1];
}

inline int64 BSGS(Mat A) {
    size_t T = P >> 3;
    Mat S(1), R(1);
    std::map<Mat, size_t> Map;
    for (size_t i = 0; i < T; ++i) Map[S] = i, S = S * A;
    for (size_t i = 1;; ++i) {
        R = R * S;
        if (Map.count(R)) return i * T - Map[R];
    }
}

size_t Q;

struct Mat2 {
    int128 a[B][B];
    inline Mat2() { Mem(a); }
    inline explicit Mat2(int64 x) { Mem(a), a[0][0] = a[1][1] = x; }
    int128 *operator[](size_t Id) { return a[Id]; }
};

inline Mat2 operator*(Mat2 A, Mat2 B) {
    Mat2 Ret;
    Ret[0][0] = (A[0][0] * B[0][0] + A[0][1] * B[1][0]) % Q;
    Ret[0][1] = (A[0][0] * B[0][1] + A[0][1] * B[1][1]) % Q;
    Ret[1][0] = (A[1][0] * B[0][0] + A[1][1] * B[1][0]) % Q;
    Ret[1][1] = (A[1][0] * B[0][1] + A[1][1] * B[1][1]) % Q;
    return Ret;
}

int64 n, a, b;

Mat Base;

inline int64 f2(int64 n) {
    Mat2 A(1), X;
    X[0][1] = 1, X[1][0] = b % Q, X[1][1] = a % Q;
    while (n) {
        if (n & 1) A = A * X;
        X = X * X, n >>= 1;
    }
    Mat2 x;
    x[1][0] = 1;
    return (A * x)[0][0];
}

inline int64 f(int64 n) {
    Mat A(1), X = Base;
    while (n) {
        if (n & 1) A = A * X;
        X = X * X, n >>= 1;
    }
    Mat x;
    x[1][0] = 1;
    return (A * x)[0][0];
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> a >> b;
    Base[0][1] = 1, Base[1][0] = b % P, Base[1][1] = a % P;
    Q = BSGS(Base);
    std::cout << f(f2(n)) << std::endl;
    return 0;
}