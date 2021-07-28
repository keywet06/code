#include <bits/stdc++.h>

using int64 = long long;
using uint64 = unsigned long long;

const int C = 256;
const int N = 400005;

bool s[N + 1][256];

int n, m, u, p, c, e;

uint64 a1, a2;

std::string t;

uint64 myRand(uint64 &k1, uint64 &k2) {
    uint64 k3 = k1, k4 = k2;
    k1 = k4;
    k3 ^= (k3 << 23);
    k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
    return k2 + k4;
}

void gen(int n, uint64 a1, uint64 a2) {
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < C; j++) {
            s[i][j] = (myRand(a1, a2) & (1ull << 32)) ? 1 : 0;
        }
    }
}

int main() {
    freopen("qi.in", "r", stdin);
    freopen("qi.out", "w", stdout);
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> m >> a1 >> a2;
    gen(n, a1, a2);
    for (int i = 1; i <= m; ++i) {
        std::cin >> t >> u;
        for (int j = 1; j <= n; ++j) {
            e = 0;
            for (int k = 0; k < 64; ++k) {
                c = t[k] <= '9' ? t[k] - '0' : t[k] - 'A' + 10;
                for (int l = 0; l < 4; ++l) {
                    e += ((c >> l) ^ p) & 1 != s[j][k << 2 | (3 - l)];
                }
                if (e > u) break;
            }
            if (e <= u) break;
        }
        std::cout << (p = e <= u) << '\n';
    }
    return 0;
}