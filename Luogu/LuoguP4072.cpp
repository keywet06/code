#include <bits/stdc++.h>
const int N = 3000;
const int Np = N + 5;
long long n, m, head, tail;
long long L[Np], b[Np], q[Np];
long long f[Np][Np];
template <typename _Tp>
_Tp sqr(_Tp);
template <typename _Tp>
inline _Tp sqr(_Tp x) {
    return x * x;
}
double slope(long long, long long, long long);
inline double slope(long long _a, long long _b, long long _c) {
    return (double)(f[_a][_b] - f[_a][_c] + sqr(b[_b]) - sqr(b[_c])) /
           (b[_b] - b[_c]);
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        std::cin >> L[i];
        b[i] = b[i - 1] + L[i];
    }
    memset(f, 127, sizeof(f));
    f[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        f[1][i] = b[i] * b[i];
    }
    for (int j = 2; j <= m; ++j) {
        head = 1, tail = 0;
        for (int i = 1; i <= n; ++i) {
            while (head < tail &&
                   slope(j - 1, q[head], q[head + 1]) < 2 * b[i]) {
                head++;
            }
            f[j][i] =
                f[j - 1][q[head]] + (b[q[head]] - b[i]) * (b[q[head]] - b[i]);
            while (head < tail && slope(j - 1, q[tail - 1], q[tail]) >
                                      slope(j - 1, q[tail], i)) {
                tail--;
            }
            q[++tail] = i;
        }
    }
    std::cout << m * f[m][n] - b[n] * b[n] << std::endl;
    return 0;
}