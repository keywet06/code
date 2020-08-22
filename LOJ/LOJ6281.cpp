#include <bits/stdc++.h>
const int C = 5;
const int N = 60000;
const int S = 225;
int n, opt, l, r, c, k;
long long ans;
long long s[N];
long long a[C][N];
long long sum[C][S];
inline int id(int x) { return x / S; }
inline int begins(int x) { return id(x) * S; }
inline int ends(int x) { return id(x) * S + S; }
inline void move(int l, int r) {
    for (int i = 0; i < C - 1; ++i) {
        for (int j = l; j <= r; ++j) {
            sum[i][id(l)] += a[i + 1][j] - a[i][j];
            a[i][j] = a[i + 1][j];
        }
    }
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[0][i];
        sum[0][id(i)] += a[0][i];
        for (int j = 1; j < C; ++j) {
            sum[j][id(i)] += a[j][i] = int(sqrt(a[j - 1][i]));
        }
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> opt >> l >> r >> c;
        --l, --r;
        if (opt == 0) {
            if (id(l) == id(r)) {
                move(l, r);
                continue;
            }
            move(l, ends(l) - 1);
            move(begins(r), r);
            for (int i = id(l) + 1; i < id(r); ++i) {
                s[i] = s[i] + (s[i] < C - 1);
            }
        } else {
            ans = 0;
            if (id(l) == id(r)) {
                for (int i = l; i <= r; ++i) ans += a[s[id(l)]][i];
                std::cout << ans << '\n';
                continue;
            }
            for (int i = l; i < ends(l); ++i) ans += a[s[id(l)]][i];
            for (int i = begins(r); i <= r; ++i) ans += a[s[id(r)]][i];
            for (int i = id(l) + 1; i < id(r); ++i) ans += sum[s[i]][i];
            std::cout << ans << '\n';
        }
    }
    return 0;
}