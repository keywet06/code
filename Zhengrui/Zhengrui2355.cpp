#include <bits/stdc++.h>

using int64 = long long;

namespace FastIO {

const int T = 1 << 15;
char buf[T], *p1 = buf, *p2 = buf;
inline char FastReadChar() { return p1 == p2 && (p2 = buf + fread(p1 = buf, 1, T, stdin), p1 == p2) ? -1 : *p1++; }

int64 Read() {
    int64 x = 0;
    char c;
    bool s = 0;
    do c = FastReadChar();
    while (c != 45 && (c < 48 || c > 57));
    if (c == 45) c = FastReadChar(), s = 1;
    do x = 10 * x + (c & 15), c = FastReadChar();
    while (c >= 48 && c <= 57);
    return s ? -x : x;
}

};  // namespace FastIO

const int N = 2000005;

const int64 INF = 1e18;

int64 n, q, r, Ans = 0;
int64 h[N], e[N], Id[N], f[N];
int64 g[N << 2], *p = g;

struct Fen {
    int64 n, *c;
    inline void Init() { c = p, p += n, std::fill(c + 1, c + n + 1, -INF); }
    inline void Add(int x, int64 y) {
        for (int i = x; i <= n; i += i & -i) c[i] = std::max(c[i], y);
    }
    inline int64 Query(int x) {
        int64 Ret = -INF;
        for (int i = x; i; i &= i - 1) Ret = std::max(Ret, c[i]);
        return Ret;
    }
};

Fen t[N], Fe;

inline void Add(int u, int d, int64 c) {
    for (int i = u + 1; i <= r; i += i & -i) t[i - 1].Add(d, c);
}

inline int64 Query(int d, int64 c) {
    int64 Ans = -INF;
    if (d < 0) return -INF;
    for (int i = d + 1; i; i &= i - 1) Ans = std::max(t[i - 1].Query(c), Ans);
    return Ans;
}

int main() {
    n = FastIO::Read(), r = FastIO::Read(), q = FastIO::Read();
    for (int i = 1; i <= n; ++i) h[i] = FastIO::Read(), Id[i] = i / r + 1;
    for (int i = 1; i < n; ++i) e[i] = FastIO::Read();
    Fe.n = n, Fe.Init();
    for (int i = 0; i < r; ++i) t[i].n = Id[n], t[i].Init();
    for (int i = n; i >= 1; --i) {
        if (i != n) {
            f[i] = std::max(Fe.Query(i + e[i]), std::max(Query(std::min(i % r - 1, (i + e[i]) % r), Id[i + e[i]]),
                            Query(i % r - 1, Id[i + e[i]] - 1)) + q) + i / r * q;
        }
        f[i] += h[i], Ans = Ans ^ (f[i] + i);
        int64 TmpAdd = f[i] - i / r * q;
        Add(i % r, Id[i], TmpAdd), Fe.Add(i, TmpAdd);
    }
    std::cout << Ans << '\n';
    return 0;
}