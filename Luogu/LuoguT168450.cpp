#include <bits/stdc++.h>

using int64 = long long;

const int N = 1000005;
const int K = 21;
const int P = 1000000007;

int T, n, k, t1, t2;
int fdp[N][K];

int64 pre[N], inv[N], lre[N];

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    pre[0] = inv[0] = inv[1] = lre[0] = 1;
    for (int i = 1; i < N; ++i) pre[i] = pre[i - 1] * i % P;
    for (int i = 2; i < N; ++i) inv[i] = (P - P / i) * inv[P % i] % P;
    for (int i = 1; i < N; ++i) lre[i] = lre[i - 1] * inv[i] % P;
    for (int i = 0; i < N; ++i) fdp[i][0] = lre[i];
    for (int i = 1; i < K; ++i) {
        fdp[0][i] = fdp[0][0], fdp[1][i] = fdp[1][0];
        for (int j = 2; j < N; ++j) {
            t1 = (1 + j) / 2, t2 = j - t1;
            fdp[j][i] = 1ll * fdp[t1][i - 1] * fdp[t2][i - 1] % P;
        }
    }
    std::cin >> T;
    while (T--) {
        std::cin >> n >> k;
        std::cout << pre[n] * fdp[n][std::min(k, K - 1)] % P << '\n';
    }
    return 0;
}