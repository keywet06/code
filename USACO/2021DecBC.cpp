#include <bits/stdc++.h>

const int B = 2;
const int C = 5;
const int N = 55;

char Map[N][N];

int T, n, k;
int f[C][N][N][B];

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> T;
    while (T--) {
        memset(f, 0, sizeof(f));
        memset(Map, 0, sizeof(Map));
        std::cin >> n >> k;
        for (int i = 1; i <= n; ++i) std::cin >> Map[i] + 1;
        for (int i = 2; Map[1][i] == '.'; ++i) f[0][1][i][0] = 1;
        for (int i = 2; Map[i][1] == '.'; ++i) f[0][i][1][1] = 1;
        for (int i = 1; i <= k; ++i) {
            for (int x = 1; x <= n; ++x) {
                for (int y = 1; y <= n; ++y) {
                    if (Map[x][y] == 'H') continue;
                    f[i][x][y][0] = f[i][x][y - 1][0] + f[i - 1][x][y - 1][1];
                    f[i][x][y][1] = f[i][x - 1][y][1] + f[i - 1][x - 1][y][0];
                }
            }
        }
        int ans = 0;
        for (int i = 0; i <= k; ++i) ans += f[i][n][n][0] + f[i][n][n][1];
        std::cout << ans << '\n';
    }
    return 0;
}