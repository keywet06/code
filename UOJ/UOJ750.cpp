#include <bits/stdc++.h>

using int64 = long long;

const int N = 40;
const int M = 1 << 20;

int n, na, nb;
int la, ra, lb, rb;

int64 p;

inline int64 Add(int64 x, int64 y) { return (x += y) >= p ? x - p : x; }
inline int64 Sub(int64 x, int64 y) { return (x -= y) < 0 ? x + p : x; }

int64 a[N];
int64 Ca[M], Cb[M], Da[M], Db[M];
int pa[M], pb[M];

inline int Print(int a1, int b1, int a2, int b2) {
    a1 = pa[a1], a2 = pa[a2], b1 = pb[b1], b2 = pb[b2];
    for (int i = 0; i < ra - la; ++i) std::cout << ((a1 >> i) & 1) - ((a2 >> i) & 1) << ' ';
    for (int i = 0; i < rb - lb; ++i) std::cout << ((b1 >> i) & 1) - ((b2 >> i) & 1) << " \n"[i == rb - lb - 1];
    int64 Ans = 0;
    for (int i = 0; i < ra - la; ++i) Ans = Add(Ans, ((a1 >> i) & 1) * a[i + la]);
    for (int i = 0; i < ra - la; ++i) Ans = Sub(Ans, ((a2 >> i) & 1) * a[i + la]);
    for (int i = 0; i < rb - lb; ++i) Ans = Add(Ans, ((b1 >> i) & 1) * a[i + lb]);
    for (int i = 0; i < rb - lb; ++i) Ans = Sub(Ans, ((b2 >> i) & 1) * a[i + lb]);
    assert(Ans == 0);
    return 0;
}

std::mt19937_64 Rand(std::chrono::system_clock::now().time_since_epoch().count());

inline int64 Query(int64 l, int64 r) {
    int tl = -1, tr = -1;
    int64 Ans = 0;
    for (int i = na - 1; i >= 0; --i) {
        while (tl + 1 < nb && Da[i] + Db[tl + 1] < l) ++tl;
        while (tr + 1 < nb && Da[i] + Db[tr + 1] <= r) ++tr;
        Ans += tr - tl;
    }
    return Ans;
}

inline int64 Queryp(int64 l, int64 r) { return Query(l, r) + Query(l + p, r + p); }

inline int64 Solve(int64 l, int64 r) {
    if (l == r) return l;
    int64 Mid = l + r >> 1;
    return Queryp(l, Mid) > Mid - l + 1 ? Solve(l, Mid) : Solve(Mid + 1, r);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> p;
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    la = 0, ra = n + 1 >> 1, lb = ra, rb = n, na = 1 << ra - la, nb = 1 << rb - lb;
    for (int i = 0; i < ra - la; ++i) {
        int64 x = a[la + i];
        int c = 1 << i;
        for (int j = 0; j < c; ++j) Ca[j | c] = Add(Ca[j], x);
    }
    for (int i = 0; i < rb - lb; ++i) {
        int64 x = a[lb + i];
        int c = 1 << i;
        for (int j = 0; j < c; ++j) Cb[j | c] = Add(Cb[j], x);
    }
    for (int i = 0; i < 1 << ra - la; ++i) pa[i] = i;
    for (int i = 0; i < 1 << rb - lb; ++i) pb[i] = i;
    std::sort(pa, pa + (1 << ra - la), [](int x, int y) { return Ca[x] < Ca[y]; });
    std::sort(pb, pb + (1 << rb - lb), [](int x, int y) { return Cb[x] < Cb[y]; });
    for (int i = 0; i < 1 << ra - la; ++i) Da[i] = Ca[pa[i]];
    for (int i = 0; i < 1 << rb - lb; ++i) Db[i] = Cb[pb[i]];
    int64 c = Solve(0, p - 1);
    int tl = -1, tr = -1, Flag = false, ca1, cb1;
    for (int i = na - 1; i >= 0; --i) {
        while (tl + 1 < nb && Da[i] + Db[tl + 1] < c) ++tl;
        while (tr + 1 < nb && Da[i] + Db[tr + 1] <= c) ++tr;
        for (int j = tl + 1; j <= tr; ++j) {
            if (Flag) {
                return Print(ca1, cb1, i, j);
            } else {
                Flag = true, ca1 = i, cb1 = j;
            }
        }
    }
    tl = -1, tr = -1;
    for (int i = na - 1; i >= 0; --i) {
        while (tl + 1 < nb && Da[i] + Db[tl + 1] < c + p) ++tl;
        while (tr + 1 < nb && Da[i] + Db[tr + 1] <= c + p) ++tr;
        for (int j = tl + 1; j <= tr; ++j) {
            if (Flag) {
                return Print(ca1, cb1, i, j);
            } else {
                Flag = true, ca1 = i, cb1 = j;
            }
        }
    }
    return 0;
}