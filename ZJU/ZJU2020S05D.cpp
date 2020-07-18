#include <bits/stdc++.h>
const int mod = 2020;
const int N = 51;
class mat {
   public:
    int x, y;
    int a[N][N];
    mat();
    int *operator[](int x);
};
int u, v, n, m, x;
mat m1, m0, mans;
inline mat::mat() {
    x = y = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) a[i][j] = 0;
}
inline int *mat::operator[](int x) { return a[x]; }
inline mat operator*(mat x, mat y) {
    mat a;
    a.x = x.x;
    a.y = y.y;
    for (int i = 0; i < a.x; ++i) {
        for (int j = 0; j < a.y; ++j) {
            for (int k = 0; k < x.y; ++k) a[i][j] += x[i][k] * y[k][j];
            a[i][j] %= mod;
        }
    }
    return a;
}
template <typename Type>
inline Type power(Type x, int y) {
    return y ^ 1 ? (y & 1 ? power(x * x, y / 2) * x : power(x * x, y / 2)) : x;
}
int main() {
    std::cin >> n >> m;
    m1.x = m1.y = n + 1;
    for (int i = 1; i <= m; ++i) {
        std::cin >> u >> v;
        ++m1[u][v];
        ++m1[v][u];
    }
    for (int i = 0; i <= n; ++i) {
        m1[i][i] = 1;
        m1[i][0] = 1;
    }
    m0.x = 1;
    m0.y = n + 1;
    m0[0][1] = 1;
    std::cin >> x;
    m0 = m0 * power(m1, x + 1);
    std::cout << m0[0][0] << std::endl;
    return 0;
}