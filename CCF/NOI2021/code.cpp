#include <bits/stdc++.h>

using int64 = long long;

const int P = 998244353;
const int N = 200005;

int n, q, l, r, c;
int a[N], b[N];

int64 x, y;

std::string s;

inline void solve() {
    c = 1, b[0] = 0, b[1] = 1;
    for (int i = 1; i <= n; ++i) {
        if (a[i]) {
            b[c] == 1 ? ++b[c - 1] : (--b[c], b[++c] = 1, b[++c] = 1);
        } else {
            ++b[c];
        }
    }
    x = 1, y = 0;
    for (int i = c; ~i; --i) {
        std::swap(x, y);
        x = (x + y * b[i]) % P;
    }
    std::cout << x << ' ' << y << '\n';
}

int main() {
    freopen("code.in", "r", stdin);
    freopen("code.out", "w", stdout);
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> q;
    std::cin >> s;
    for (int i = 0; i < n; ++i) a[i + 1] = s[i] == 'E';
    solve();
    while (q--) {
        std::cin >> s;
        if (s[0] == 'A') {
            std::cin >> s;
            a[++n] = s[0] == 'E';
        } else if (s[0] == 'F') {
            std::cin >> l >> r;
            for (int i = l; i <= r; ++i) a[i] ^= 1;
        } else {
            std::cin >> l >> r;
            for (int i = 0; i << 1 < r - l; ++i) std::swap(a[l + i], a[r - i]);
        }
        solve();
    }
    return 0;
}