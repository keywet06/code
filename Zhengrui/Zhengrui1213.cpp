#include <bits/stdc++.h>
const int mod = 998244353;
const int N = 16;
const int Np = N + 5;
const int M = Np + 5;
int n, m, x, y, tag;
int come[M], to[M];
int f[Np], size[Np];
long long ans, sum;
int find(int x);
inline int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        std::cin >> come[i] >> to[i];
    }
    for (int i = 0; i < 1 << m; ++i) {
        for (int j = 1; j <= n; ++j) {
            f[j] = j;
            size[j] = 1;
        }
        tag = 0;
        for (int j = 0; j < m; ++j) {
            if (i & (1 << j)) {
                if ((x = find(come[j])) == (y = find(to[j]))) {
                    ++tag;
                } else {
                    size[y] += size[x];
                    size[x] = 0;
                    f[x] = y;
                }
            }
        }
        if (tag > 1) {
            continue;
        }
        sum = 1;
        for (int j = 1; j <= n; ++j) {
            if (size[j]) {
                (sum *= size[j]) %= mod;
            }
        }
        (ans += sum) %= mod;
    }
    std::cout << ans << std::endl;
    return 0;
}