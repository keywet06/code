#include <bits/stdc++.h>

using int64 = long long;

const int64 N = 305;

char s[N];

int64 base1 = 131, base2 = 233, n, m;
int64 qpow1[N], qpow2[N];
int64 a[N][N], d[N][N], sum[N][N], aa[N][N], sum2[N][N];

int64 cal(int64 x, int64 y, int64 l, int64 type) {
    if (type == 1) {
        return sum[x][y] - sum[x - l][y] * qpow2[l] - sum[x][y - l] * qpow1[l] +
               sum[x - l][y - l] * qpow1[l] * qpow2[l];
    }
    y = m + l - y, x = n + l - x;
    return sum2[x][y] - sum2[x - l][y] * qpow2[l] - sum2[x][y - l] * qpow1[l] +
           sum2[x - l][y - l] * qpow1[l] * qpow2[l];
}
int64 work(int64 l) {
    for (int64 i = l; i <= n; i++) {
        for (int64 j = l; j <= m; j++) {
            if (cal(i, j, l, 1) == cal(i, j, l, 2)) return 1;
        }
    }
    return 0;
}
int64 ans = 0;
int main() {
    std::cin >> n >> m;
    for (int64 i = 1; i <= n; i++) {
        scanf("%s", s + 1);
        for (int64 j = 1; j <= (int64)strlen(s + 1); j++) a[i][j] = s[j] - '0';
    }
    qpow1[0] = 1;
    for (int i = 1; i <= 300; i++) qpow1[i] = qpow1[i - 1] * base1;
    qpow2[0] = 1;
    for (int i = 1; i <= 300; i++) qpow2[i] = qpow2[i - 1] * base2;
    for (int64 i = 1; i <= n; i++) {
        for (int64 j = 1; j <= m; j++) d[i][j] = d[i][j - 1] * base1 + a[i][j];
    }
    for (int64 i = 1; i <= n; i++) {
        for (int64 j = 1; j <= m; j++) {
            sum[i][j] = sum[i - 1][j] * base2 + d[i][j];
        }
    }
    for (int64 i = 1; i <= n; i++) {
        for (int64 j = 1; j <= m; j++) aa[i][j] = a[n - i + 1][m - j + 1];
    }
    for (int64 i = 1; i <= n; i++) {
        for (int64 j = 1; j <= m; j++) d[i][j] = d[i][j - 1] * base1 + aa[i][j];
    }
    for (int64 i = 1; i <= n; i++) {
        for (int64 j = 1; j <= m; j++) {
            sum2[i][j] = sum2[i - 1][j] * base2 + d[i][j];
        }
    }
    for (int i = 1; i <= std::max(n, m); i++) {
        if (work(i)) ans = i;
    }
    ans != 1 && ans != 0 ? printf("%llu", ans) : printf("-1\n");
    return 0;
}