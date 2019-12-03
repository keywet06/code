#include <iostream>
const int N = 1005;
int T, cnt, n, k;
int a[N];
int c[N][N], h[N][N];
void dfs(int, int);
int Main();
int main() {
    scanf("%d", &T);
    while (T--) {
        Main();
    }
}
int Main() {
    cnt = n = k = 0;
    memset(h, 0, sizeof(h));
    memset(c, 0, sizeof(c));
    memset(a, 0, sizeof(a));
    scanf("%d", &n);
    c[0][1] = 1;
    for (int i = 1; i <= 20; ++i) {
        for (int j = 1; j <= i; ++j) {
            c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
        }
    }
    k = 20;
    while (c[k][(k - 1) / 2 + 1] >= n) {
        --k;
    }
    dfs(1, 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i == j) {
                printf("0 ");
                continue;
            }
            for (int l = 1; l <= k; ++l) {
                if (h[i][l] == 1 && h[j][l] == 0) {
                    printf("%d ", l);
                    break;
                }
            }
        }
        printf("\n");
    }
    return 0;
}
inline void dfs(int u, int r) {
    if (u > k / 2) {
        ++cnt;
        for (int i = 1; i <= k / 2; ++i) {
            h[cnt][a[i]] = 1;
        }
        return;
    }
    for (int i = r; i <= k; ++i) {
        a[u] = i;
        dfs(u + 1, i + 1);
        if (cnt == n) {
            return;
        }
    }
}