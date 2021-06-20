#include <bits/stdc++.h>

class ifastream {
   public:
    ifastream &operator>>(int &x) {
        static int c;
        c = getchar();
        while (c < '0' || c > '9') c = getchar();
        x = c - '0', c = getchar();
        while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
        return *this;
    }
} ifin;

const int N = 4005;
const int K = 805;

int n, k;
int u[N][N], w[N][N], dp[K][N];

int sum(int l, int r, int up, int dn) {
    return u[--l][--up] + u[r][dn] - u[l][dn] - u[r][up];
}

void solve(int k, int l, int r, int pl, int pr) {
    if (l > r) return;
    int mid = l + r >> 1, p = 0;
    for (int i = pl; i <= pr; ++i) {
        if (dp[k - 1][i - 1] + w[i][mid] < dp[k][mid]) {
            p = i, dp[k][mid] = dp[k - 1][i - 1] + w[i][mid];
        }
    }
    solve(k, l, mid - 1, pl, p);
    solve(k, mid + 1, r, p, pr);
}

int main() {
    ifin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) ifin >> u[i][j], u[i][j] += u[i - 1][j];
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) u[i][j] += u[i][j - 1];
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) w[i][j] = sum(i, j, i, j) / 2;
    }
    memset(dp, 50, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i <= k; ++i) solve(i, 1, n, 1, n);
    std::cout << dp[k][n] << std::endl;
    return 0;
}