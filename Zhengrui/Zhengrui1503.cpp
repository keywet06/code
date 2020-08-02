#include <bits/stdc++.h>
const int N = 20;
const int P = 1 << N;
const long long mod = 998244353;
int T, l, n, k, t, left, le, o, f;
long long ans, now, put;
long long lg[P];
long long A[N][N], C[N][N];
std::vector<int> list;
inline long long power(long long x, int y) {
    return y ? power(x * x % mod, y / 2) * (y & 1 ? x : 1) % mod : 1;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> T;
    A[0][0] = C[0][0] = 1;
    for (int i = 0; i < N; ++i) lg[1 << i] = i;
    for (int i = 1; i < N; ++i) {
        A[i][0] = C[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            A[i][j] = (j * A[i - 1][j - 1] + A[i - 1][j]) % mod;
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
        }
    }
    while (T--) {
        std::cin >> n >> k;
        ans = 0;
        for (int i = 1; i < 1 << k; ++i) {
            list.clear();
            le = n;
            t = i;
            l = 0;
            f = lg[i & (-i)];
            while (t) {
                list.push_back(lg[t & (-t)] - f);
                t &= t - 1;
                ++l;
            }
            list.push_back(k);
            now = put = 1;
            left = k;
            for (int j = 1; j < list.size(); ++j) {
                t = list[j] - list[j - 1];
                now = (now * C[left][t]) % mod;
                put = (put * A[t][t]) % mod;
                left -= t;
            }
            le -= left = f;
            o = 1;
            while (o < list.size() && list[o] <= k - left) ++o;
            if (o < list.size()) {
                now = (now * A[list[o] - list[o - 1]][list[o] - k + left]) % mod;
                for (++o; o < list.size(); ++o) {
                    t = list[o] - list[o - 1];
                    now = (now * A[t][t]) % mod;
                }
            }
            le -= left = le % k;
            for (o = 1; o < list.size() && list[o] < left; ++o) {
                t = list[o] - list[o - 1];
                now = (now * A[t][t]) % mod;
            }
            if (o != list.size()) {
                t = list[o] - list[o - 1];
                now = (now * A[t][left - list[o - 1]]) % mod;
            }
            now = (now * power(put, le / k)) % mod;
            (ans += l & 1 ? now : mod - now) %= mod;
        }
        std::cout << ans << std::endl;
    }
    return 0;
}