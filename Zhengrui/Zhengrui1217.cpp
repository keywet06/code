#include <bits/stdc++.h>
const int N = 500;
const int Z = 10001;
const int mod = 10007;
int n, k;
int p[Z];
int b[N][N];
long long ans, ssum, scnt, sum;
int main() {
    std::cin >> n >> k;
    int Z = 11;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> b[i][j];
            if (b[i][j] >= Z) {
                Z = 10001;
            }
        }
    }
    for (int i = 0; i <= n - k; ++i) {
        sum = 0;
        for (int x = 0; x < k; ++x) {
            for (int y = 0; y < k - 1; ++y) {
                ++p[b[i + x][y]];
                sum += b[i + x][y];
            }
        }
        for (int j = 0; j <= n - k; ++j) {
            for (int x = 0; x < k; ++x) {
                ++p[b[i + x][j + k - 1]];
                sum += b[i + x][j + k - 1];
            }
            ssum = sum;
            scnt = -k * k;
            for (int l = 0; l < Z; ++l) {
                if (!p[l]) {
                    continue;
                }
                scnt += 2 * p[l];
                ssum -= 2 * p[l] * l;
                (ans += p[l] * (l * scnt + ssum)) %= mod;
            }
            for (int x = 0; x < k; ++x) {
                --p[b[i + x][j]];
                sum -= b[i + x][j];
            }
        }
        memset(p, 0, sizeof(p));
    }
    std::cout << ans << std::endl;
    return 0;
}