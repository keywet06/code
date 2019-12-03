#include <bits/stdc++.h>
const int N = 5005;
char c[N];
double ans[N][N];
int m, n, x, y;
long long a[N], b[N];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
        a[i] += a[i - 1];
    }
    scanf("%s", c + 1);
    for (int i = 1; i <= n; ++i) {
        b[i] = b[i - 1] + c[i] - '0';
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (b[j] - b[i - 1] > 1) {
                ans[i][j] = (double)(a[j] - a[i - 1]) / (j - i + 1);
            }
        }
    }
    for (int i = n; i; --i) {
        for (int j = 1; j <= n; ++j) {
            ans[i][j] =
                std::max(ans[i][j], std::max(ans[i + 1][j], ans[i][j - 1]));
        }
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d", &x, &y);
        printf("%.15f\n", ans[x][y]);
    }
    return 0;
}