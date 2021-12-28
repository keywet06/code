#include <bits/stdc++.h>

template <typename Type1, typename Type2>
inline Type1 Min(Type1 x, Type2 y) {
    return x < y ? x : y;
}

template <typename Type1, typename Type2>
inline Type1 Max(Type1 x, Type2 y) {
    return x > y ? x : y;
}

template <typename Type1, typename Type2>
inline Type1 &Mid(Type1 &x, Type2 y) {
    return x < y ? x : (x = y);
}

template <typename Type1, typename Type2>
inline Type1 &Mad(Type1 &x, Type2 y) {
    return x > y ? x : (x = y);
}

using int64 = long long;

const int N = 5005;
const int64 INF = 0x0101010101010101;
const int64 JNF = 0xfefefefefefefefe;

char ch;

int T, n, k, cx, cy, na, nb;
int pa[N], pb[N], va[N], vb[N], ca[N], cb[N];

inline int Dis(int i, int j) { return std::abs(pa[i] - pb[j]); }
inline bool In(int i, int j) { return Dis(i, j) <= k; }

inline void T1() {
    int NA = na + 1, NB = nb + 1;
    int h[NA][NB];
    int64 f[NA][NB], g[NA][NB];
    memset(h, 0, sizeof(h));
    memset(f, 0xfe, sizeof(f));
    memset(g, 0xfe, sizeof(g));
    f[0][1] = g[1][0] = 0;
    for (int i = 1, j = 0; i <= na; ++i) {
        while (j < nb && pb[j + 1] + k < pa[i]) ++j;
        ca[i] = j;
    }
    for (int i = 1, j = 0; i <= nb; ++i) {
        while (j < na && pa[j + 1] + k < pb[i]) ++j;
        cb[i] = j;
    }
    for (int i = 1; i <= na; ++i) {
        for (int j = 1; j <= nb; ++j) {
            if (In(i, j)) h[i][j] = h[i - 1][j - 1] + 1;
            f[i][j] = f[i][j - 1];
            if (In(i - 1, j)) Mid(f[i][j], f[i - 1][j - 1] - va[i - 1]);
            g[i][j] = g[i - 1][j];
            if (In(i, j - 1)) Mid(g[i][j], g[i - 1][j - 1] - vb[i - 1]);
            if (j - h[i - 1][j] <= ca[i]) ;
        }
    }
}

inline void T2() {}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> T >> n >> k;
    for (int i = 1; i <= n; ++i) {
        std::cin >> ch >> cx >> cy;
        (ch == 'G' ? pa[++na] : pb[++nb]) = cx;
        (ch == 'G' ? pa[na] : pb[nb]) = cy;
    }
    pa[++na] = int(2e9) + 5;
    (T == 1 ? T1 : T2)();
    return 0;
}