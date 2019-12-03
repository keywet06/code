#include <bits/stdc++.h>
const int M = 50005;
const int N = 105;
int T, ans, sum, n;
int dp[M];
int a[N];
void init();
int Main();
int main() {
    scanf("%d", &T);
    while (T--) {
        init();
        Main();
    }
    return 0;
}
inline void init() {
    sum = 0;
    memset(dp, 0, sizeof(dp));
}
inline int Main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        sum += a[i];
    }
    dp[0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = sum / 2; j >= a[i]; --j) {
            dp[j] |= dp[j - a[i]];
        }
    }
    for (int i = sum / 2;; --i) {
        if (dp[i]) {
            ans = i;
            break;
        }
    }
    printf("%d\n", sum - (ans << 1));
    return 0;
}