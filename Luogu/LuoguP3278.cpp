#include <bits/stdc++.h>

using int64 = long long;

const int C = 450;
const int N = 202500;
const int M = N << 1;
const int P = 20130426;

int n, l, r, v, c;

int64 ps[C], ms[C], us[C];
int64 dt[N], mu[N];
int64 pe[M];

std::string s;

inline int gid(int x) { return x / C; }
inline int cbe(int x) { return (x - 1) * C; }
inline int cen(int x) { return x * C; }
inline int gbe(int x) { return cbe(gid(x)); }
inline int gen(int x) { return cen(gid(x)); }

inline void pushdown(int x) {
    for (int i = cbe(x); i < cen(x); ++i) {
        dt[i] = (dt[i] * ms[x] + ps[x]) % P;
        mu[i] = mu[i] + us[x];
    }
    ps[x] = us[x] = 0, ms[x] = 1;
}

inline int64 power(int x) {
    if (x <= c) return pe[x];
    while (c < x) ++c, pe[c] = pe[c - 1] * v % P;
    return pe[x];
}

inline void plus(int l, int r, int v) {
    for (int i = l; i < r; ++i) dt[i] = (dt[i] + v) % P;
}

inline void mul(int l, int r, int v) {
    for (int i = l; i < r; ++i) dt[i] = dt[i] * v % P;
}

inline void pin(int l, int r) {
    dt[r] += dt[r - 1];
    for (int i = r - 1; i > l; --i) {
        dt[i] = dt[i - 1];
    }
    dt[l] = 0;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int i = 0; i < N; ++i) mu[i] = i;
    for (int i = 1; i <= n; ++i) {
        std::cin >> s;
        if (s[i] == 'm' && s.length() == 3) {
            std::cin >> l >> r >> v;
            pushdown(l), pushdown(r);
            
        }
    }
    return 0;
}