#include <bits/stdc++.h>

using int64 = long long;

using Vector = std::vector<int>;
using Matrix = std::vector<Vector>;

inline std::ostream &operator<<(std::ostream &out, Matrix A) {
    for (Vector &v : A) {
        for (int &x : v) out << x << ' ';
        out << std::endl;
    }
    return out;
}

inline size_t GetN(const Matrix A) { return A.size(); }
inline size_t GetM(const Matrix A) { return A.front().size(); }

const int P = int(1e9) + 7;

inline int Add(int x, int y) { return (x += y) >= P ? x - P : x; }
inline int Mul(int x, int y) { return int64(x) * y % P; }
inline int &Adds(int &x, int y) { return (x += y) >= P ? (x -= P) : x; }
inline int &Muls(int &x, int y) { return x = int64(x) * y % P; }

inline Matrix operator+(Matrix A, Matrix B) {
    assert(GetN(A) == GetN(B) && GetM(A) == GetM(B));
    size_t N = GetN(A), M = GetM(A);
    Matrix Ret(N, Vector(M));
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) Ret[i][j] = Add(A[i][j], B[i][j]);
    }
    return Ret;
}

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

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    size_t n, k;
    std::cin >> n >> k;
    Matrix In(n, Vector(k)), Ou(k, Vector(n));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < k; ++j) std::cin >> Ou[j][i], Ou[j][i] %= P;
        for (size_t j = 0; j < k; ++j) std::cin >> In[i][j], In[i][j] %= P;
    }
    Matrix O(Matrix(k, Vector(k))), I(O);
    for (size_t i = 0; i < k; ++i) I[i][i] = 1;
    std::vector<Matrix> Mats(1, Ou * In), Matp(1, I);
    size_t m;
    std::cin >> m;
    for (size_t t = 0, u, v, d; t < m; ++t) {
        std::cin >> u >> v >> d, --u, --v;
        while (1ll << Mats.size() <= d) {
            Matp.emplace_back(Matp.back() + Matp.back() * Mats.back());
            Mats.emplace_back(Mats.back() * Mats.back());
        }
        Matrix Mu(I), Su(O);
        for (int i = Mats.size() - 1; i >= 0; --i) {
            if (!((d >> i) & 1)) continue;
            Su = Su + Mu * Matp[i];
            Mu = Mu * Mats[i];
        }
        Matrix x(n, Vector(1));
        x[u][0] = 1;
        std::cout << (In * (Su * (Ou * x)) + x)[v][0] << std::endl;
    }
    return 0;
}