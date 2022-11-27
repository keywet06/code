#include <bits/stdc++.h>

using int64 = long long;

const int N = 200005;
const int P = 1000000007;

int64 Pow(int64 Base, int Exp) {
    int64 Ret = 1;
    while (Exp) {
        if (Exp & 1) Ret = Ret * Base % P;
        Base = Base * Base % P, Exp >>= 1;
    }
    return Ret;
}

int T, n, m, k;

int64 f[N], Fac[N], Rac[N], Pro[N], Pak[N];

int main() {
    Fac[0] = Rac[0] = 1;
    for (int i = 1; i < N; ++i) Fac[i] = Fac[i - 1] * i % P;
    Rac[N - 1] = Pow(Fac[N - 1], P - 2);
    for (int i = N - 2; i; --i) Rac[i] = Rac[i + 1] * (i + 1) % P;
    std::cin >> T;
    while (T--) {
        std::cin >> n >> m >> k;
        int64 Ca = 0, Cb = 0, Ret = 0;
        for (int i = 1; i <= n + m + 2; ++i) {
            int64 a = Pow(i, n), b = Pow(i, m);
            f[i] = ((a - Ca) * (b - Cb) % P + P) % P, Ca = a, Cb = b;
        }
        for (int i = 1; i <= n + m + 2; ++i) f[i] = (f[i - 1] + f[i]) % P;
        if (k <= n + m + 2 && (std::cout << f[k] << std::endl, true)) continue;
        Pro[0] = Pak[n + m + 3] = 1;
        for (int i = 1; i <= n + m + 2; ++i) Pro[i] = Pro[i - 1] * (k - i) % P;
        for (int i = n + m + 2; i; --i) Pak[i] = Pak[i + 1] * (k - i) % P;
        for (int i = 1; i <= n + m + 2; ++i) {
            int64 cp = Pro[i - 1] * Pak[i + 1] % P;
            int64 cq = Rac[i - 1] * Rac[n + m + 2 - i] % P;
            int64 Mul = ((n + m + 2 - i) & 1) ? -1 : 1;
            Ret = (Ret + (Mul * cp % P + P) % P * cq % P * f[i] % P) % P;
        }
        std::cout << Ret << std::endl;
    }
    return 0;
}