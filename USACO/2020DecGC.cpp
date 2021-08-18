#include <bits/stdc++.h>

using int64 = long long;

const int N = 205;

int n, c;

int64 e, d, ans, up, dn, ul, ur, dl, dr, el, er;
int64 x[N], y[N], p[N], q[N], pa[N];

void change(int pl, int pr) {
    while (q[el + 1] <= pl) ++el;
    while (q[er] <= pr) ++er;
}

int main() {
    std::cin >> n;
    for (int i = 0; i < n; ++i) std::cin >> x[i] >> y[i], p[i] = i;
    std::sort(p, p + n, [](int a, int b) { return x[a] < x[b]; });
    for (int l = 0; l < n; ++l) {
        for (int r = l; r < n; ++r) {
            up = std::min(y[p[l]], y[p[r]]), dn = std::max(y[p[l]], y[p[r]]);
            e = x[p[r]] - x[p[l]], d = dn - up;
            if (e < d) continue;
            q[c = 0] = -10000000000ll;
            for (int i = l; i <= r; ++i) q[++c] = y[p[i]];
            q[c + 1] = 10000000000ll;
            std::sort(q + 1, q + c + 1);
            ul = ur = dl = dr = 0;
            for (int i = 1; i <= c; ++i) {
                if (!ul && q[i] + e >= dn && q[i] <= up) ul = i;
                if (q[i] == up) ur = i;
                if (q[i] == dn) dl = i;
                if (q[i] - e <= up && q[i] >= dn) dr = i;
            }
            el = er = dl;
            for (int i = ul; i <= ur; ++i) {
                change(q[i - 1] + 1 + e, q[i] + e);
                ans += er - el;
            }
        }
    }
    for (int i = 0; i < n; ++i) std::swap(x[i], y[i]);
    std::sort(p, p + n, [](int a, int b) { return x[a] < x[b]; });
    for (int l = 0; l < n; ++l) {
        for (int r = l; r < n; ++r) {
            up = std::min(y[p[l]], y[p[r]]), dn = std::max(y[p[l]], y[p[r]]);
            e = x[p[r]] - x[p[l]], d = dn - up;
            if (e < d) continue;
            c = 0, q[0] = -10000000000ll;
            for (int i = l; i <= r; ++i) q[++c] = y[p[i]];
            q[c + 1] = 10000000000ll;
            std::sort(q + 1, q + c + 1);
            ul = ur = dl = dr = 0;
            for (int i = 1; i <= c; ++i) {
                if (!ul && q[i] + e >= dn && q[i] <= up) ul = i;
                if (q[i] == up) ur = i;
                if (q[i] == dn) dl = i;
                if (q[i] - e <= up && q[i] >= dn) dr = i;
            }
            el = er = dl;
            for (int i = ul; i <= ur; ++i) {
                change(q[i - 1] + 1 + e, q[i] + e - 1);
                ans += er - el;
            }
        }
    }
    std::cout << ans + 1 << std::endl;
    return 0;
}