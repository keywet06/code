#include <bits/stdc++.h>
const int C = 8;
const int C1 = C + 1;
const int D = 1 << C;
const int N = 1005;
int n, ans;
int num[C1];
int a[N];
int dp[N][D];
std::vector<int> pos[C1];
int check(int x) {
    memset(num, 0, sizeof(num));
    memset(dp, -1, sizeof(dp));
    dp[0][0] = 0;
    int res = -1;
    for (int i = 0; i < n; i++) {
        if (i) num[a[i]]++;
        for (int j = 0; j < (1 << C); j++) {
            if (dp[i][j] == -1) continue;
            for (int k = 1; k <= C; k++) {
                if (j & (1 << k - 1)) continue;
                int t = num[k] + x - 1;
                if (t < pos[k].size()) {
                    dp[pos[k][t]][j | (1 << k - 1)] =
                        std::max(dp[pos[k][t]][j | (1 << k - 1)], dp[i][j]);
                }
                if (++t < pos[k].size()) {
                    dp[pos[k][t]][j | (1 << k - 1)] =
                        std::max(dp[pos[k][t]][j | (1 << k - 1)], dp[i][j] + 1);
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) res = std::max(res, dp[i][(1 << C) - 1]);
    if (res == -1) return 0;
    ans = std::max(ans, C * x + res);
    return 1;
}
void split(int l, int r) {
    if (l > r) return;
    int mid = (l + r) >> 1;
    if (check(mid)) {
        split(mid + 1, r);
    } else {
        split(l, mid - 1);
    }
}
int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        pos[a[i]].push_back(i);
    }
    for (int i = 1; i <= C; i++) {
        if (pos[i].size() == 0) {
            for (int j = 1; j <= C; j++) {
                if (pos[j].size()) ans++;
            }
            std::cout << ans << std::endl;
            return 0;
        }
    }
    split(1, n);
    std::cout << ans << std::endl;
    return 0;
}