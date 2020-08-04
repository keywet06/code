#include <bits/stdc++.h>
const int N = 105;
int n, K, ans;
int l[N], r[N];
inline void dfs(int c, int sum) {
    if (c > n) {
        ans += !sum;
        return;
    }
    for (int i = l[c]; i <= r[c]; ++i) dfs(c + 1, sum ^ i);
}
int main() {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> l[i] >> r[i];
    dfs(1, 0);
    std::cout << ans << std::endl;
    return 0;
}