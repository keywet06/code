#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

#ifndef OCT_MIAD_HPP
#define OCT_MIAD_HPP

#define templ template <typename Type1, typename Type2>
templ inline Type1 Min(Type1 x, Type2 y) { return x < y ? x : y; }
templ inline Type1 Max(Type1 x, Type2 y) { return y < x ? x : y; }
templ inline Type1 &Mid(Type1 &x, Type2 y) { return x < y ? x : x = y; }
templ inline Type1 &Mad(Type1 &x, Type2 y) { return y < x ? x : x = y; }
#undef templ

#define templ template <typename Type1, typename Type2, typename... Args>
templ inline Type1 Min(Type1 x, Type2 y, Args... args) { return Min(Min(x, y), args...); }
templ inline Type1 Max(Type1 x, Type2 y, Args... args) { return Max(Max(x, y), args...); }
templ inline Type1 &Mid(Type1 &x, Type2 y, Args... args) { return Mid(Mid(x, y), args...); }
templ inline Type1 &Mad(Type1 &x, Type2 y, Args... args) { return Mad(Mad(x, y), args...); }
#undef templ

#endif

using int64 = long long;

const int N = 800;
const int M = 8000;
const int d[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

/* const */ int64 INF;

int n, m, Cnt;
int Px[M], Py[M];
int Map[N][N], Id[N][N], Next[4][N][N], Dis[4][M], Par[4][M];

int64 f[M][M];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> m;
    int Tx, Ty;
    for (int i = 1; i <= n; ++i) {
        std::string s;
        std::cin >> s;
        for (int j = 0; j < m; ++j) {
            if (s[j] == '#') Map[i][j + 1] = 1, Id[i][j + 1] = ++Cnt, Px[Cnt] = i, Py[Cnt] = j + 1;
            if (s[j] == 'G') Map[i][j + 1] = 2, Tx = i, Ty = j + 1;
        }
    }
    Id[Tx][Ty] = ++Cnt, Px[Cnt] = Tx, Py[Cnt] = Ty;
    for (int c = 0, Si, Di, Ei, Sj, Dj, Ej; c < 4; ++c) {
        d[c][0] > 0 ? (Si = n, Di = -1, Ei = 0) : (Si = 1, Di = 1, Ei = n + 1);
        d[c][1] > 0 ? (Sj = m, Dj = -1, Ej = 0) : (Sj = 1, Dj = 1, Ej = m + 1);
        for (int i = Si; i != Ei; i += Di) {
            for (int j = Sj; j != Ej; j += Dj) Next[c][i][j] = Map[i][j] ? Id[i][j] : Next[c][i + d[c][0]][j + d[c][1]];
        }
    }
    for (int c = 0; c < 4; ++c) {
        for (int i = 1; i <= Cnt; ++i) {
            Par[c][i] = Next[c][Px[i] + d[c][0]][Py[i] + d[c][1]];
            Dis[c][i] = std::abs(Px[i] - Px[Par[c][i]]) + std::abs(Py[i] - Py[Par[c][i]]);
        }
    }
    memset(f, 1, sizeof(f)), INF = **f;
    for (int c = 0; c <= Cnt + 6; ++c) f[Cnt][c] = 0;
    for (int c = Cnt + 5; c >= 2; --c) {
        for (int u = 1; u < Cnt; ++u) {
            for (int i = 0; i < 4; ++i) Mid(f[u][c], f[Par[i][u]][c + 1] + Dis[i][u] * c);
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (Map[i][j] == 2) {
                std::cout << 0;
            } else {
                int64 Ans = INF;
                for (int c = 0, v; c < 4; ++c) {
                    v = Next[c][i + d[c][0]][j + d[c][1]];
                    Mid(Ans, f[v][2] + std::abs(Px[v] - i) + std::abs(Py[v] - j));
                }
                std::cout << (Ans == INF ? -1 : Ans);
            }
            std::cout << " \n"[j == m];
        }
    }
    return 0;
}