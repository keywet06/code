#include <bits/stdc++.h>

#define mkp std::make_pair

using int32 = int;
using i5 = int32;
using pi5 = std::pair<i5, i5>;

namespace oct {

void ios() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
}

}  // namespace oct

const int N = 1010005;
const int M = N << 2;

char str[N];

int n, a, b, p, m, lt;

pi5 ls[M];

void create(int l, int r) {
    ls[++lt] = l <= r ? mkp(l, r) : (ls[++lt] = mkp(l, n - 1), mkp(0, r));
}

int main() {
    std::cin >> n >> a >> b >> p >> m >> str;
    int ans = 0;
    for (int i = 0; i < m; i++)
        if (str[i] == '0') {
            create((p + n - 1ll * i * a % n) % n,
                   (0ll + n - 1 - 1ll * i * a % n) % n);
        } else {
            create((n - 1ll * i * a % n) % n,
                   (p + n - 1ll * i * a % n - 1) % n);
        }
    for (int i = 1; i < m; i++) {
        create((0ll + b + n - 1ll * a * i % n) % n,
               (0ll + b + n - 1ll * a * i % n) % n);
    }
    std::sort(ls + 1, ls + 1 + lt);
    int tmp = -1;
    for (int i = 1; i <= lt; i++) {
        if (ls[i].first > tmp) {
            ans += ls[i].first - tmp - 1, tmp = ls[i].second;
        } else {
            tmp = std::max(tmp, ls[i].second);
        }
    }
    std::cout << ans + n - 1 - tmp << std::endl;
    return 0;
}