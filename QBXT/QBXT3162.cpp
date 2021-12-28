#include <bits/stdc++.h>

using int64 = long long;
using uint64 = unsigned long long;

const int N = 10000005;
const int D = 9;

int T, n, m, PCnt;
int P[N], S[N], Rx[N], Ry[N];
int C[D][D], F[D][D];

int64 Mu[N];

inline int64 Solve(int n, int m) {
    uint64 t = std::min(n, m);
    int64 Ret = 0;
    for (uint64 i = 1, Last; i <= t; i = Last + 1) {
        Last = std::min(n / (n / i), m / (m / i));
        Ret += (Mu[Last] - Mu[i - 1]) * (n / i) * (m / i);
    }
    return Ret;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    for (int i = 0; i < D; ++i) {
        C[i][0] = 1;
        for (int j = 1; j <= i; ++j) C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
    F[1][0] = 1, F[1][1] = -1;
    for (int i = 2; i < D; ++i) {
        for (int j = 0; j < D; ++j) {
            for (int x = 1; x <= i; ++x) {
                for (int y = 0; y + (x == i) <= j; ++y) {
                    F[i][j] -= C[j][y] * C[i - y][x - y] * F[x][y];
                }
            }
        }
    }
    for (int i = 2; i < N; ++i) {
        if (!S[i]) S[i] = i, P[PCnt++] = i, Mu[i] = 1, Rx[i] = 1;
        for (int j = 0, k; j < PCnt && (k = P[j] * i) < N; ++j) {
            S[k] = P[j];
            if (!Mu[i]) continue;
            if (i % P[j]) {
                Mu[k] = F[Rx[k] = Rx[i] + 1][Ry[k] = Ry[i]];
            } else if (i / P[j] % P[j]) {
                Mu[k] = F[Rx[k] = Rx[i]][Ry[k] = Ry[i] + 1];
            }
            if (i % P[j] == 0) break;
        }
    }
    for (int i = 1; i < N; ++i) Mu[i] += Mu[i - 1];
    std::cin >> T;
    while (T--) {
        std::cin >> n >> m;
        std::cout << Solve(n, m) << '\n';
    }
    return 0;
}