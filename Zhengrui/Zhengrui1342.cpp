#include <bits/stdc++.h>
const int N = 505;
const long long mod = 1000000007;
long long n, m, k, x, y;
long long deg[N];
long long mul[N][N];
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m >> k;
    for (int i = 1; i <= m; ++i) {
        std::cin >> x >> y;
        ++deg[x];
        ++deg[y];
        mul[x][y] = 1;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (mul[i][j]) {
                mul[i][j] = deg[i] - 1;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (mul[i][i] != 1) {
                  
        }
    }
    return 0;
}