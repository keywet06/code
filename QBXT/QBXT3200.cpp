#include <bits/stdc++.h>

using int64 = long long;

const int P = 998244353;

inline int Add(int x, int y) { return (x += y) >= P ? x - P : x; }
inline int Mul(int x, int y) { return int64(x) * y % P; }
inline int &Adds(int &x, int y) { return (x += y) >= P ? (x -= P) : x; }
inline int &Muls(int &x, int y) { return x = int64(x) * y % P; }

using Vector = std::vector<int>;
using Matrix = std::vector<Vector>;

std::mt19937_64 rd(std::chrono::system_clock::now().time_since_epoch().count());

inline size_t GetN(const Matrix A) { return A.size(); }
inline size_t GetM(const Matrix A) { return A.front().size(); }

inline Matrix operator*(Matrix A, Matrix B) {
    assert(GetM(A) == GetN(B));
    size_t N = GetN(A), K = GetN(B), M = GetM(B);
    Matrix Ret(N, Vector(M));
    for (size_t i = 0; i < N; ++i) {
        for (size_t k = 0; k < K; ++k) {
            for (size_t j = 0; j < M; ++j) {
                Adds(Ret[i][j], Mul(A[i][k], B[k][j]));
            }
        }
    }
    return Ret;
}

inline Matrix In(int n) {
    Matrix Ret(n, Vector(n));
    for (Vector &v : Ret) {
        for (int &x : v) std::cin >> x;
    }
    return Ret;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    int n;
    while (std::cin >> n) {
        Matrix A, B, C;
        A = In(n), B = In(n), C = In(n);
        Matrix D(1, Vector(n));
        for (int i = 0; i < n; ++i) D[0][i] = rd() % P;
        std::cout << (D * A * B == D * C ? "Yes" : "No") << std::endl;
    }
    return 0;
}