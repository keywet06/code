#include <bits/stdc++.h>

using int64 = long long;

namespace oct {

void ios() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
}

}  // namespace oct

const int64 P = 1000000007;
const int64 N = 5100;
const int64 M = N << 1;

int64 n, m;
int64 p[M], pre[M], re[M];
int64 f[N][N];

int64 mul(int64 a, int64 b, int64 p) {
    int64 ans = 0;
    if (b == 0) return ans % p;
    for (; b; b >>= 1) {
        if (b & 1) ans = (ans + a) % p;
        a = (a + a) % p;
    }
    return ans % p;
}

int64 powmod(int64 a, int64 b, int64 p) {
    int64 ans = 1;
    if (b == 0) return ans % p;
    for (; b; b >>= 1) {
        if (b & 1) ans = (ans * a) % p;
        a = (a * a) % p;
    }
    return ans % p;
}

int64 inv(int64 x) { return powmod(x, P - 2, P); }

int64 cb(int64 n, int64 m) {
    return m > n ? 0 : ((pre[n] * re[m]) % P * re[n - m]) % P;
}

int main() {
    pre[0] = pre[1] = re[0] = re[1] = 1;
    for (int64 i = 2; i < M; i++) pre[i] = (pre[i - 1] * i) % P;
    re[M - 1] = inv(pre[M - 1]);
    for (int64 i = M - 2; i >= 2; i--) {
        re[i] = (re[i + 1] * (i + 1)) % P;
    }
    oct::ios();
    std::cin >> n >> m;
    for (int64 i = 1; i <= n; i++) {
        for (int64 j = 1; i * j <= m; j++) {
            for (int64 k = i, sg = 1; k <= n && j * k <= m; k++, sg = (P - sg))
                f[i][j] = (f[i][j] + (((sg * cb(k, i)) % P * cb(n, k)) % P *
                                      cb(m - j * k + n - 1, n - 1)) %
                                         P) %
                          P;
            f[i][j] = (f[i][j] * inv(cb(m + n - 1, n - 1))) % P;
        }
    }
    for (int64 i = n; i >= 1; i--) {
        p[i] = 1;
        for (int64 j = 1; j <= m; j++) {
            f[i][j] = (f[i][j] + f[i + 1][j]) % P, p[i] = (p[i] + f[i][j]) % P;
        }
    }
    for (int64 i = 1; i <= n; i++){
        p[i] = (p[i] + p[i - 1]) % P, std::cout << p[i] << '\n';}
    return 0;
}