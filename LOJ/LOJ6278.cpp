#include <bits/stdc++.h>
const int N = 60000;
const int S = 225;
int n, l, r, opt, ans;
long long c;
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
            c *= c;
            ans = 0;
            if (id(l) == id(r)) {
                for (int i = l; i <= r; ++i) ans += a[i] + plus[id(l)] < c;
                std::cout << ans << '\n';
                continue;
            }
            for (int i = l; i < ends(l); ++i) ans += a[i] + plus[id(l)] < c;
            for (int i = begins(r); i <= r; ++i) ans += a[i] + plus[id(r)] < c;
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
                if (s[l] >= c) --l;
                c += plus[i];
                ans += l - i * S + 1;
            }
            std::cout << ans << '\n';
        }
    }
    return 0;
}