#include <bits/stdc++.h>
#include "Fraction.hpp"
const int N = 500005;
int i, l, m, n, now, r, tmp, x, y;
int ans[N], bigest[N], left[N], right[N], smallest[N];
void build(int, int, int);
void update(int);
int main() {
    scanf("%d %d", &n, &m);
    build(1, 1, n);
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d", &x, &y);
        l = 1;
        r = n;
        now = 1;
        while (l < r) {
            if (x<(l + r)>> 1) {
                r = (l + r) >> 1;
                now = now << 1;
            } else {
                l = (l + r) >> 1 + 1;
                now = now << 1 | 1;
            }
        }
        tmp = now;
        if (y < bigest[now]) {
            bigest[now] = smallest[now] = y;
            if (ans[now]) {
                for (now = tmp; now != 1; now >>= 1) {
                    if (now & 1 && bigest[now ^ 1] > y) {
                        ans[tmp] = 0;
                        break;
                    }
                }
                for (now = tmp >> 1; now != 1; now >>= 1) {
                    update(now);
                }
                for (now = tmp; now != 1; now >>= 1) {
                    if (!(now & 1) && ans[now ^ 1] && bigest[tmp] > smallest[now ^ 1]) {
                        i = now ^ 1;
                        l = left[i];
                        r = right[i];
                        while (l < r) {
                            i = i << 1 + !ans[i << 1];
                        }
                    }
                }
            }
        }
    }
    return 0;
}
inline void update(int now) {
    bigest[now] = std::max(bigest[now << 1], bigest[now << 1 | 1]);
    smallest[now] = INT_MAX;
    if (ans[now << 1]) {
        smallest[now] = std::min(smallest[now], smallest[now << 1]);
    }
    if (ans[now << 1 | 1]) {
        smallest[now] = std::min(smallest[now], smallest[now << 1 | 1]);
    }
    if (smallest[now] == INT_MAX) {
        smallest[now] = std::min(smallest[now << 1], smallest[now << 1 | 1]);
    }
    ans[now] = ans[now << 1] + ans[now << 1 | 1];
}