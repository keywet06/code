#include <bits/stdc++.h>

const int N = 105;

int T, n, m, k, x, Flag;
int last[N], p[N], use[N], up[N];
int f[N][N];

inline void Connect(int u, int v) {
    if (f[u][v] == -1 || f[v][u] == 1) return void(Flag = true);
    f[u][v] = 1, f[v][u] = -1;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> T;
    while (T--) {
        memset(last, 0, sizeof(last));
        memset(up, -1, sizeof(up));
        memset(f, 0, sizeof(f));
        Flag = false;
        std::cin >> n >> m;
        for (int i = 1; i <= m; ++i) {
            memset(p, 0, sizeof(p));
            memset(use, 0, sizeof(use));
            std::cin >> k;
            std::stack<int> S;
            for (int j = 1; j <= k; ++j) {
                std::cin >> x, p[j] = x * 2 - !use[x];
                if (Flag) continue;
                if (use[x]) {
                    if (S.top() != x && (Flag = true)) continue;
                    S.pop();
                } else {
                    int Up = S.empty() ? 0 : S.top();
                    if (up[x] != -1 && up[x] != Up && (Flag = true)) continue;
                    up[x] = Up, S.push(x);
                }
                use[x] = 1;
                Flag |= last[p[j]] && last[p[j]] != i - 1;
                last[p[j]] = i;
            }
            if (Flag) continue;
            for (int j = 1; j < k; ++j) Connect(p[j], p[j + 1]);
        }
        n <<= 1;
        for (int k = 1; k <= n; ++k) {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    if (f[i][k] == 1 && f[k][j] == 1) Connect(i, j);
                    if (f[i][k] == -1 && f[k][j] == -1) Connect(j, i);
                }
                if (Flag) break;
            }
            if (Flag) break;
        }
        std::cout << (Flag ? "NO" : "YES") << '\n';
    }
    return 0;
}