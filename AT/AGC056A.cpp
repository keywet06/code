#include <bits/stdc++.h>

#define Deb std::cerr
#define Delin Deb << "[Debug] at Line " << __LINE__
#define Debug Delin << " : "
#define Deline Delin << std::endl

template <typename _Tp>
inline _Tp Max(_Tp x, _Tp y) {
    return x > y ? x : y;
}

template <typename _Tp, typename... Args>
inline _Tp Max(_Tp x, _Tp y, Args... args) {
    return Max(Max(x, y), args...);
}

using int64 = long long;

const int N = 105;
const int M = 505;

int n, flag;
int r[N];

int64 co, rts;
int64 a[N][N], ret[N][N];
int64 ans[M][M];
int64 pre[N][N][N];

inline void dfs(int c, int cnt) {
    ++rts;
    if (c > n) {
        if (cnt != n) return;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) ret[i][j] = a[i][j];
        }
        flag = 1;
        return;
    }
    int toc, b = c - 1, col;
    int64 *B = a[b], *C = a[c];
    for (int i = 1; i + 2 <= n; ++i) {
        if (!r[i] || !r[i + 1] || !r[i + 2]) continue;
        --r[i], --r[i + 1], --r[i + 2];
        toc = cnt - (B[i] && B[i + 2] && !B[i + 1] && B[i] != B[i + 2]);
        col = Max(B[i], B[i + 1], B[i + 2]);
        if (!col) col = ++co, ++toc;
        C[i] = C[i + 1] = C[i + 2] = col;
        dfs(c + 1, toc);
        C[i] = C[i + 1] = C[i + 2] = 0;
        ++r[i], ++r[i + 1], ++r[i + 2];
        if (flag) return;
    }
    for (int i = 1; i + 1 <= n; ++i) {
        if (!r[i] || !r[i + 1]) continue;
        --r[i], --r[i + 1];
        toc = cnt, col = Max(B[i], B[i + 1]);
        if (!col) col = ++co, ++toc;
        C[i] = C[i + 1] = col;
        for (int j = 1; j + 2 <= i; ++j) {
            if (!r[j]) continue;
            --r[j];
            if (!(C[j] = B[j])) C[j] = ++co, ++toc;
            dfs(c + 1, toc);
            toc -= !B[j], C[j] = 0;
            ++r[j];
            if (flag) break;
        }
        for (int j = i + 3; j <= n; ++j) {
            if (flag) break;
            if (!r[j]) continue;
            --r[j];
            if (!(C[j] = B[j])) C[j] = ++co, ++toc;
            dfs(c + 1, toc);
            toc -= !B[j], C[j] = 0;
            ++r[j];
        }
        C[i] = C[i + 1] = 0;
        ++r[i], ++r[i + 1];
        if (flag) return;
    }
    toc = cnt;
    for (int i = 1; i + 4 <= n; ++i) {
        if (!r[i]) continue;
        --r[i];
        if (!(C[i] = B[i])) C[i] = ++co, ++toc;
        for (int j = i + 2; j + 2 <= n; ++j) {
            if (!r[j]) continue;
            --r[j];
            if (!(C[j] = B[j])) C[j] = ++co, ++toc;
            for (int k = j + 2; k <= n; ++k) {
                if (!r[k]) continue;
                --r[k];
                if (!(C[k] = B[k])) C[k] = ++co, ++toc;
                dfs(c + 1, toc);
                toc -= !B[k], C[k] = 0;
                ++r[k];
                if (flag) break;
            }
            toc -= !B[j], C[j] = 0;
            ++r[j];
            if (flag) break;
        }
        toc -= !B[i], C[i] = 0;
        ++r[i];
        if (flag) return;
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    for (n = 1; n < 6; ++n) r[n] = 3;
    for (n = 6; n < 12; ++n) {
        r[n] = 3, flag = 0, dfs(1, 0);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) pre[n][i][j] = ret[i][j];
        }
    }
    std::cin >> n;
    int u = n / 6, c;
    for (int i = 1, c; i < u; ++i) {
        c = (i - 1) * 6;
        for (int x = 1; x <= 6; ++x) {
            for (int y = 1; y <= 6; ++y) ans[c + x][c + y] = pre[6][x][y];
        }
    }
    c = (u - 1) * 6, u = n - (u - 1) * 6;
    for (int x = 1; x <= u; ++x) {
        for (int y = 1; y <= u; ++y) ans[c + x][c + y] = pre[u][x][y];
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) std::cout << (ans[i][j] ? '#' : '.');
        std::cout << '\n';
    }
    return 0;
}