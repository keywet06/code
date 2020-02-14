#include <bits/stdc++.h>
const int N = 20;
const int Ni = 4;
const int _1_leftN = 1 << N;
int ans, n, max, l;
int w[N];
int a[_1_leftN], vis[_1_leftN], as[_1_leftN], p[_1_leftN];
void dfs(int c, int last, int now);
inline void dfs(int c, int last, int now) {
    if (c == 1 << n) {
        if (now > ans) {
            ans = now;
            for (int i = 1; i < 1 << i; ++i) {
                as[i] = a[i];
            }
        }
        return;
    }
    if (now + max * ((1 << n) - c) <= ans) {
        return;
    }
    vis[last] = 1;
    for (int i = 1; i < 1 << n; ++i) {
        if (vis[i]) {
            continue;
        }
        a[c] = i;
        dfs(c + 1, i, now + p[last ^ i]);
    }
    vis[last] = 0;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n;
    l = 1;
    for (int i = 0; i < n; ++i) {
        std::cin >> w[i];
        if (w[i] != 1) {
            l = 0;
        }
    }
    for (int i = 0; i < 1 << n; ++i) {
        for (int j = 0; j < n; ++j) {
            if ((1 << j) & i) {
                p[i] ^= w[j];
            }
        }
        max = std::max(max, p[i]);
    }
    if (l) {
        std::cout << (1 << n) - 2 << std::endl;
        as[1] = 1;
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < 1 << i; ++j) {
                as[j + (1 << i)] = as[(1 << i) - j - 1] | (1 << i);
            }
        }
        for (int i = 1; i < 1 << n; ++i) {
            std::cout << as[i] << " ";
        }
        std::cout << std::endl;
        return 0;
    }
    for (int i = 1; i < 1 << n; ++i) {
        a[1] = i;
        dfs(2, i, 0);
    }
    std::cout << ans << std::endl;
    for (int i = 1; i < 1 << n; ++i) {
        std::cout << as[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}