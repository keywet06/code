#include <bits/stdc++.h>
const int N = 1005;
int ans, n, m, x;
int a[N], b[N];
int f[N][N];
int gcd(int, int);
int main() {
    scanf("%d %d %d", &n, &m, &x);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d", &b[i]);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            f[i][j] = (gcd(a[i], b[j]) >= x) ? f[i - 1][j - 1] + 1 : 0;
            ans = std::max(ans, f[i][j]);
        }
    }
    printf("%d\n", ans);
    return 0;
}
inline int gcd(int a, int b) {
    if (a % b == 0) {
        return b;
    }
    return gcd(b, a % b);
}