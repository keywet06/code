#include <bits/stdc++.h>
const int N = 60000;
const int S = 225;
int n, l, r, opt, ans;
long long c;
long long a[N], s[N], plus[N];
<<<<<<< HEAD
=======
inline int id(int x) { return x / S; }
inline int begins(int x) { return id(x) * S; }
inline int ends(int x) { return id(x) * S + S; }
>>>>>>> 406ef0d98a484a2613e66fd396bfc311917cd6ec
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
<<<<<<< HEAD
            if (l / S == r / S) {
                for (int i = l; i <= r; ++i) a[i] += c;
                memcpy(s + l / S * S, a + l / S * S, S << 3);
                std::sort(s + l / S * S, s + l / S * S + S);
                continue;
            }
            for (int i = l; i < l / S * S + S; ++i) a[i] += c;
            for (int i = r / S * S; i <= r; ++i) a[i] += c;
            memcpy(s + l / S * S, a + l / S * S, S << 3);
            memcpy(s + r / S * S, a + r / S * S, S << 3);
            std::sort(s + l / S * S, s + l / S * S + S);
            std::sort(s + r / S * S, s + r / S * S + S);
            for (int i = l / S + 1; i < r / S; ++i) plus[i] += c;
        } else {
            c *= c;
            ans = 0;
            if (l / S == r / S) {
                for (int i = l; i <= r; ++i) ans += a[i] < c;
                std::cout << ans << '\n';
                continue;
            }
            for (int i = l; i < l / S * S + S; ++i) ans += a[i] < c;
            for (int i = r / S * S; i <= r; ++i) ans += a[i] < c;
=======
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
>>>>>>> 406ef0d98a484a2613e66fd396bfc311917cd6ec
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
