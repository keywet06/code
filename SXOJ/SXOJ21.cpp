#include <bits/stdc++.h>

using namespace std;

const int P = 998244353;
const int N = 20000010;

int T, n, m, k, l;
int pre[N], re[N], inv[N];

int mul(int a, int b) { return 1ll * a * b % P; }

int binom(int a, int b) {
    return a < b ? 0 : mul(pre[a], mul(re[b], re[a - b]));
}

int power(int a, int b) {
    int ret = 1;
    while (b) ret = b & 1 ? mul(ret, a) : ret, a = mul(a, a), b >>= 1;
    return ret;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    pre[1] = re[1] = re[0] = inv[1] = 1;
    for (int i = 2; i < N; i++) pre[i] = mul(pre[i - 1], i);
    re[N - 1] = power(pre[N - 1], P - 2);
    for (int i = N - 2; i >= 0; i--) re[i] = mul(re[i + 1], i + 1);
    std::cin >> T;
    while (T--) {
        std::cin >> n >> m >> k, l = n + m;
        if (n + m < k && (std::cout << 0 << '\n', 1)) continue;
        std::cout << mul(binom(n, k), mul(pre[n + m], re[n + m - k])) << '\n';
    }
    return 0;
}