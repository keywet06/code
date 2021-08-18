#include <bits/stdc++.h>

using int64 = long long;

const int N = 2505;

int n, pl, pr;
int x[N], y[N], d[N], s[N];

int64 ans;

void add(int x) {
    ++x;
    while (x < N) ++s[x], x = x + (x & -x);
}
int sum(int x) {
    int ret = (++x, 0);
    while (x) ret += s[x], x &= x - 1;
    return ret;
}

int main() {
    std::cin >> n;
    for (int i = 0; i < n; ++i) std::cin >> x[i] >> y[i], d[i] = i;
    std::sort(d, d + n, [](int a, int b) { return y[a] < y[b]; });
    for (int i = 0; i < n; ++i) y[d[i]] = i;
    std::sort(d, d + n, [](int a, int b) { return x[a] < x[b]; });
    for (int l = 0; l < n; ++l) {
        memset(s, 0, sizeof(s));
        for (int r = l; r < n; ++r) {
            add(y[d[r]]);
            pl = std::min(y[d[l]], y[d[r]]), pr = std::max(y[d[l]], y[d[r]]);
            ans += sum(pl) * (r - l + 1 - sum(pr - 1));
        }
    }
    std::cout << ans + 1 << std::endl;
    return 0;
}