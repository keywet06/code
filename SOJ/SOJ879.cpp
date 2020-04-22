#include <bits/stdc++.h>
const int N = 60005;
int m, n;
int L[N], R[N], w[N], s[N], z[N];
std::set<int> set;
std::map<int, int> map;
inline void plus(const int l, const int r, const int x) {
    for (int i = l; i <= r; ++i) {
        s[i] += x;
    }
}
inline void dfs(int c) {
    if (c > m) {
        for (int i = 1; i <= n; ++i) {
            if (std::abs(s[i]) > 1) {
                return;
            }
        }
        for (int i = 1; i <= m; ++i) {
            std::cout << bool(~z[i]) << " ";
        }
        std::cout << std::endl;
        exit(0);
    }
    if (w[c]) {
        z[c] = w[c];
        plus(L[c], R[c], z[c]);
        dfs(c + 1);
        plus(L[c], R[c], -z[c]);
    } else {
        z[c] = -1;
        plus(L[c], R[c], z[c]);
        dfs(c + 1);
        plus(L[c], R[c], -z[c]);
        z[c] = 1;
        plus(L[c], R[c], z[c]);
        dfs(c + 1);
        plus(L[c], R[c], -z[c]);
    }
}
int main() {
    std::cin >> m >> n;
    for (int i = 1; i <= m; ++i) {
        std::cin >> L[i] >> R[i] >> w[i];
        set.insert(L[i]);
        set.insert(R[i]);
        if (w[i] < 1) {
            w[i] = -1 - w[i];
        }
    }
    n = 0;
    for (std::set<int>::iterator it = set.begin(); it != set.end(); ++it) {
        map[*it] = ++n;
    }
    dfs(1);
    std::cout << -1 << std::endl;
    return 0;
}