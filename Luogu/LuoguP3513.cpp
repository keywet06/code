#include <bits/stdc++.h>

#define pub push_back

const int B = 2;
const int N = 5005;
const int M = N << 1;

bool in[N];
bool lk[N][N];

int n, ind, tot, num, top;
int sz[B], s[B];
int mat[N], con[N];
int dfn[M], low[M], instack[M], sta[M], bl[M];

std::vector<int> g[M];

inline void tarjan(int x) {
    dfn[x] = low[x] = ++ind, sta[++top] = x, instack[x] = 1;
    for (auto to : g[x])
        if (!dfn[to]) {
            tarjan(to), low[x] = std::min(low[x], low[to]);
        } else if (instack[to]) {
            low[x] = std::min(low[x], dfn[to]);
        }
    if (dfn[x] == low[x]) {
        ++num;
        int y;
        do {
            y = sta[top--], instack[y] = 0, bl[y] = num;
        } while (y != x);
    }
}
inline int read(int x = 0, char ch = getchar(), int f = 0) {
    for (; !isdigit(ch); ch = getchar()) f = ch == '-';
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return f ? -x : x;
}

int main() {
    n = read();
    for (int i = 1, c; i <= n; ++i)
        for (int c = read(), j = 1, x; j <= c; ++j) x = read(), lk[i][x] = 1;
    for (int i = 1; i <= n; ++i) {
        {
            for (int j = 1; j <= n; ++j)
                if (i ^ j) lk[i][j] ? g[i].pub(j + n) : g[i + n].pub(j);
        }
    }
    for (int i = 1; i <= 2 * n; ++i) {
        if (!dfn[i]) tarjan(i);
    }
    for (int i = 1; i <= n; ++i) {
        if (bl[i + n] == bl[i]) return puts("0"), 0;
    }
    for (int i = 1; i <= n; ++i) in[i] = bl[i + n] < bl[i], ++sz[in[i]];
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if ((in[j] ^ in[i]) && (lk[i][j] ^ in[j])) ++con[i], mat[i] = j;
        }
    }
    int ans = sz[0] && sz[1];
    for (int i = 1; i <= n; ++i) {
        if (!con[i] && sz[in[i]] - 1) ++ans;
    }
    for (int i = 1; i <= n; ++i) {
        if (!con[i]) ++s[in[i]];
    }
    ans += s[0] * s[1];
    for (int i = 1; i <= n; ++i) {
        if (con[i] == 1 && !con[mat[i]]) ++ans;
    }
    return printf("%d\n", ans), 0;
}
