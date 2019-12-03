#include <cstdlib>
#include "pascal.hpp"
const int K = 6;
const int N = 210;
const int dx[4] = {-1, 0, 0, 1};
const int dy[4] = {0, -1, 1, 0};
char ch;
int T, cnt, m, n;
int ans[K];
int a[N][N];
void dfs1(int, int);
void dfs2(int, int);
void dfs3(int, int);
void Main();
int main() {
	freopen("in.in", "r", stdin);
    readln(n, m);
    while (n + m > 0) {
        printf("Case %d: ", ++T);
        Main();
        printf("OK!\n");
        readln(n, m);
    }
    return 0;
}
inline void Main() {
    for (int i = 2; i <= n + 1; ++i) {
        for (int j = 0; j < m; ++j) {
            read(ch);
            if (ch > '9') {
                ch = ch - 'a' + 10;
            } else {
                ch -= '0';
            }
            a[i][(j << 2) + 2] = (ch & 8) >> 3;
            a[i][(j << 2) + 3] = (ch & 4) >> 2;
            a[i][(j << 2) + 4] = (ch & 2) >> 1;
            a[i][(j << 2) + 5] = ch & 1;
        }
        readln();
    }
    m <<= 2;
    for (int i = 0; i <= n + 2; ++i) {
        a[i][0] = -1;
        a[i][m + 2] = -1;
    }
    for (int i = 0; i <= m + 2; ++i) {
        a[0][i] = -1;
        a[n + 2][i] = -1;
    }
    dfs1(1, 1);
    for (int i = 2; i <= n + 1; ++i) {
        for (int j = 2; j <= m + 1; ++j) {
            if (a[i][j] == 1) {
                cnt = 0;
                dfs2(i, j);
                ++ans[cnt];
            }
        }
    }
    for (int i = 0; i < ans[1]; ++i) {
        printf("A");
    }
    for (int i = 0; i < ans[5]; ++i) {
        printf("D");
    }
    for (int i = 0; i < ans[3]; ++i) {
        printf("J");
    }
    for (int i = 0; i < ans[2]; ++i) {
        printf("K");
    }
    for (int i = 0; i < ans[4]; ++i) {
        printf("S");
    }
    for (int i = 0; i < ans[0]; ++i) {
        printf("W");
    }
}
inline void dfs1(int x, int y) {
    a[x][y] = -1;
    for (int i = 0; i < 4; ++i) {
        if (a[x + dx[i]][y + dy[i]] == 0) {
            dfs1(x + dx[i], y + dy[i]);
        }
    }
}
inline void dfs2(int x, int y) {
    a[x][y] = -1;
    for (int i = 0; i < 4; ++i) {
        if (a[x + dx[i]][y + dy[i]] == 1) {
            dfs2(x + dx[i], y + dy[i]);
        } else if (a[x + dx[i]][y + dy[i]] == 0) {
            ++cnt;
            dfs3(x + dx[i], y + dy[i]);
        }
    }
}
inline void dfs3(int x, int y) {
    a[x][y] = -1;
    for (int i = 0; i < 4; ++i) {
        if (a[x + dx[i]][y + dy[i]] == 0) {
            dfs3(x + dx[i], y + dy[i]);
        }
    }
}
