#include <bits/stdc++.h>
using namespace std;
const int INF = 100000;
int n, i, j, k, m, w, opt;
int l[10010], h[10010];
int dp[10010][1010];
int x[10010], y[10010];
bool p[10010];
int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (i = 0; i < n; i++) {
        scanf("%d %d", &x[i], &y[i]);
        l[i] = 0;
        h[i] = m + 1;
    }
    l[n] = 0;
    h[n] = m + 1;
    for (i = 0; i < k; i++) {
        scanf("%d", &w);
        scanf("%d %d", &l[w], &h[w]);
        p[w] = true;
    }
    for (i = 1; i <= n; i++) {
        for (j = 0; j <= m; j++) {
            dp[i][j] = INF;
        }
    }
    dp[0][0] = INF;
    for (i = 1; i <= m; i++) {
        dp[0][i] = 0;
    }
    for (i = 1; i <= n; i++) {
        for (j = x[i - 1]; j <= m; j++) {
            if (j == m) {
                for (w = m - x[i - 1]; w <= m; w++) {
                    dp[i][j] = std::min(dp[i][j], dp[i - 1][w] + 1);
                    dp[i][j] = std::min(dp[i][j], dp[i][w] + 1);
                }
            }
            dp[i][j] = std::min(dp[i][j], dp[i - 1][j - x[i - 1]] + 1);
            dp[i][j] = std::min(dp[i][j], dp[i][j - x[i - 1]] + 1);
        }
        for (j = std::max(1, l[i] + 1); j <= std::min(m - y[i - 1], h[i] - 1); j++) {
            dp[i][j] = std::min(dp[i][j], dp[i - 1][j + y[i - 1]]);
        }
        for (j = l[i]; j >= 1; j--) {
            dp[i][j] = INF;
        }
        for (j = h[i]; j <= m; j++) {
            dp[i][j] = INF;
        }
    }
    int ans = INF;
    int cnt = k;
    for (i = n; i >= 1; i--) {
        for (j = l[i] + 1; j <= h[i] - 1; j++) {
            ans = std::min(ans, dp[i][j]);
        }
        if (ans < INF) {
            break;
        }
        if (p[i] == true) {
            k--;
        }
    }
    if (cnt == k) {
        printf("1\n%d", ans);
    } else {
        printf("0\n%d", k);
    }
    return 0;
}