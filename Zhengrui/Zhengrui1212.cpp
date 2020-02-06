#include <bits/stdc++.h>
const int N = 50000;
const int Np = N + 5;
int n, cnt, u, v, Q, T, head, tail, ans, x;
int f[Np], q[Np];
int find(int dollar);
inline int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> Q >> T;
    for (int i = 1; i <= n; ++i) {
        f[i] = i;
    }
    cnt = n;
    for (int i = 1; i <= Q; ++i) {
        std::cin >> u >> v;
        u = (u + T * ans - 1) % n + 1;
        v = (v + T * ans - 1) % n + 1;
        if (find(u) != find(v)) {
            f[find(u)] = find(v);
            --cnt;
        }
        ans = INT_MAX;
        head = 1;
        tail = 0;
        memset(q, 0, sizeof(q));
        x = 0;
        while (tail < n) {
            ++tail;
            if (!q[find(tail)]++) {
                ++x;
            }
            while (q[find(head)] > 1) {
                --q[find(head++)];
            }
            if (x == cnt) {
                ans = std::min(ans, tail - head + 1);
            }
        }
        std::cout << ans << std::endl;
    }
    return 0;
}