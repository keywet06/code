#include <bits/stdc++.h>

const int N = 1 << 20 | 5;
const int M = 1 << 21 | 5;

int q, flag, o, x, num, ret, cnt, c1, c2, c3;
int po[N], px[N], is[N], vis[N], a1[N], a2[N], a3[N], a[N];
int size[M];

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> q;
    for (int i = 1; i <= q; ++i) std::cin >> po[i] >> px[i], flag |= po[i] == 2;
    if (flag) {
        for (int _ = 1; o = po[_], x = px[_], _ <= q; ++_) {
            if (o == 1) {
                if (is[x]) continue;
                a[++cnt] = x;
            } else {
                if (vis[x] != cnt) {
                    vis[x] = cnt, c1 = c2 = c3 = 0;
                    for (int i = 1; i <= cnt; ++i) {
                        c1 = std::max(c1, x ^ a[i]);
                        c2 = std::max(c2, x & a[i]);
                        c3 = std::max(c3, x | a[i]);
                    }
                    a1[x] = c1, a2[x] = c2, a3[x] = c3;
                }
                std::cout << a1[x];
                if (o == 2) std::cout << ' ' << a2[x] << ' ' << a3[x];
                std::cout << '\n';
            }
        }
    } else {
        for (int _ = 1; o = po[_], x = px[_], _ <= q; ++_) {
            if (o == 1) {
                ++size[c1 = 1];
                for (int i = 19; i >= 0; --i) {
                    ++size[c1 = c1 << 1 | bool(x & (1 << i))];
                }
            } else {
                c1 = 1, c3 = 0;
                for (int i = 19; i >= 0; --i) {
                    c2 = bool(x & (1 << i));
                    if (size[c1 << 1 | !c2]) {
                        c1 = c1 << 1 | !c2;
                        c3 |= 1 << i;
                    } else {
                        c1 = c1 << 1 | c2;
                    }
                }
                std::cout << c3 << '\n';
            }
        }
    }
    return 0;
}