#include <bits/stdc++.h>

const int C = 10;
const int N = 100005;

int n, m, ans, id1, id2, id3, id4, f;
int a[C], b[C], ra[C], rb[C];
int pa[N], pb[N], ca[N], cb[N];

std::string sa, sb;

inline void check(int x, int y) {
    memcpy(ra, a, sizeof(a));
    memcpy(rb, b, sizeof(b));
    --ra[x], --rb[y];
    int i = 1, j = 8, s = 1, t;
    while (i < C) {
        for (int k = j, x; k <= 9; ++k) {
            t = std::min(ra[i], rb[j]);
            s += t, ra[i] -= t, rb[j] -= t;
        }
        ++i, --j;
    }
    if (s > ans) ans = s, id1 = x, id2 = y;
}

inline void getans(int x, int y) {
    memcpy(ra, a, sizeof(a));
    memcpy(rb, b, sizeof(b));
    --ra[x], --rb[y], ca[1] = x, cb[1] = y;
    int i = 1, j = 8, s = 1, c = 1, d, t;
    while (i < C) {
        for (int k = j, x; k <= 9; ++k) {
            t = std::min(ra[i], rb[k]);
            s += t, ra[i] -= t, rb[k] -= t;
            while (t--) ++c, ca[c] = i, cb[c] = k;
        }
        ++i, --j;
    }
    d = c;
    for (int i = 1; i < C; ++i) {
        while (ra[i]--) ca[++c] = i;
        while (rb[i]--) cb[++d] = i;
    }
    for (int i = n; i; --i) std::cout << ca[i];
    std::cout << std::endl;
    for (int i = n; i; --i) std::cout << cb[i];
    std::cout << std::endl;
}

inline void check(int x, int y, int z, int w) {
    memcpy(ra, a, sizeof(a));
    memcpy(rb, b, sizeof(b));
    if (x + y < 10) return;
    if (--ra[x] < 0) return;
    if (--rb[y] < 0) return;
    if (--ra[z] < 0) return;
    if (--rb[w] < 0) return;
    int i = 1, j = 8, t, s = 1;
    while (i < C) {
        for (int k = j, x; k <= 9; ++k) {
            t = std::min(ra[i], rb[j]);
            s += t, ra[i] -= t, rb[j] -= t;
        }
        ++i, --j;
    }
    if (z + w > 9 || s == n - 1 && z + w == 9) {
        ++s, t = std::min(m - n, rb[9]);
        rb[9] -= t, s += t;
    }
    if (s > ans) ans = s, id1 = x, id2 = y, id3 = z, id4 = w;
}

inline void getans(int x, int y, int z, int w) {
    memcpy(ra, a, sizeof(a));
    memcpy(rb, b, sizeof(b));
    if (x + y < 10) return;
    if (--ra[x] < 0) return;
    if (--rb[y] < 0) return;
    if (--ra[z] < 0) return;
    if (--rb[w] < 0) return;
    std::cout << x << ' ' << y << ' ' << z << ' ' << w << std::endl;
    ca[1] = x, cb[1] = y, ca[n] = z, cb[n] = w;
    int i = 1, j = 8, t, s = 1, c = 1, d, p = n;
    while (i < C) {
        for (int k = j, x; k <= 9; ++k) {
            t = std::min(ra[i], rb[j]);
            s += t, ra[i] -= t, rb[j] -= t;
            while (t--) ++c, ca[c] = i, cb[c] = k;
        }
        ++i, --j;
    }
    if (z + w > 9 || s == n - 1 && z + w == 9) {
        t = std::min(m - n, rb[9]);
        rb[9] -= t, s += t;
        for (int i = 1; i <= t; ++i) cb[n + i] = 9;
        p = n + t;
    }
    d = c;
    for (int i = 1; i < C; ++i) {
        while (ra[i]--) ca[++c] = i;
    }
    for (int i = 1; i < C; ++i) {
        while (d < c && rb[i]--) cb[++d] = i;
    }
    for (int i = 1; i < C; ++i) {
        while (rb[i]-- > 0) cb[++p] = i;
    }
    if (f) {
        for (int i = m; i; --i) std::cout << cb[i];
        std::cout << std::endl;
        for (int i = n; i; --i) std::cout << ca[i];
        std::cout << std::endl;
    } else {
        for (int i = n; i; --i) std::cout << ca[i];
        std::cout << std::endl;
        for (int i = m; i; --i) std::cout << cb[i];
        std::cout << std::endl;
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> sa >> sb;
    for (char ch : sa) ++a[ch - '0'];
    for (char ch : sb) ++b[ch - '0'];
    if (sa.size() == sb.size()) {
        n = sa.size();
        for (int i = 1; i <= 9; ++i) {
            for (int j = 10 - i; j <= 9; ++j) {
                if (!a[i] || !b[j]) continue;
                check(i, j);
                break;
            }
        }
        if (!ans) return std::cout << sa << '\n' << sb << '\n', 0;
        getans(id1, id2);
    } else {
        if (sa.size() > sb.size()) sa.swap(sb), f = 1;
        n = sa.size(), m = sb.size();
        for (int i = 1; i <= 9; ++i) {
            for (int j = 1; j <= 9; ++j) {
                for (int k = 1; k <= 9; ++k) {
                    for (int l = 1; l <= 9; ++l) {
                        check(i, j, k, l);
                    }
                }
            }
        }
        if (!ans) {
            if (f) {
                std::cout << sb << '\n' << sa << '\n';
            } else {
                std::cout << sa << '\n' << sb << '\n';
            }
            return 0;
        }
        getans(id1, id2, id3, id4);
    }
    return 0;
}