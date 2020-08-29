#include <bits/stdc++.h>
using int64 = long long;
using pint64 = std::pair<int64, int64>;
const int C = 60;
const int N = 250;
const int M = 20000;
const int mod = 1000000007;
struct node {
    int k;
    int64 v;
    int64 a[N];
};
int n, cnt, num;
int64 k;
int64 a[N], c[N], d[N];
pint64 que[M];
node s[M];
inline int operator<(node x, node y) {
    for (int i = 1; i <= n; ++i) {
        if (x.a[i] != y.a[i]) return x.a[i] < y.a[i];
    }
    return 0;
}
inline int operator==(node x, node y) {
    for (int i = 1; i <= n; ++i) {
        if (x.a[i] != y.a[i]) return 0;
    }
    return 1;
}
inline int get(int64 x, int64 y) {
    if (x == -1) return 0;
    int tmp = 0;
    for (int i = C; ~i; --i) {
        if ((x >> i) & 1 == (y >> i) & 1) {
            tmp += (x >> i) & 1;
        } else {
            return ++tmp;
        }
    }
    return tmp;
}
inline int64 dp() {
    std::sort(que + 1, que + num + 1);
    int64 ans = 0, l = 0, r = -1;
    for (int i = 1; i <= num; ++i) {
        if (que[i].first > r) {
            ans += r - l + 1;
            l = que[i].first;
        }
        r = que[i].second;
    }
    return ans + r - l + 1;
}
int main() {
    std::cin >> n >> k;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    std::sort(a + 1, a + n + 1);
    for (int i = 1; i <= C; ++i) {
        for (int j = 1; j <= n; ++j) c[j] = a[j] & ((1ll << i) - 1);
        std::sort(c + 1, c + n + 1);
        c[0] = -1;
        int size = std::unique(c + 1, c + n + 1) - c - 1;
        for (int j = 1; j <= size; j++) {
            if (a[1] >= c[j]) {
                int P = get(c[j - 1], c[j]);
                for (int l = 1; l <= n; l++) d[l] = (a[l] - c[j]) >> i;
                s[++cnt].v = d[1];
                s[cnt].k = i + P;
                for (int l = 1; l < n; l++) s[cnt].a[l] = d[l + 1] - d[l];
            }
        }
    }
    std::sort(s + 1, s + cnt + 1);
    num = 0;
    int64 ans = 0;
    for (int i = 1; i <= cnt; i++) {
        if (i != 1 && !(s[i] == s[i - 1])) ans = (ans + dp()) % mod, num = 0;
        if (s[i].k > k) continue;
        que[++num] = std::make_pair(std::max(s[i].v - k + s[i].k, 0ll), s[i].v);
    }
    ans = (ans + dp()) % mod;
    std::cout << ans << std::endl;
    return 0;
}