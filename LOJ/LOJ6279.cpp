#include <bits/stdc++.h>
const int N = 150000;
const int S = 320;
int n, l, r, opt;
long long c, ans;
long long a[N], s[N], plus[N];
inline int id(int x) { return x / S; }
inline int begins(int x) { return id(x) * S; }
inline int ends(int x) { return id(x) * S + S; }
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    memset(a, 127, sizeof(a));
    std::cin >> n;
    for (int i = 0; i < n; ++i) std::cin >> a[i], s[i] = a[i];
    for (int i = 0; i < S; ++i) std::sort(s + i * S, s + i * S + S);
    for (int i = 0; i < n; ++i) {
        std::cin >> opt >> l >> r >> c;
        --l, --r;
        if (opt == 0) {
            if (id(l) == id(r)) {
                for (int i = l; i <= r; ++i) a[i] += c;
                memcpy(s + begins(l), a + begins(l), S << 3);
                std::sort(s + begins(l), s + ends(l));
                continue;
            }
            for (int i = l; i < ends(l); ++i) a[i] += c;
            for (int i = begins(r); i <= r; ++i) a[i] += c;
            memcpy(s + begins(l), a + begins(l), S << 3);
            memcpy(s + begins(r), a + begins(r), S << 3);
            std::sort(s + begins(l), s + ends(l));
            std::sort(s + begins(r), s + ends(r));
            for (int i = id(l) + 1; i < id(r); ++i) plus[i] += c;
        } else {
            ans = -1;
            if (id(l) == id(r)) {
                for (int i = l; i <= r; ++i) {
                    if (a[i] + plus[id(l)] < c) {
                        ans = std::max(ans, a[i] + plus[id(l)]);
                    }
                }
                std::cout << ans << '\n';
                continue;
            }
            for (int i = l; i < ends(l); ++i) {
                if (a[i] + plus[id(l)] < c) {
                    ans = std::max(ans, a[i] + plus[id(l)]);
                }
            }
            for (int i = begins(r); i <= r; ++i) {
                if (a[i] + plus[id(r)] < c) {
                    ans = std::max(ans, a[i] + plus[id(r)]);
                }
            }
            for (int i = l / S + 1; i < r / S; ++i) {
                int l = i * S, r = i * S + S - 1, mid;
                c -= plus[i];
                while (l < r) {
                    mid = l + r + 1 >> 1;
                    if (s[mid] < c) {
                        l = mid;
                    } else {
                        r = mid - 1;
                    }
                }
                if (s[l] >= c) {
                    c += plus[i];
                    continue;
                }
                c += plus[i];
                ans = std::max(ans, s[l] + plus[i]);
            }
            std::cout << ans << '\n';
        }
    }
    return 0;
}