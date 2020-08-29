#include <bits/stdc++.h>
const int N = 200005;
int n, t, k, cnt;
int a[N], fa[N];
std::vector<int> v[N];
int main() {
    std::cin >> n >> t >> k;
    a[0] = 1;
    for (int i = 1; i <= t; i++) std::cin >> a[i];
    if (a[t] > k || n - t < k) {
        std::cout << -1 << '\n';
        return 0;
    }
    for (int i = 0; i <= t; i++) {
        for (int j = 1; j <= a[i]; j++) v[i].push_back(++cnt);
    }
    for (int i = 0; i < a[1]; i++) fa[v[1][i]] = 1;
    for (int i = 2; i <= t; i++) fa[v[i][0]] = v[i - 1][0];
    int l = n - t - k;
    for (int i = 2; i <= t; i++) {
        for (int j = 1; j < a[i]; j++) {
            if (l && j < a[i - 1]) {
                fa[v[i][j]] = v[i - 1][j];
                l--;
            } else {
                fa[v[i][j]] = v[i - 1][0];
            }
        }
    }
    if (l) {
        std::cout << -1 << '\n';
        return 0;
    }
    std::cout << n << '\n';
    for (int i = 2; i <= n; i++) std::cout << fa[i] << ' ' << i << '\n';

    return 0;
}