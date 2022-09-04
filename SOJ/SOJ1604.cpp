#include <bits/stdc++.h>

using int64 = long long;

const int N = 25;

int n;
int px[N], py[N];
int ct[11], c[11][252];
int f[1024][1024];

int64 Diss[N][N];

inline int64 Dis(int a, int b) {
    return int64(px[a] - px[b]) * (px[a] - px[b]) + int64(py[a] - py[b]) * (py[a] - py[b]);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n;
    for (int i = 0; i <= 2 * n; ++i) std::cin >> px[i] >> py[i];
    for (int i = 0; i <= 2 * n; ++i) {
        for (int j = 0; j <= 2 * n; ++j) Diss[i][j] = Dis(i, j);
    }
    for (int i = 0, x; i < 1 << n; ++i) x = __builtin_popcount(i), c[x][ct[x]++] = i;
    f[0][0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int ea = 0, a; ea < ct[i]; ++ea) {
            a = c[i][ea];
            for (int eb = 0, b; eb < ct[i]; ++eb) {
                if (!f[a][b = c[i][eb]]) continue;
                std::cout << std::bitset<2>(a) << " . " << std::bitset<2>(b) << std::endl;
                for (int c = 0; c < n; ++c) {
                    if ((a >> c) & 1) continue;
                    int64 Min = Diss[c][n << 1];
                    for (int d = 0; d < n; ++d) {
                        if (!((b >> d) & 1)) Min = std::min(Min, Diss[c][n + d]);
                    }
                    for (int d = 0; d < n; ++d) {
                        if (!((b >> d) & 1) && Min == Diss[c][n + d]) f[a | 1 << c][b | 1 << d] = 1;
                    }
                }
            }
        }
    }
    std::cout << (f[(1 << n) - 1][(1 << n) - 1] ? "POSSIBLE" : "IMPOSSIBLE") << '\n';
    return 0;
}