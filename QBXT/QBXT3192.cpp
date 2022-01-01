#include <bits/stdc++.h>

using int64 = long long;
using int128 = __int128;

using Vector = std::vector<int128>;
using Vector2 = std::vector<Vector>;

inline Vector2 operator*(Vector2 A, Vector2 B) {
    assert(A.front().size() == B.size());
    size_t N = A.size(), K = B.size(), M = B.front().size();
    Vector2 Ret(N, Vector(M));
    for (size_t i = 0; i < N; ++i) {
        for (size_t k = 0; k < K; ++k) {
            for (size_t j = 0; j < M; ++j) Ret[i][j] += A[i][k] * B[k][j];
        }
    }
    return Ret;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    size_t n, m, k;
    std::cin >> n >> m >> k;
    if (!m) return std::cout << -1 << std::endl, 0;
    size_t t = 4 * n, r = 3 * n, p = 2 * n;
    Vector2 A(t, Vector(t));
    for (size_t i = 0; i < n; ++i) {
        ++A[n + i][p + i], ++A[i][n + i];
        ++A[r + i][p + i], ++A[r + i][r + i];
    }
    for (size_t i = 0, u, v, c; i < m; ++i) {
        std::cin >> u >> v >> c, --u, --v;
        ++A[p + v][(3 - c) * n + u];
    }
    auto Check = [&](Vector2 &A) {
        int64 u = k + n;
        for (size_t i = r; i < t; ++i) {
            for (size_t j = p; j < r; ++j) {
                if ((u -= A[i][j]) <= 0) return false;
            }
        }
        return true;
    };
    std::vector<Vector2> Mats;
    Mats.emplace_back(A);
    while (Check(Mats.back())) {
        if (Mats.size() > 100) return std::cout << -1 << std::endl, 0;
        Mats.push_back(Mats.back() * Mats.back());
    }
    Vector2 Mat(t, Vector(t));
    for (int i = 0; i < t; ++i) Mat[i][i] = 1;
    int64 Ans = 0;
    for (int i = Mats.size() - 1; i >= 0; --i) {
        auto Tmp = Mat * Mats[i];
        if (Check(Tmp)) Mat.swap(Tmp), Ans |= 1ll << i;
    }
    std::cout << Ans << std::endl;
    return 0;
}
