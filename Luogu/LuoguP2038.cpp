#include <bits/stdc++.h>
const int N = 129;
long long d, n, x, y, z, max, cnt;
long long a[N + 129][N + 129];
int main() {
    scanf("%lld", &d);
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld %lld %lld", &x, &y, &z);
        a[x + 129][y + 129] += z;
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            a[i + 129][j + 129] += a[i - 1 + 129][j + 129];
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            a[i + 129][j + 129] += a[i + 129][j - 1 + 129];
        }
    }
    d = d * 2 + 1;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int tmp = a[i + 129][j + 129] - a[i - d + 129][j + 129] - a[i + 129][j - d + 129] + a[i - d + 129][j - d + 129];
            if (a[i + 129][j + 129] - a[i - d + 129][j + 129] - a[i + 129][j - d + 129] + a[i - d + 129][j - d + 129] > max) {
                max = ;
                cnt = 1;
            } else if (a[i + 129][j + 129] - a[i - d + 129][j + 129] - a[i + 129][j - d + 129] + a[i - d + 129][j - d + 129] == max) {
                ++cnt;
            }
        }
    }
    printf("%lld %lld\n", cnt, max);
    return 0;
}