#include <bits/stdc++.h>

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

const int N = 605;
const int FN = N * 3;
const int FM = N * N;

int n, Ans;
int IdCa[N], IdCb[N], Cas[N], Cbs[N], NumCa[N], NumCb[N];
int a[N][N], Col[2][N][N], s[N][N];

std::vector<std::pair<int, int> > ColP[FM];

inline void Add(int ax, int ay, int x, int y, int cx, int cy) {
    Col[ax][x][cx] = y;
    if (int v = Col[ay][y][cx]) Col[ax][v][cx] = 0, Add(ay, ax, y, v, cy, cx);
    Col[ay][y][cx] = x;
}

inline void Add(int x, int y) {
    int cx = 1, cy = 1;
    while (Col[0][x][cx]) ++cx;
    while (Col[1][y][cy]) ++cy;
    Add(0, 1, x, y, cx, cy);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1, x; j <= n; ++j) {
            std::cin >> x, a[i][j] = x;
            ColP[x].emplace_back(i, j);
        }
    }
    for (int c = 1; c <= n * n; ++c) {
        if (ColP[c].empty()) continue;
        int TCa = 0, TCb = 0, CAns = 0;
        for (auto p : ColP[c]) {
            int x = p.first, y = p.second;
            if (!IdCa[x]) IdCa[x] = ++TCa, Cas[TCa] = x;
            if (!IdCb[y]) IdCb[y] = ++TCb, Cbs[TCb] = y;
            Mad(CAns, ++NumCa[x], ++NumCb[y]);
        }
        for (auto p : ColP[c]) Add(IdCa[p.first], IdCb[p.second]);
        for (int i = 1; i <= TCa; ++i) {
            for (int j = 1; j <= CAns; ++j) {
                if (int x = Col[0][i][j]) s[Cas[i]][Cbs[x]] = j - 1;
            }
        }
        Mad(Ans, CAns++);
        for (int i = 1; i <= TCa; ++i) IdCa[Cas[i]] = 0, NumCa[Cas[i]] = 0, memset(Col[0][i], 0, sizeof(int) * CAns);
        for (int i = 1; i <= TCb; ++i) IdCb[Cbs[i]] = 0, NumCb[Cbs[i]] = 0, memset(Col[1][i], 0, sizeof(int) * CAns);
    }
    std::vector<std::tuple<int, int, int> > Vec;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s[i][j]) Vec.emplace_back(i, j, s[i][j]);
        }
    }
    std::cout << Ans - 1 << ' ' << Vec.size() << '\n';
    for (auto p : Vec) std::cout << std::get<0>(p) << ' ' << std::get<1>(p) << ' ' << std::get<2>(p) << '\n';
    return 0;
}