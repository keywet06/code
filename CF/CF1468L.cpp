#include <bits/stdc++.h>

#define fi first
#define se second
#define mkp std::make_pair
#define pub push_back

using int64 = long long;
using int128 = __int128;

using pi56 = std::pair<int, int64>;

const int N = 1005;
const int X = 1e6 + 5;
const int Y = 1e9 + 5;
const int MI = 8;
const int Millers[MI] = {2, 3, 5, 7, 11, 13, 17, 19};
const int64 Z = 1e18 + 5;

bool is[N];

int n, k, pcnt, acnt, cnt, dc, fr, hr, scnt;
int vis[X], pri[X];

int64 x, y, z;
int64 a[N], at[N], ans[N], cp[N];

pi56 st[N];

std::map<int64, int> map;

std::map<int64, std::vector<int64> > vep;

int128 power(int128 x, int64 y, const int64 P) {
    return y ? (y & 1 ? power(x * x % P, y >> 1, P) * x % P
                      : power(x * x % P, y >> 1, P))
             : 1;
}

inline bool MillerRobinTest(int64 x, int64 y) {
    int64 t = y - 1;
    int128 c;
    while (!(t & 1)) t >>= 1;
    if ((c = power(c, t, y)) == 1) return true;
    for (t; t >> 1 < y; t <<= 1) {
        if (c == 1) return false;
        if (c == y - 1) return false;
        c = c * c % y;
    }
    return false;
}

inline bool MillerRobin(int64 x) {
    if (x < X) return !vis[x];
    for (int i = 0; i < MI; ++i) {
        if (!MillerRobinTest(Millers[i], x)) return false;
    }
    return true;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    for (int i = 2; i < X; ++i) {
        if (!vis[i]) pri[++pcnt] = i;
        for (int j = 1; j <= pcnt, i * pri[j] < X; ++j) {
            vis[i * pri[j]] = 1;
            if (i % pri[j] == 0) break;
        }
    }
    std::cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        if (is[i] = MillerRobin(cp[i] = a[i])) continue;
        int64 l = 1, r = X, mid;
        while (l < r) {
            mid = l + r >> 1;
            if (mid * mid < a[i]) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        if (l * l == a[i] && (is[i] = MillerRobin(cp[i] = l))) continue;
        for (int j = 1; j <= pcnt, pri[j] * pri[j] * pri[j] <= a[i]; ++j) {
            if ((x = a[i]) % pri[j]) continue;
            while (!(x % pri[j])) x /= pri[j];
            cp[i] = pri[j], is[i] = x == 1;
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (is[i]) ++map[cp[i]], vep[cp[i]].pub(a[i]);
    }
    for (auto p : map) {
        if (p.se > 1) at[++acnt] = p.fi, fr += p.se, hr = std::max(hr, p.se);
    }
    if (fr >= k) {
        if (k & 1 && hr == 2) {
            for (int i = 1; i <= n; ++i) {
                if (is[i]) continue;
                x = a[i], y = 0;
                for (int j = 1; j <= dc; ++j) {
                    y += !(x % at[j]);
                    while (!(x % at[j])) x /= at[j];
                }
                if (x == 1 && y << 1 < k) {
                    std::cout << a[i] << ' ', --k;
                    for (int j = 1; j <= dc; ++j) {
                        if (!(a[i] % at[j])) {
                            std::cout << vep[at[j]][0] << ' ' << vep[at[j]][1]
                                      << ' ';
                            map[at[j]] = 0, ----k;
                        }
                    }
                    for (auto p : map) {
                        if (k && p.se > 1) {
                            std::cout << vep[p.fi][0] << ' ' << vep[p.fi][1]
                                      << ' ';
                            ----k;
                        }
                    }
                    std::cout << '\n';
                    return 0;
                }
            }
            std::cout << 0 << '\n';
            return 0;
        }
        for (auto p : map) {
            if (p.se > 1) st[++scnt] = mkp(p.se, p.fi);
        }
        std::sort(st + 1, st + scnt + 1,
                  [](pi56 x, pi56 y) { return x.fi > y.fi; });
        for (int i = 1; i <= scnt; ++i) {
            for (int j = 0; j < st[i].fi; ++j) {
                ans[++cnt] = vep[st[i].se][j];
                if (!--k) {
                    if (!j) ans[1] = vep[st[i].se][1];
                    break;
                }
            }
            if (!k) break;
        }
        for (int i = 1; i <= cnt; ++i) std::cout << ans[i] << " \n"[i == cnt];
        return 0;
    }
    for (int i = 1; i <= n; ++i) {
        x = a[i];
        for (int j = 1; j <= dc; ++j) {
            while (!(x % at[j])) x /= at[j];
        }
        if (x == 1) ans[++cnt] = a[i];
    }
    if (cnt < k) return std::cout << 0 << '\n', 0;
    for (int i = 1; i <= k; ++i) std::cout << ans[i] << " \n"[i == k];
    return 0;
}
