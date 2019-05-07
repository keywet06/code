#include <cstdio>
const int N = 105;
const int dfx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dfy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
int cnt, n, m;
int a[N][N];
void getln();
void dfs(int, int);
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        getln();
        for (int j = 1; j <= m; ++j) {
            a[i][j] = getchar() == 'W';
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i][j]) {
                ++cnt;
                dfs(i, j);
            }
        }
    }
    printf("%d\n", cnt);
    return 0;
}
inline void getln() {
    while (getchar() != '\n')
        ;
}
inline void dfs(int x, int y) {
    a[x][y] = 0;
    for (int i = 0; i < 8; ++i) {
        if (a[x + dfx[i]][y + dfy[i]]) {
            dfs(x + dfx[i], y + dfy[i]);
        }
    }
}