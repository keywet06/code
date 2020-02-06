#include <bits/stdc++.h>
const int N = 500;
const int Z = 10001;
const int mod = 10007;
int n, k, cnt;
int p[Z];
int b[N][N];
long long ans, sum;
int main() {
    std::cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> b[i][j];
        }
    }
    for (int i = 0; i < n - k + 1; ++i) {
        for (int j = 0; j < n - k + 1; ++j) {
            cnt = sum = 0;
            for (int x = 0; x < k; ++x) {
                for (int y = 0; y < k; ++y) {
                    ++p[b[i + x][j + y]];
                    sum += b[i + x][j + y];
                }
            }
            cnt -= k * k;
            for (int i = 0; i < Z; ++i) {
                if (!p[i]) {
                    continue;
                }
                cnt += p[i];
                sum -= p[i] * i;
                ans += i * cnt + sum;
                cnt += p[i];
                sum -= p[i] * i;
            }
            ans %= mod;
            memset(p, 0, sizeof(p));
        }
    }
    std::cout << ans << std::endl;
    return 0;
}