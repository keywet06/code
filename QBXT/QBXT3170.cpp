#include <bits/stdc++.h>

template <typename Type, typename MType>
inline Type Pow(Type x, MType m) {
    Type Ret(1);
    while (m) {
        if (m & 1) Ret = Ret * x;
        x = x * x, m >>= 1;
    }
    return Ret;
}

using int64 = long long;

const int K = 50;
const int G = 55;

struct Mat {
    int64 a[K][K];
    inline Mat() { memset(a, 0, sizeof(a)); }
    inline Mat(int64 x) {
        memset(a, 0, sizeof(a));
        for (int i = 0; i < K; ++i) a[i][i] = x;
    }
    int64 *operator[](size_t x) { return a[x]; }
};

int64 P;

inline Mat operator*(Mat A, Mat B) {
    Mat Ret;
    for (size_t i = 0; i < K; ++i) {
        for (size_t k = 0; k < K; ++k) {
            for (size_t j = 0; j < K; ++j) Ret[i][j] += A[i][k] * B[k][j] % P;
        }
    }
    for (size_t i = 0; i < K; ++i) {
        for (size_t j = 0; j < K; ++j) Ret[i][j] %= P;
    }
    return Ret;
}

int n, k, r;

int64 C[G][G];

Mat A, x, b;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> P >> k >> r;
    for (int i = 0; i < G; ++i) {
        C[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % P;
        }
    }
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j <= k; ++j) A[i][(i + j) % k] += C[k][j];
    }
    x[0][0] = 1;
    b = Pow(A, n) * x;
    std::cout << b[r][0] << std::endl;
    return 0;
}