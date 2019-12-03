#include "kw/BigInt.hpp"
const int N = 1000000;
int cnt, m, n;
int pri[N + 5], vis[N + 5], ms[N + 5];
kw::BigInt ans = 1;
void plus(int);
void less(int);
int main() {
    for (int i = 2; i <= N; ++i) {
        if (!vis[i]) {
            pri[++cnt] = i;
            vis[i] = i;
        }
        for (int j = 1; j <= cnt && i * pri[j] <= N; ++j) {
            vis[i * pri[j]] = pri[j];
            if (i % pri[j - 1]) {
                continue;
            }
        }
    }
    scanf("%d %d", &n, &m);
    if (n < m) {
        std::swap(n, m);
    }
    for (int i = 1; i <= m; ++i) {
        plus(n - i + 1);
        less(i);
    }
    for (int i = 1; i <= cnt; ++i) {
        for (int j = 0; j < ms[pri[i]]; ++j) {
            ans *= pri[i];
            if (ans.length() > 50) {
                ans.makelen(50);
                ans.zero();
            }
        }
    }
    std::cout << ans << std::endl;
    return 0;
}
inline void plus(int x) {
    while (x != 1) {
        ++ms[vis[x]];
        x /= vis[x];
    }
}
inline void less(int x) {
    while (x != 1) {
        --ms[vis[x]];
        x /= vis[x];
    }
}