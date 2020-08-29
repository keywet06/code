#include <bits/stdc++.h>
const int N = 300005;
int n, x, k;
int a[N], b[N], ans[N], c[N];
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        ans[i] = a[i] ? n + 1 : 0, c[i] = -1;
    }
    for (int i = 2; i <= n; i++) {
        std::cin >> x;
        b[i] = x, c[x] = i;
    }
    for (int i = n; i > 1; i--) {
        if (c[i] == -1) ans[i] = 1, k++;
        x = b[i];
        ans[x] = a[x] ? std::min(ans[x], ans[i]) : ans[x] + ans[i];
    }
    std::cout << k + 1 - ans[1] << '\n';
    return 0;
}