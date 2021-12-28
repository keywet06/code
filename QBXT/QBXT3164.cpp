#include <bits/stdc++.h>

using int64 = long long;

const int N = 100005;

int n, m, PCnt;
int P[N], V[N];

int64 F[N];

inline int64 Solve(int n, int m) {
    size_t t = std::min(n, m);
    int64 Ret = 0;
    for (size_t i = 1, Last; i <= t; i = Last + 1) {
        Last = std::min(n / (n / i), m / (m / i));
        Ret += (F[Last] - F[i - 1]) * (n / i) * (m / i);
    }
    return Ret;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    F[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (!V[i]) V[i] = i, P[PCnt++] = i, F[i] = i - 1;
        for (int j = 0, t; j < PCnt && (t = P[j] * i) < N; ++j) {
            V[t] = P[j], F[t] = F[i] * (P[j] - bool(i % P[j]));
            if (i % P[j] == 0) break;
        }
    }
    for (int i = 1; i < N; ++i) F[i] += F[i - 1];
    std::cin >> n >> m;
    std::cout << 2 * Solve(n, m) - int64(n) * m << std::endl;
    std::cout << double(INT64_MAX);
    return 0;
}