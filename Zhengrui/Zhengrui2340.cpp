#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

using int64 = long long;

const int N = 5e5 + 10, M = N / 2;
const int dx[] = {1, 1, 0, -1, -1, -1, 0, 1};
const int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};

int n, m, q;
int Ax[N], Ay[N], Bx[N], By[N], Cx[N], Cy[N], Dx[N], Dy[N];
int tl[N], t[N], R[N], D[N], Sx[N], Sy[N];

int64 tr[N], Ans[N], Cle[N];

std::vector<std::pair<int, int> > Cha[N], Ask[N];

inline int LB(int x) { return x & -x; }

inline void Add(int i, int x) {
    for (int t = i; i < N; i += LB(i)) tl[i] += x, tr[i] += t * 1ll * x;
}
inline int64 Query(int i) {
    int64 Ans = 0;
    for (int t = i; i; i -= LB(i)) Ans += (t + 1ll) * tl[i] - tr[i];
    return Ans;
}

inline void Clear() {
    for (int i = 0; i < N; ++i) tl[i] = tr[i] = Cle[i] = 0, Cha[i].clear(), Ask[i].clear();
}

inline void Copy() {
    for (int i = 1; i <= n; ++i) Ax[i] = Cx[i], Ay[i] = Cy[i], Bx[i] = Dx[i], By[i] = Dy[i];
}

inline void Mv(int i) {
    Ax[R[i]] += D[i] * dx[t[i]], Ay[R[i]] += D[i] * dy[t[i]], Bx[R[i]] += D[i] * dx[t[i]], By[R[i]] += D[i] * dy[t[i]];
}

inline void Solve() {
    int64 Ret = 0;
    for (int i = 1; i < N; ++i) {
        for (int j = Cha[i].size(); j--;) {
            if (Cha[i][j].second > 0) {
                Add(Cha[i][j].first, 1), Add(Cha[i][j].second + 1, -1);
            } else {
                Add(Cha[i][j].first, -1), Add(-Cha[i][j].second + 1, 1);
            }
        }
        Ret += Cle[i];
        for (int j = Ask[i].size(); j--;) Ans[Ask[i][j].first] += Query(Ask[i][j].second) + Ret;
    }
}

inline void Insert(int a, int b, int c) { Cha[a].emplace_back(b, c); }

inline void Terp(int a, int b, int c, int Op) {
    if (c > 0) {
        Cle[a] += (c - b + 1) * !Op, Insert(a, N - c + 1, -(N - b + 1));
    } else {
        c = -c, Cle[a] -= (c - b + 1) * !Op, Insert(a, N - c + 1, N - b + 1);
    }
}

inline void Solve1(int* Ax, int* Ay, int* Bx, int* By, int* Sx, int* Sy, int Op) {
    Clear();
    Copy();
    if (!Op) {
        for (int i = 1; i <= n; ++i) {
            Insert(Ay[i], Ax[i], Ax[i]), Insert(Ay[i], Bx[i], -Bx[i]);
            Insert(By[i], Ax[i], -Ax[i]), Insert(By[i], Bx[i], Bx[i]);
        }
    }
    for (int i = 1; i <= m; Mv(i++)) {
        if ((t[i] ^ Op) == 0) {
            Insert(Ay[R[i]], Ax[R[i]] + 1, Ax[R[i]] + D[i]), Insert(Ay[R[i]], Bx[R[i]] + 1, -Bx[R[i]] - D[i]);
            Insert(By[R[i]], Ax[R[i]] + 1, -Ax[R[i]] - D[i]), Insert(By[R[i]], Bx[R[i]] + 1, Bx[R[i]] + D[i]);
        } else if ((t[i] ^ Op) == 4) {
            Insert(Ay[R[i]], Ax[R[i]] - D[i], Ax[R[i]] - 1), Insert(Ay[R[i]], Bx[R[i]] - D[i], -Bx[R[i]] + 1);
            Insert(By[R[i]], Ax[R[i]] - D[i], -Ax[R[i]] + 1), Insert(By[R[i]], Bx[R[i]] - D[i], Bx[R[i]] - 1);
        }
    }
    for (int i = 1; i <= q; ++i) Ask[Sy[i]].emplace_back(i, Sx[i]);
    Solve();
}
inline void Solve2(int* Ax, int* Ay, int* Bx, int* By, int* Sx, int* Sy, int Op) {
    Clear(), Copy();
    for (int i = 1; i <= m; Mv(i++)) {
        if ((t[i] ^ Op) == 3) {
            Terp(Ax[R[i]] + Ay[R[i]], Ax[R[i]] - D[i], Ax[R[i]] - 1, Op);
            Terp(Bx[R[i]] + Ay[R[i]], Bx[R[i]] - D[i], -Bx[R[i]] + 1, Op);
            Terp(Ax[R[i]] + By[R[i]], Ax[R[i]] - D[i], -Ax[R[i]] + 1, Op);
            Terp(Bx[R[i]] + By[R[i]], Bx[R[i]] - D[i], Bx[R[i]] - 1, Op);
        } else if ((t[i] ^ Op) == 7) {
            Terp(Ax[R[i]] + Ay[R[i]], Ax[R[i]] + 1, Ax[R[i]] + D[i], Op);
            Terp(Bx[R[i]] + Ay[R[i]], Bx[R[i]] + 1, -Bx[R[i]] - D[i], Op);
            Terp(Ax[R[i]] + By[R[i]], Ax[R[i]] + 1, -Ax[R[i]] - D[i], Op);
            Terp(Bx[R[i]] + By[R[i]], Bx[R[i]] + 1, Bx[R[i]] + D[i], Op);
        }
    }
    for (int i = 1; i <= q; ++i) Ask[Sx[i] + Sy[i]].emplace_back(i, N - Sx[i]);
    Solve();
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> m >> q;
    for (int i = 1; i <= n; ++i) std::cin >> Cx[i] >> Cy[i] >> Dx[i] >> Dy[i], ++Dx[i], ++Dy[i];
    for (int i = 1; i <= m; ++i) std::cin >> t[i] >> R[i] >> D[i];
    for (int i = 1; i <= q; ++i) std::cin >> Sx[i] >> Sy[i];
    Solve1(Ax, Ay, Bx, By, Sx, Sy, 0);
    Solve1(Ay, Ax, By, Bx, Sy, Sx, 2);
    Solve2(Ax, Ay, Bx, By, Sx, Sy, 0);
    Solve2(Ay, Ax, By, Bx, Sy, Sx, 4);
    for (int i = 1; i <= n; ++i) --Dx[i], std::swap(Cx[i], Dx[i]), Cx[i] = M - Cx[i], Dx[i] = M - Dx[i], ++Dx[i];
    for (int i = 1; i <= m; ++i) {
        if (t[i] & 1) {
            t[i] ^= 2;
        } else if (t[i] % 4 == 0) {
            t[i] ^= 4;
        }
    }
    for (int i = 1; i <= q; ++i) Sx[i] = M - Sx[i];
    Solve2(Ax, Ay, Bx, By, Sx, Sy, 0);
    Solve2(Ay, Ax, By, Bx, Sy, Sx, 4);
    for (int i = 1; i <= q; ++i) std::cout << Ans[i] << '\n';
    return 0;
}