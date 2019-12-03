#include <bits/stdc++.h>
const int N = 31;
char c;
int ans, n, m, x, y;
int da[N], db[N], dc[N];
int e[N][N];
void dfs(int);
int main() {
    scanf("%d %d", &n, &m);
    if (m == 0) {
        long long tmp = 1;
        while (n--) {
            tmp *= 3;
        }
        printf("%lld\n", tmp);
        return 0;
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d %c", &x, &y, &c);
        if (x > y) {
            std::swap(x, y);
        }
        e[x][y] = c == 'R' ? -1 : 1;
    }
    dfs(1);
    printf("%d\n", ans);
    return 0;
}
inline void dfs(int x) {
    if (x > n) {
        ++ans;
        return;
    }
    register int flag = 0;
    if (!da[x]) {
        for (register int i = x + 1; i <= n; ++i) {
            if (e[x][i] == -1) {
                if (da[i]) {
                    flag = 1;
                }
                ++db[i];
                ++dc[i];
            } else if (e[x][i] == 1) {
                if (db[i] && dc[i]) {
                    flag = 1;
                }
                ++da[i];
            }
        }
        if (!flag) {
            dfs(x + 1);
        }
        for (register int i = x + 1; i <= n; ++i) {
            if (e[x][i] == -1) {
                --db[i];
                --dc[i];
            } else if (e[x][i] == 1) {
                --da[i];
            }
        }
    }
    flag = 0;
    if (!db[x]) {
        for (register int i = x + 1; i <= n; ++i) {
            if (e[x][i] == -1) {
                if (db[i]) {
                    flag = 1;
                }
                ++da[i];
                ++dc[i];
            } else if (e[x][i] == 1) {
                if (da[i] && dc[i]) {
                    flag = 1;
                }
                ++db[i];
            }
        }
        if (!flag) {
            dfs(x + 1);
        }
        for (register int i = x + 1; i <= n; ++i) {
            if (e[x][i] == -1) {
                --da[i];
                --dc[i];
            } else if (e[x][i] == 1) {
                --db[i];
            }
        }
    }
    flag = 0;
    if (!dc[x]) {
        for (register int i = x + 1; i <= n; ++i) {
            if (e[x][i] == -1) {
                flag = 1;
            } else if (e[x][i] == 1) {
                if (da[i] && db[i]) {
                    flag = 1;
                }
                ++dc[i];
            }
        }
        if (!flag) {
            dfs(x + 1);
        }
        for (register int i = x + 1; i <= n; ++i) {
            if (e[x][i] == 1) {
                --dc[i];
            }
        }
    }
}
