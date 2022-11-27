#include <bits/stdc++.h>

const int B = 10;
const int E = 1 << B;
const int N = 1000005;
const int Ns = 1 << 21;
const int M = 100001;

using Bit = std::bitset<M>;

int n, m, q, o, L, R, x, IdCnt;
int Id[M], a[N], Seg[Ns];

Bit f[E];

inline void Check(int x) {
    if (Id[x]) return;
    int n = Id[x] = 1 << IdCnt++;
    for (int i = 0; i < n; ++i) {
        Bit &Bi = f[i | n] = f[i];
        for (int j = x; j < M; ++j) Bi[j] = Bi[j] | Bi[j - x];
    }
}

inline void Build(int u, int l, int r) {
    if (l == r) return void(Seg[u] = Id[a[l]]);
    int Mid = l + r >> 1;
    Build(u << 1, l, Mid), Build(u << 1 | 1, Mid + 1, r);
    Seg[u] = Seg[u << 1] | Seg[u << 1 | 1];
}

inline void Update(int u, int l, int r) {
    if (l >= L && r <= R) return void(Seg[u] = Id[x]);
    if (Seg[u] != (Seg[u << 1] | Seg[u << 1 | 1])) Seg[u << 1] = Seg[u << 1 | 1] = Seg[u];
    int Mid = l + r >> 1;
    if (L <= Mid) Update(u << 1, l, Mid);
    if (R > Mid) Update(u << 1 | 1, Mid + 1, r);
    Seg[u] = Seg[u << 1] | Seg[u << 1 | 1];
}

inline int Query(int u, int l, int r) {
    if (l >= L && r <= R) return Seg[u];
    if (Seg[u] != (Seg[u << 1] | Seg[u << 1 | 1])) Seg[u << 1] = Seg[u << 1 | 1] = Seg[u];
    int Mid = l + r >> 1, Ans = 0;
    if (L <= Mid) Ans |= Query(u << 1, l, Mid);
    if (R > Mid) Ans |= Query(u << 1 | 1, Mid + 1, r);
    return Ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> m >> q, f[0][0] = 1;
    for (int i = 1; i <= n; ++i) std::cin >> a[i], Check(a[i]);
    Build(1, 1, n);
    while (q--) {
        std::cin >> o >> L >> R >> x;
        if (o == 1) {
            Check(x), Update(1, 1, n);
        } else if (o == 2) {
            std::cout << (f[Query(1, 1, n)][x] ? "Yes" : "No") << '\n';
        }
    }
    return 0;
}