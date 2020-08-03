#include <bits/stdc++.h>
const int N = 200;
const int mod = 998244353;
int n, x, j;
int a[N], b[N], d[N], v[N];
inline void dfs(int c, int s) {
    if (c == n + 1) {
        x = 0;
        for (int i = 1; i <= n; ++i) {
            for (j = 0; j < i && j <= n - i; ++j) {
                if (b[i - j] == b[i + j]) {
                    ++x;
                } else {
                    break;
                }
            }
        }
        for (int i = 1; i <= n; ++i) {
            for (j = 1; j <= i && j <= n - i; ++j) {
                if (b[i - j + 1] == b[i + j]) {
                    ++x;
                } else {
                    break;
                }
            }
        }
        ++d[x];
        return;
    }
    for (int i = s; i <= n; ++i) {
        if (!v[i]) {
            v[i] = 1;
            b[i] = a[c];
            dfs(c + 1, a[c] == a[c + 1] ? i + 1 : 1);
            v[i] = 0;
        }
    }
}
int main() {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    std::sort(a + 1, a + n + 1);
    dfs(1, 1);
    for (int i = n * n; i; --i) {
        if (d[i]) {
            std::cout << i << " " << d[i] << std::endl;
            return 0;
        }
    }
    return 0;
}