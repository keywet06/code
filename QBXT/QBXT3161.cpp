#include <bits/stdc++.h>

const int N = 50005;

int T, a, b, c, d, k, PCnt;
int P[N], S[N], Mu[N];

inline int Solve(int n, int m) {
    int t = std::min(n, m), Ret = 0;
    for (int i = 1, Last; i <= t; i = Last + 1) {
        Last = std::min(n / (n / i), m / (m / i));
        Ret += (Mu[Last] - Mu[i - 1]) * (n / i) * (m / i);
    }
    return Ret;
}

inline int Solve(int n, int m, int k) {
    return Solve(n / k, m / k);
}

inline int Solve(int a, int b, int c, int d, int k) {
    return Solve(b, d, k) - Solve(a, d, k) - Solve(b, c, k) + Solve(a, c, k);
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    Mu[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (!S[i]) S[i] = i, P[PCnt++] = i, Mu[i] = -1;
        for (int j = 0; j < PCnt && P[j] * i < N; ++j) {
            S[P[j] * i] = P[j], Mu[P[j] * i] = i % P[j] ? -Mu[i] : 0;
            if (i % P[j] == 0) break;
        }
    }
    for (int i = 1; i < N; ++i) Mu[i] += Mu[i - 1];
    std::cin >> T;
    while (T--) {
        std::cin >> a >> b >> c >> d >> k;
        std::cout << Solve(--a, b, --c, d, k) << '\n';
    }
    return 0;
}